/*
 * LED_Blinking.c
 *
 * Created: 7/23/2021 9:48:28 PM
 * Author : Duong Quang Ha
 * Hardware : Arduino UNO R3
 * Microcontroller : Atmega328P
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

int main(void)
{
	uint8_t i=0; // counter number
	DDRD = 0xFF; // Port D is output port
	/* Replace with your application code */
	while (1)
	{
		/* pin D0 is connected to pin A of IC7447, pin D1 is connected to pin B, pin D2 <-> C, pin D3 <-> D
		Code to send out from PORT D : 0 <-> 0000, 1 <-> 0001, 2 <-> 0010, ...  
		*/
		PORTD = 0x00; // Initialvalue for PORTD
		PORTD |= i;
		i++;
		if(i==10) i=0;
		_delay_ms(1000);
	}
	return 0;
}

