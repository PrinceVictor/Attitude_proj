#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>

#include "communi.h"
#include "usart.h"

namespace COMMUNI{

using std::cout;
using std::endl;

uint8_t recieve_data[19];

typedef enum{
    SerialIniting = 0x00,
    SerialConnecting = 0xff,
    SerialConnecting_Success = 0x01
}communiTask;

typedef struct{
    float x;
    float y;
    float z;
}axis_data;

typedef struct{
    axis_data gyro;
    axis_data acc;
    float IMU_yaw;
}origindata;

origindata attitude;

}

using namespace COMMUNI;

int main(int argc, char** argv){

//    uint8_t recieve_data[];

//    sayHello();
    Usart * serialPort = nullptr;
    if(argc > 1)    serialPort = new Usart(*(argv+1), boost::lexical_cast<uint32_t>(*(argv+2)));
    else serialPort = new Usart();


    if(serialPort->init_flag){

        communiTask Task = SerialConnecting;

        while(true){
            switch (Task) {
            case SerialConnecting:{

                do{

                    serialPort->readData(true,recieve_data,6);
                    cout <<"waiting serail chain connecting"<<endl;

                }while(*recieve_data != 0xa0 || *(recieve_data+5) != 0xb0 );

                serialPort->readData(true,recieve_data+6,14);
                if(recieve_data[0] == 0xa0 && recieve_data[5] == 0xb0 && recieve_data[18] == 0xc0){
                    cout<< "connect success" <<endl;
                    Task = SerialConnecting_Success;
                }
                break;
            }
            case SerialConnecting_Success:{

                do{
                    serialPort->readData(true,recieve_data,19);


                }while(recieve_data[0] == 0xa0 && recieve_data[5] == 0xb0 && recieve_data[18] == 0xc0);

                Task = SerialConnecting;
                break;
            }

            default:
                break;
            }




        }

    }

    return 0;
}




