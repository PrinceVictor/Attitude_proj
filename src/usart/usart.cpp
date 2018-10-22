#include "usart.h"

using namespace USART;

Usart::Usart(){
    if(!com_path) com_path = "/dev/ttyUSB0";
    init_flag = serialInit();
}

Usart::Usart(char* path, uint32_t baudrate){
    if(!path) com_path = path;
    if(!baudrate) com_baudrate = baudrate;
    init_flag = serialInit();
}

uint8_t* Usart::readData(bool flag, uint8_t* data, size_t size){
    if(flag){
        USART::read(*com, USART::buffer(data, size));
        return data;
    }
}

uint8_t* Usart::writeData(bool flag, uint8_t* data, size_t size){
    if(flag){
        USART::write(*com, USART::buffer(data, size));
        return data;
    }
}


bool Usart::serialInit(){

    com = new serial_port(serial_service,com_path);

    if(com){
        com->set_option(serial_port::baud_rate(com_baudrate));
        com->set_option(serial_port::flow_control(serial_port::flow_control::none));
        com->set_option(serial_port::parity(serial_port::parity::none));
        com->set_option(serial_port::stop_bits(serial_port::stop_bits::one));
        com->set_option(serial_port::character_size(8));

        cout<<"serial port: "<<com_path<<" baudrate: "<<com_baudrate<<endl;
        cout<<"serial port init success"<<endl;

        return true;
    }
    else{
        cout<<"Init Failed"<<endl;
        return false;
    }
}

Usart::~Usart(){
    if(com){
        delete com;
    }
}
