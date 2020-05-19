#include<avr/io.h>
#include "timeout.h"
#include "motor.h"
#include "IC_74hc148.h"
#include "controller.h"

int main()
{
    Motor motor[3];
    IC_74hc148 sensorData;
    HD44780_3W_8BIT lcdInterface;
    Controller convControl;

    motor[3].Init(&PORTB,PB4,
            &PORTB,PB5);
    motor[2].Init(&PORTC,PC5,
            &PORTC,PC4);
    motor[1].Init(&PORTD,PD6,
            &PORTD,PD7);
    motor[0].Init(&PORTD,PD4,
            &PORTD,PD5);

    sensorData.Init(&PORTC,PC0, //C
                    &PORTC,PC1, //b
                    &PORTC,PC2);//a
    
    lcdInterface.Init(&PORTB,PB0, //DATA/RS
                        &PORTB,PB1 //CLK
                        &PORTB,PB2);//LCD E
    
    convControl.Init(motor,&sensorData,&lcdInterface);

    convControl.get_ready();

    return 0;
}
