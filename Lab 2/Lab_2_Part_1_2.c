/*
 * GccApplication4.c
 *
 * Created: 2/8/2019 2:09:25 PM
 * Author : Derya Yavuz
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void init(){
	
	//Timer Prescale
	TCCR0B &= ~(1<<CS00);
	TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS02);

	//Timer Mode setting.
	//Timer mode (normal), 0
	TCCR0A &= ~(1<<WGM00);
	TCCR0A &= ~(1<<WGM01);
	
	//Enable output compare interrupt.
	TIMSK0 |= (1<< OCIE0A);

	//Set the bits to output compare mode. 
	TCCR0A |= (1<< COM0A0);
	TCCR0A &= ~(1<<COM0A1);
	
	//Set it to output
	DDRD |= (1 << PORTD6);
	
	//Set the value to the number of ticks.
	OCR0A = 71;
	TCNT0 = 0;
	sei();
	
}

ISR(TIMER0_COMPA_vect){
	OCR0A = TCNT0 + 71;
}



int main(void)
{
	init();
	//Set it to look for the rising edGe.
	//TCCR1B |= (1<<ICES1);
	//Set output capture interrupt enable.
	//TIFR1 |= (1<<ICF1);
	
    while (1) 
    {
		
		
    }
}
