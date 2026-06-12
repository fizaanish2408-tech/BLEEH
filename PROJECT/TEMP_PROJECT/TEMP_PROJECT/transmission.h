/*
 * transmission.h
 *
 * Created: 6/12/2026 2:38:36 PM
 *  Author: LENOVO
 */ 


#ifndef TRANSMISSION_H_
#define TRANSMISSION_H_

#define F_CPU 16000000
#include <avr/io.h>
#include<util/delay.h>


void transmission_init(void);
void transmission_enable(void);
void transmission(char data);



#endif /* TRANSMISSION_H_ */