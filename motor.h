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
//Class initialization
void Motor::Init(volatile __uint8_t *m_port_pos, __uint8_t m_dq_pos,
                    volatile __uint8_t *m_port_neg,__uint8_t m_dq_neg)
{
    //save globals
    m_pport_a=m_port_pos;
    m_dq_a=m_dq_pos;
    m_pport_b=m_port_neg;
    m_dq_b=m_dq_neg;

    //init data and clk ports
    *m_pport_a &= ~(1<<m_dq_a); //set pins to LOW
    *m_pport_b &= ~(1<<m_dq_b); //set pins to LOW

    *Port2DDR(m_pport_a) |= (1<<m_dq_a); //Enable pins as outputs
    *Port2DDR(m_pport_b) |= (1<<m_dq_b); //Enable pins as outputs

    m_status=MOTOR_IDLE;
}   

//Motor start
void Motor::start()
{
    *m_pport_a |= (1<<m_dq_a); //set A high
    *m_pport_b &= ~(1<<m_dq_b); //set B low

    m_status=MOTOR_RUN;
}

//Motor stop
void Motor::stop()
{
    *m_pport_a &= ~(1<<m_dq_a); //set A low
    *m_pport_b &= ~(1<<m_dq_b); //set B low

    m_status=MOTOR_IDLE;
}

//status of motor
bool Motor::is_running()
{
    if(m_status==MOTOR_RUN) return true;
    return false;
}
