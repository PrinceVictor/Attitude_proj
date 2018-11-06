#ifndef communi_H
#define communi_H

#include <iostream>
#include <chrono>

void sayHello(void);

namespace COMMUNI{

uint8_t recieve_data[19];

using std::cout;
using std::endl;
using namespace std::chrono;

typedef std::chrono::duration<int,std::micro> us_type;
typedef std::chrono::steady_clock::time_point timepoint;

typedef enum{
    SerialIniting = 0x00,
    SerialConnecting = 0xff,
    SerialConnecting_Success = 0x01,
    SerialComplete = 0x1f
}communiTask;

typedef struct{
    int16_t x;
    int16_t y;
    int16_t z;
}mpu_data;

typedef struct{
    float yaw;
    float pitch;
    float roll;
}imu_data;

typedef struct{
    imu_data dmp_data;
    imu_data q_data;
    mpu_data gyro;
    mpu_data acc;
    float IMU_yaw;
}origindata;

typedef union {
    float float_data;
    unsigned char byte_data[4];
} byte2float;

float byteTofloat(uint8_t* input){
    byte2float tmpdata;
    tmpdata.byte_data[0] = *input;
    tmpdata.byte_data[1] = *(input+1);
    tmpdata.byte_data[2] = *(input+2);
    tmpdata.byte_data[3] = *(input+3);
    return tmpdata.float_data;
}
origindata origin_attitude;

}



#endif
