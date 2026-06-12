/*
 * pwm.c
 *
 * Created: 09-06-2026 15:14:26
 *  Author: ACER
  definition doesnt need ;*/ 

#define F_CPU 16000000UL
#include <avr/io.h>

void pwm0a_config()
{
	/*creating output pin for pwm on d6*/

	DDRD |= (1<<DDD6);


	//FAST PWM
	TCCR0A |= (1<<WGM00);
	TCCR0A |= (1<<WGM01);
	// non INVERTING PWM
	TCCR0A &= ~(1<<COM0A0);
	TCCR0A |= (1<<COM0A1);
	//PRESCALAR TIMER CLK/1024
	TCCR0B &=~(1<<CS02);
	TCCR0B |=(1<<CS01);
	TCCR0B |=(1<<CS00);

	OCR0A = 154;
}

void pwm_duty(int duty){
	
	int A = (duty*256) /100;
	OCR0A = A ;
}