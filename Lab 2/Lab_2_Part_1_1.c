/*
 * GccApplication3.c
 *
 * Created: 2/6/2019 8:16:32 PM
 * Author : Derya Yavuz
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void init(){
	
	//Enable input capture.
	TCCR1B |= (1<<ICES1);
	
	//Enable for writing. 
	DDRB |= (1<<PINB5);
	
	//Prescale the clock.
	//Timer Prescale
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B &= ~(1<<CS12);
	
	//Setting timer mode to normal.
	TCCR1B &= (1<<WGM12);
	TCCR1B &= (1<<WGM13);
	
	//Enabling interrupts.
	TIMSK1 |= (1<<ICIE1);
	
	//Looking for rising edge.
	TCCR1B |= (1<<ICES1);
	
	
	//Enable all interrupts function.
	sei();
}

ISR(TIMER1_CAPT_vect){
	//or do the PINB-PORTB toggle if this doesn't work
	PORTB ^= (1<<PORTB5);
	TIMSK1 ^= (1<<ICIE1);

}

int main(void)
{
	init();

    while (1) 
    {
    }
}
