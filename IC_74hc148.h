#include<stdio.h>

class IC_74hc148{
    public:
        void Init(volatile __uint8_t *pport_c,__uint8_t data_c,
                    volatile __uint8_t *pport_b,__uint8_t data_b,
                    volatile __uint8_t *pport_a,__uint8_t data_a);
        int read();
    private:
        volatile __uint8_t *port_c, c, *port_b, b, *port_a, a;
        volatile __uint8_t *port2DDR(volatile __uint8_t *port){return port-1;}
};
