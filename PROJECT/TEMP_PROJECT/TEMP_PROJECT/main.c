/*
 * TEMP_PROJECT.c
 *
 * Created: 6/12/2026 11:38:10 AM
 * Author : LENOVO
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "lcd.h"         //to display on lcd
#include <util/delay.h>
#include "pwm.h"



int main(void)
{
	lcd_init();
	pwm0a_config();
	
	DDRD |= (1<<DDD6);  //pwm output
	DDRB|=(1<<DDB2);		//LED PIN
	  
	
	DDRC&=~(1<<DDC3);     //PC3(ADC3) as input
	
	ADMUX&=~(1<<REFS1);		//AVCC WITH AREF AND INTERNAL REF VOLTAGE
	ADMUX|=(1<<REFS0);
	
	ADMUX&=~(1<<ADLAR);     //ADLAR=0, Takes full 10 bit by default
	
	ADMUX|=(1<<MUX0);           //CHANNEL 3
	ADMUX|=(1<<MUX1);
	ADMUX&=~(1<<MUX2);
	ADMUX&=~(1<<MUX3);
	
	ADCSRA|=(1<<ADEN);      //ADEN=1, ENABLE ADC
	
	ADCSRA|=(1<<ADPS2);		//SET PRESCALAR
	ADCSRA|=(1<<ADPS1);
	ADCSRA|=(1<<ADPS0);
	
	UBRR0H=0;
	UBRR0L=103;
	UCSR0C&=~(1<<UMSEL01)|(1<<UMSEL00);     //ASYCHRONOUS
	UCSR0C&=~(1<<UPM01)|(1<<UPM00);			//NO PARITY
	UCSR0C|=(1<<UCSZ01)|(1<<UCSZ00);				// 8 BIT MODE
	UCSR0C&=~(1<<USBS0);				//1 STOP BIT
	
	UCSR0B|=(1<<TXEN0);				//TRANSMISSION ENABLE
	

	/* Replace with your application code */
	while (1)
	{
		ADCSRA|=(1<<ADSC);		//ADSC=1, START CONVERSION
		
		
		while(!(ADCSRA&(1<<ADIF)));		//check for conversion complete
		ADCSRA|=(1<<ADIF);
		
		uint16_t adc_val=ADC;
		//To print on LCD
		lcd_set_cursor(0,0);           //cursor at inital position
		lcd_print("TEMPERATURE");			//display=>TEMPERATURE
		lcd_set_cursor(1,0);			//cursor on 2nd line
		
		float voltage=adc_val*0.0049;	//Vinput=(adc_val*Aref)/1024          (5/1024=0.0049)
		float temp=voltage/0.01;		//OR temp=volt*100
		// 1 C -->10mV (0.01V)
		
		lcd_print_float(temp);
		_delay_ms(1000);
		
		
		if(temp<35){
			pwm_duty(0);
		}
		else if ((temp>35)&&(temp<=50)){
			pwm_duty(30);
		}
		else if ((temp>50)&&(temp<=70)){
			pwm_duty(60);
		}
		else if (temp>70){
			pwm_duty(100);
		}
		if(temp>=80){
			int data= temp;
			UDR0=data;
			while(!(UCSR0A&(1<<TXC0)));
			UCSR0A|=(1<<TXC0);
			_delay_ms(1000);
		
			PORTB|=(1<<PB2);    //LED ON
		}
		else if(temp<80){
			PORTB&=~(1<<PB2);     //TEMP<80, LED OFF
		}	
			
			

	}
}





