#ifndef communi_H
#define communi_H

void sayHello(void);

union {
    float float_data;
    unsigned char byte_data[4];
} byte2float;



#endif
