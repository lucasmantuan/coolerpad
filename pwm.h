#ifndef PWM_H
#define PWM_H

int pwm_enable();
int pwm_disable();
int pwm_period(int *value);
int pwm_duty(int *value);

#endif
