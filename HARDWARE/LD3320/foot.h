#ifndef FOOT_H
#define FOOT_H

#define front_left 0x01 //PA0
#define front_right 0x02//PA1
#define back_left 0x03//PA2
#define back_right 0x04//PA3

void pwm_init(void);
void set_foot(uint8_t mark,uint8_t angle);
void forward(void);
void backward(void);
void right(void);
void left(void);

#endif