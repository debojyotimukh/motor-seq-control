#include<stdint.h>
#include<stdbool.h> 

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
