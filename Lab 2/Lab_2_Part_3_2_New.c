#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>
#include "uart.h"

void adc_init(){
	ADMUX = (1<<REFS0);	// Choose reference voltage on ADMUX
	ADMUX &= ~(1<<REFS1);

	ADMUX &= ~(1<<MUX0);	// Select A0 as input channel
	ADMUX &= ~(1<<MUX1);
	ADMUX &= ~(1<<MUX2);
	ADMUX &= ~(1<<MUX3);

	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t ch){
	ch &= 0b00000111;				// AND operation w/ 7
	ADMUX = (ADMUX & 0xF8)|ch;		// clears bottom 3b before zeroing
	ADCSRA |= (1<<ADSC);			// Starts single conversion
	while(ADCSRA & (1<< ADSC));
		return (ADC);	
}

void adc_voltage(){
	/*
	Groups:
	1: 0 - 128
	2: 128 - 256
	3: 256 - 384
	4: 384 - 512
	5: 512 - 640
	6: 640 - 768
	7: 768 - 896
	8: 896 - 1023
	*/
	int adc_result0 = adc_read(0);
	if(adc_result0 >= 0 && adc_result0 <= 128){
		PORTB &= ~(1<<PINB2);
		PORTB &= ~(1<<PINB3);
		PORTB &= ~(1<<PINB4);
	}
	else if(adc_result0 >= 128 && adc_result0 <= 256){
		PORTB |= (1<<PINB2);
		PORTB &= ~(1<<PINB3);
		PORTB &= ~(1<<PINB4);
	}
	else if(adc_result0 >= 256 && adc_result0 <= 384){
		PORTB &= ~(1<<PINB2);
		PORTB |= (1<<PINB3);
		PORTB &= ~(1<<PINB4);
	}
	else if(adc_result0 >= 384 && adc_result0 <= 512){
		PORTB |= (1<<PINB2);
		PORTB |= (1<<PINB3);
		PORTB &= ~(1<<PINB4);
	}
	else if(adc_result0 >= 512 && adc_result0 <= 640){
		PORTB &= ~(1<<PINB2);
		PORTB &= ~(1<<PINB3);
		PORTB |= (1<<PINB4);
	}
	else if(adc_result0 >= 640 && adc_result0 <= 768){
		PORTB |= (1<<PINB2);
		PORTB &= ~(1<<PINB3);
		PORTB |= (1<<PINB4);
	}
	else if(adc_result0 >= 768 && adc_result0 <= 896){
		PORTB &= ~(1<<PINB2);
		PORTB |= (1<<PINB3);
		PORTB |= (1<<PINB4);
	}
	else{
		PORTB |= (1<<PINB2);
		PORTB |= (1<<PINB3);
		PORTB |= (1<<PINB4);
	}
}

int main(void)
{
	uint16_t adc_result0;
	adc_init();			// initialize ADC
	_delay_ms(50);

	uart_init();
    while (1)
    {	
    	adc_voltage();
    	adc_result0 = adc_read(0);
    	printf("ADC: %d\n", adc_result0);
    }
}
