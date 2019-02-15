#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <math.h>
#include "uart.h"

int LTHRES = 1023;

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

int main(void)
{
	uint16_t adc_result0;
	char int_buffer[10];
	DDRC = 0x01;		// connect sensor to PC0
	adc_init();			// initialize ADC
	_delay_ms(50);

	uart_init();
    while (1)
    {	
    	adc_result0 = adc_read(0);
    	printf("ADC Result: %d\n", adc_result0);
    	if(adc_result0<LTHRES){
    		PORTC = 0x01;
    	}
    	else{
    		PORTC = 0x00;
    	}

    }
}