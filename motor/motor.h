#ifndef MOTOR_H
#define MOTOR_H

int speed_transition(int initial, int final, int time);
int speed_control(int period, int duty);
int turn_on();
int turn_off();

#endif
