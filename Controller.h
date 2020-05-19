#include<stdio.h>
#include<stdint.h>
#include "motor.h"
#include "hd44780.h"
#include "IC_74hc148.h"

class Controller{
    static const uint8_t SYS_RUNNING= 0x01;
    static const uint8_t SYS_READY= 0x00;

    public:
        void Init(Motor *motor,IC_74hc148 *encoder,HD44780 *lcd);
        void get_ready();
    private:
        static const int DELAY_TIME=2000;
        void start();
        void stop();
        void clear_fault();

        uint8_t sys_status;
        Motor *motorArr;
        IC_74hc148 *sensorData;
        HD44780 *lcdInterface;

};

void Controller::start()
{
    for (int i = 3; i >= 0; i--)
    {
        lcdInterface->lcd_clrscr();
        lcdInterface->lcd_string_format("ConvControl\n M%d ON",i+1);
        motorArr[i].start();
        _delay_ms(DELAY_TIME);
    }

    sys_status=SYS_RUNNING;
    lcdInterface->lcd_clrscr();
    lcdInterface->lcd_string_format("ConvControl\n Running...");
    
}

void Controller::stop()
{
    for(int i=0;i<=3;i++)
    {
        lcdInterface->lcd_clrscr();
        lcdInterface->lcd_string_format("ConvControl\n M%d OFF",i+1);
        motorArr[i].stop();
        _delay_ms(DELAY_TIME);
    }
    sys_status=SYS_READY;
    lcdInterface->lcd_cursor_home();
    lcdInterface->lcd_string_format("ConvControl\n READY...");
}

void Controller::clear_fault()
{
    int n;
    n=sensorData->read();

    for(int i=n;i>=0;i--)
    {
        lcdInterface->lcd_clrscr();
        lcdInterface->lcd_string_format("ConvControl\n M%d OFF",i+1);
        motorArr[i].stop();
        _delay_ms(DELAY_TIME);
    }
    for(int i=n+1;i<=3;i++)
    {
        lcdInterface->lcd_clrscr();
        lcdInterface->lcd_string_format("ConvControl\n M%d OFF",j+1);
        motorArr[i].stop();
        _delay_ms(DELAY_TIME);
    }
    sys_status=SYS_READY;
    lcdInterface->lcd_clrscr();
    lcdInterface->lcd_string_format("ConvControl\n Fault in M%d",n+1);
}

void Controller::get_ready()
{
    while (1)
    {
        if((sensorData->read()==6)&&(sys_status==SYS_READY)) start();
        if((sensorData->read()==5)&&(sys_status==SYS_RUNNING)) stop();
        if((sensorData->read()<5)&&(sys_status==SYS_RUNNING)) clear_fault();
        
    }
    
}