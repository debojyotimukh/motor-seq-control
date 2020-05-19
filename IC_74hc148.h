#include<stdint.h>
#include<stdbool.h> 
#include<avr/io.h>

class IC_74hc148{
    public:
        void Init(volatile uint8_t *pport_c,uint8_t data_c,
                    volatile uint8_t *pport_b,uint8_t data_b,
                    volatile uint8_t *pport_a,uint8_t data_a);
        int read();
    private:
        volatile uint8_t *port_c, c, *port_b, b, *port_a, a;
        volatile uint8_t *port2DDR(volatile uint8_t *port){return port-1;}
};

void IC_74hc148::Init(volatile uint8_t *pport_c,uint8_t data_c,
                    volatile uint8_t *pport_b,uint8_t data_b,
                    volatile uint8_t *pport_a,uint8_t data_a)
{
    //save globals
    port_c=pport_c;
    c=data_c;
    port_b=pport_b;
    b=data_b;
    port_a=pport_a;
    a=data_a;

    *port2DDR(port_c) &= ~(1<<c);
    *port2DDR(port_b) &= ~(1<<b);
    *port2DDR(port_a) &= ~(1<<a);
}

int IC_74hc148::read()
{
    int j=0,k=0,l=0;
    if(bit_is_set(PINC,c)) l=1;
    if(bit_is_set(PINC,b)) k=1;
    if(bit_is_set(PINC,a)) j=1;

    return (4*j+2*k+l);
}


