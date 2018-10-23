#include <iostream>
#include <boost/asio.hpp>
#include <communi.h>
#include <usart.h>
#include <string>
#include <fstream>
using namespace std;
using namespace boost::asio;
using namespace COMMUNI;

origindata data1;

int main(int argc, char** argv)
{

    string input1 ="static1.txt";
    string input2 ="static2.txt";
    string input3 ="static3.txt";
    string output1 ="matlab_static1.txt";
    string output2 ="matlab_static2.txt";
    string output3 ="matlab_static3.txt";
#if 0
    ofstream writefile(output1, ios_base::out|ios_base::trunc );
#elif 0
    ofstream writefile(output2, ios_base::out|ios_base::trunc );
#elif 1
    ofstream writefile(output3, ios_base::out|ios_base::trunc );
#endif

#if  0
    ifstream file(input1, ios_base::in|ios_base::binary);
#elif 0
    ifstream file(input2, ios_base::in|ios_base::binary);
#elif 1
    ifstream file(input3, ios_base::in|ios_base::binary);
#endif
    while(1){
        if(file.read((char *)& data1,sizeof(data1))){
            writefile<<data1.IMU_yaw << " " << data1.dmp_data.yaw << " "<<data1.dmp_data.pitch << " "<<data1.dmp_data.roll
                     <<" "<<data1.gyro.x << " "<<data1.gyro.y << " "<<data1.gyro.z<< " "<<
                       data1.acc.x << " "<<data1.acc.y << " "<<data1.acc.z <<endl;
        }
        else{
            cout<<"finish"<<endl;
            return 0;
        }
    }

    cout << "Hello World!" << endl;
    sayHello();
    return 0;
}
