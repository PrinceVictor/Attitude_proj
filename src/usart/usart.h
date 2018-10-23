#ifndef __usart_H
#define __usart_H

#include <iostream>
#include <boost/asio.hpp>
//#include <boost/thread.hpp>

namespace USART {

using std::cout;
using std::endl;

using namespace boost::asio;

}


class Usart{

public:

    USART::serial_port* com;
    USART::io_service  serial_service;

    uint8_t init_flag;


private:

    const char* com_path = nullptr;
    uint32_t com_baudrate = 460800;

public:

    Usart();
    Usart(char* path, uint32_t baudrate);

    ~Usart();

    uint8_t* readData(bool flag, uint8_t* data, size_t size);
    uint8_t* writeData(bool flag, uint8_t* data, size_t size);

private:

    bool serialInit();

};


#endif
