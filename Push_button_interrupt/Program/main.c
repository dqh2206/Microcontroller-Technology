/*
 * Push_button_interrupt.c
 *
 * Created: 7/26/2021 4:30:25 PM
* Created: 7/23/2021 9:48:28 PM
* Author : Duong Quang Ha
* Hardware : Arduino UNO R3
* Micro controller : Atmega328P
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
volatile uint8_t count=0; // global variable 

/* Port D (digital output) of Atmega328P is used to connect directly with 7-segment LED (Common Cathode)
 * In practice, the limiting resistance should be used to limit the current flowing through each segment. 
 * In schematic, PORTD0 is connected to segment A, PORTD1 is connected to segment B, ... 
 * PORTB0 is a digital input that is connected to the push button. 
 */ 
uint8_t LED_Display (uint8_t i)
{
	uint8_t LED[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; // 7-segment LED decoder
	// For example, number 0 corresponds to segment A = 1, B = 1, C = 1, D = 1, E = 1, F = 1, G = 0, Dot = 0. 
	switch(i)
	{
		case 0 : {return LED[0]; break;}
		case 1 : {return LED[1]; break;}
		case 2 : {return LED[2]; break;}
		case 3 : {return LED[3]; break;}
		case 4 : {return LED[4]; break;}
		case 5 : {return LED[5]; break;}
		case 6 : {return LED[6]; break;}
		case 7 : {return LED[7]; break;}
		case 8 : {return LED[8]; break;}
		case 9 : {return LED[9]; break;}
		default: break;
	}
}

ISR(PCINT0_vect) // PINB0 interrupt program
{
	count++;
	if(count==10) count =0;
}

int main(void)
{
    /* Replace with your application code */
	DDRB &= 0xFE; // PortB0 as input
	DDRD = 0xFF; // Port D as output
	PCICR = 0x01; // select interrupt group PCINT0-7
	PCMSK0 = 0x01; // activate PINB0 interrupt
	sei(); // activate global interrupt
	/* Replace with your application code */
	while (1)
	{
		PORTD = LED_Display(count);
		_delay_ms(100);
	}
	return 0;
}

