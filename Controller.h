#include<stdio.h>
#include<stdint.h>
#include "motor.h"
#include "hd44780.h"


class Controller{
    static const uint8_t SYS_RUNNING= 0x01;
    static const uint8_t SYS_READY= 0x00;

    public:
        void Init(Motor *motor,)
}