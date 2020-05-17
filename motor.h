#include<stdio.h>

class Motor{
    static const int MOTOR_RUN=0x01; //Run flag
    static const int MOTOR_IDLE=0x00; //Idle flag

    private:
        volatile __uint8_t* Port2DDR(volatile __uint8_t *port){return port-1;}
        volatile __uint8_t *m_pport_a, *m_pport_b;
        __uint8_t m_dq_a,m_dq_b;
        
        __uint8_t m_status;
    public:
        void Init(volatile __uint8_t *m_pport_pos,__uint8_t m_dq_pos,
                    volatile __uint8_t *m_port_neg,__uint8_t m_dq_neg);
        void start();
        void stop();
        bool is_running();
};