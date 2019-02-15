//PART 2.2
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "uart.h"

unsigned int DelayHi = 1200; 	// high time of pulse
unsigned int DelayLo = 20; 		// low time of pulse
unsigned int diff, edge1, edge2, overflows;
unsigned long pulse_width;
int HiorLo; 

void init(){
	DDRB |= (1<<PB1);		//Set PB1 to Output
	DDRB &= ~(1<<PB0);		//Set PB0 to Input
	PORTB |= (1<<PB1);		//Set PB1 (OC1A) to HIGH
	
	TCCR1A = 0x40;				// enable output compare on OC1A to toggle on compare
	TCCR1B |= 0x02;				// set prescaler to 64 for channel 0 (2MHz)
	OCR1A = TCNT1 + 16; 		// pull PB1 pin high quickly
	OCR1A += DelayHi; 			// start second OC1 operation
	HiorLo = 0;					// next time use DelayLo as delay count of OC0 operation
	TIMSK1 |= 0x02; 			// enable interrupt for OC1A
	//TCCR1B &= ~(1<<ICES1);		//sets input capture edge select
	sei();
}

void measurePW(){
	pulse_width = 0;
	TCCR1B |= 0x02;		// prescale the clock by 64
	sei();
	TCCR1B |= 0x40;		// capture rising edges
	overflows = 0;
	TIMSK1 |= 0x01;		// enable overflow interrupt
	TIFR1 |= 0x20;		// clear input capture flag
	while(!(TIFR1 & 0x20));		// wait until an edge
		//sei();			// enable interrupts
		edge1 = ICR1;	// save time of capture first edge
		TCCR1B &= 0xBF;	// capture falling edges
		TIFR1 |= 0x20;	// clear input capture flag
	while(!(TIFR1 & 0x20));		// wait until falling edge
		cli();			// disable interrupts
		edge2 = ICR1;	// save time of the second edge
		if(edge2 < edge1) overflows--;
		diff = edge2-edge1;
		pulse_width = ((long)overflows * 65536u + (long)diff);
		printf("pulse width = 4us * %d\n", pulse_width);

}

void discreteFreq(){
	TCCR0A |= 0x40; // setting CTC mode
	TCCR0A |= 0x02;
	DDRD |= 0x40;		// set as output
	TCCR0B |= 0x03;	
	
	if(pulse_width > 0 && pulse_width < 1500){
		OCR0A = 120;
	}
	else if(pulse_width > 1500 && pulse_width < 2500){
		OCR0A = 105;
	}
	else if(pulse_width > 2500 && pulse_width < 4000){
		OCR0A = 95;
	}
	else if(pulse_width > 4000 && pulse_width < 5500){
		OCR0A = 90;
	}
	else if(pulse_width > 5500 && pulse_width < 6500){
		OCR0A = 80;
	}
	else if(pulse_width > 6500 && pulse_width < 7500){
		OCR0A = 71;
	}
	else if(pulse_width > 7500 && pulse_width < 9000){
		OCR0A = 63;
	}
	else{
		OCR0A = 60;
	}
}

void continuousFreq(){
	TCCR0A |= 0x40;	//toggle pin on reset
	TCCR0A |= 0x02; 	// use CTC mode
	DDRD |= 0x40;
	TCCR0B |= 0x03;

	OCR0A = (int)(0.11*(float)(pulse_width+1025.14));
}

int main(void)
{
	uart_init();
	init();
    while (1)
    {
    	measurePW();
    	printf("pulse width = 4us * %d\n", pulse_width);
    	discreteFreq();
    	//continuousFreq();
    }
}

ISR (TIMER1_COMPA_vect){
	if(HiorLo == 1){
		OCR1A += DelayHi;
		HiorLo = 0;
	} else {
		OCR1A += DelayLo;
		HiorLo = 1;
	}
}

ISR(TIMER1_OVF_vect){
	overflows++;
}

ISR(TIMER0_COMPA_vect){
	PORTB ^= (1<<PB6);
}

