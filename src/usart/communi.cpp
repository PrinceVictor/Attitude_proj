#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <fstream>
#include <string>

#include "communi.h"
#include "usart.h"

using namespace COMMUNI;

#define writeEABLE 1
#define timerEABLE 0

us_type us_times,period(1000000);
timepoint time_last,time_now;

int main(int argc, char** argv){

//    sayHello();
    Usart * serialPort = nullptr;
    if(argc > 1)  {
        serialPort = new Usart(*(argv+1), boost::lexical_cast<uint32_t>(*(argv+2)));
    }
    else serialPort = new Usart();


    if(serialPort->init_flag){

#if writeEABLE
        std::string writre_filename;
        cout<<"input file name please: "<<endl;
        std::getline(std::cin,writre_filename);

        if(writre_filename.empty()) writre_filename = "sample_data_static.txt";

        std::ofstream Writefile(writre_filename,std::ios_base::out|std::ios_base::trunc|std::ios_base::binary);

        if(!Writefile){
            cout << "open file fialed "<<endl;
            return -1;
        }
        else{
            cout << "open file success "<<endl;
        }

#endif
        uint32_t recieve_count =0;
        uint32_t timercount = 0;
        communiTask Task = SerialConnecting;

        while(true){
            switch (Task) {
            case SerialConnecting:{

                do{

                    serialPort->readData(true,recieve_data,1);
                    cout <<"waiting serail chain connecting"<<endl;

                }while(*recieve_data != 0xa0);

                serialPort->readData(true,recieve_data+1,44);
                if(recieve_data[0] == 0xa0 && recieve_data[5] == 0xb0 && recieve_data[18] == 0xc0 && recieve_data[31] == 0xd0 && recieve_data[44] == 0xe0){
                    cout<< "connect success" <<endl;
                    Task = SerialConnecting_Success;
                }
                break;
            }
            case SerialConnecting_Success:{

                serialPort->readData(true,recieve_data,45);
                if(recieve_data[0] == 0xa0 && recieve_data[5] == 0xb0 \
                        && recieve_data[18] == 0xc0 && recieve_data[31] == 0xd0 && recieve_data[44] == 0xe0){


                    recieve_count++;

#if timerEABLE
                    static float freqz =0;
                    time_now = steady_clock::now();
                    us_times =duration_cast<duration<int,std::micro>>(time_now - time_last) ;
                    if(us_times.count()){
                        freqz = 1.0f/us_times.count()*1000000;
                        time_last = time_now;
                        cout<<"freqz:  "<< freqz << endl;
                    }
#endif

                    origin_attitude.IMU_yaw = byteTofloat(recieve_data+1);

                    origin_attitude.dmp_data.yaw = byteTofloat(recieve_data+6);
                    origin_attitude.dmp_data.pitch = byteTofloat(recieve_data+10);
                    origin_attitude.dmp_data.roll = byteTofloat(recieve_data+14);

                    origin_attitude.gyro.x =(int16_t)(recieve_data[19]*256 + recieve_data[20]) ;
                    origin_attitude.gyro.y =(int16_t)(recieve_data[21]*256 + recieve_data[22]) ;
                    origin_attitude.gyro.z =(int16_t)(recieve_data[23]*256 + recieve_data[24]) ;

                    origin_attitude.acc.x =(int16_t)(recieve_data[25]*256 + recieve_data[26]) ;
                    origin_attitude.acc.y =(int16_t)(recieve_data[27]*256 + recieve_data[28]) ;
                    origin_attitude.acc.z =(int16_t)(recieve_data[29]*256 + recieve_data[30]) ;

                    origin_attitude.q_data.yaw = byteTofloat(recieve_data+32);
                    origin_attitude.q_data.pitch = byteTofloat(recieve_data+36);
                    origin_attitude.q_data.roll = byteTofloat(recieve_data+40);

 #if writeEABLE

                    Writefile.write((char*)&origin_attitude,sizeof(origin_attitude));
                    if(timercount >= 30){
                        Writefile.close();
                        cout << recieve_count * sizeof(origin_attitude) <<endl;
                        Task = SerialComplete;
                    }
#endif
                    time_now = steady_clock::now();
                    us_times = duration_cast<duration<int,std::micro>>(time_now - time_last) ;

                    if(us_times.count() >= period.count()){
                        cout<<"IMU YAW: "<<origin_attitude.IMU_yaw<<endl;
                        cout<<"DMP YAW: "<<origin_attitude.dmp_data.yaw <<"  PITCH: "<<origin_attitude.dmp_data.pitch<<
                              "  ROLL: "<<origin_attitude.dmp_data.roll<<endl;
                        cout<<"gyro x: "<<origin_attitude.gyro.x <<"  gyro y: "<<origin_attitude.gyro.y<<
                              "  gyro z: "<<origin_attitude.gyro.z<<endl;
                        cout<<"acc x: "<<origin_attitude.acc.x <<"  acc y: "<<origin_attitude.acc.y<<
                              "  acc z: "<<origin_attitude.acc.z<<endl;
                        time_last = time_now;
                        timercount++;
                    }
//                    cout<<"time used: "<<us_times.count() <<endl;
                }
                else{
                    Task = SerialConnecting;
                }
                break;
            }
            case SerialComplete:{
                cout<<"trans data completed"<<endl;
                return 0;
                break;
            }
            default:
                break;
            }

        }

    }

    return 0;
}




