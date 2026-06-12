
#define F_CPU 16000000UL
#include <avr/io.h>
#include "pwm.h"

int main(void)
{ 
	pwm0a_config();
	pwm_duty(60);
while(1){



}

}


