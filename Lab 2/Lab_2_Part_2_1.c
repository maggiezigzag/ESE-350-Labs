/*
 * GccApplication6.c
 *
 * Created: 2/8/2019 4:13:41 PM
 * Author : Derya Yavuz
 */ 

//PART 2.1

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

/*void USART_init(void);
void USART_send( unsigned char data);
void USART_putstring(char* StringPtr);

char String[10] = "";


void USART_init(void){
	
	/*Set baud rate 
	UBRR0H = (unsigned char)(BAUD_PRESCALLER>>8);
	UBRR0L = (unsigned char)BAUD_PRESCALLER;
	//Enable receiver and transmitter
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit 
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_send( unsigned char data)
{
	
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	
}

void USART_putstring(char* StringPtr){
	
	while(*StringPtr != 0x00){
		USART_send(*StringPtr);
	StringPtr++;}
	
}*/

void init(){
	
	
	

	//Timer mode (normal), 0
	// TCCR0A &= ~(1<<WGM00);
	// TCCR0A &= ~(1<<WGM01);
	
	//Set the CTC bits in TCCR0A and TCCR0B.
	//TCCR0A &= ~(1<<WGM00);
	
	//TCCR0B &= ~(1<<WGM02);
	
	//Set the bits to output compare mode.
	
	//TCCR0A &= ~(1<<COM0A1);
	//Set the value to the number of ticks.
	OCR0A = 71;
	TCNT0 = 0;

	//Enable output compare interrupt.
	//TIMSK0 |= (1<< OCIE0A);

	//Set it to output
	DDRD  = 0xFF;
	PORTD = 0;
	//TIMSK0 |= 1 << OCIE0A;
	//TCNT0 = 0;
	//Timer Prescale
	//TCCR0B &= ~(1<<CS00);
	//TCCR0B &= ~(1<<CS01);
	TCCR0B |= (1<<CS02);
	TCCR0A |= (1<<WGM01);
	TCCR0A |= (1<< COM0A0);
	

	
}
/*ISR(TIMER0_COMPA_vect){
	PORTD ^= 0x0F;
}*/




int main(void)
{
	//USART_init();
	init();
	//Set it to look for the rising edGe.
	//TCCR1B |= (1<<ICES1);
	//Set output capture interrupt enable.
	//TIFR1 |= (1<<ICF1);
	
	//Reset counter manually.
	// if(OCR0A == TCNT0){
	// 	TCNT0 = 0;
	// }
	
	while (1)
	{
		
		/*sprintf(String,"%d \n", 5); // Print to terminal (converts a number into a string)
		USART_putstring(String);*/
	}
}
