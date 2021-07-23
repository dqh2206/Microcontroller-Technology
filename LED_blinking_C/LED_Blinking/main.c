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
    /* Replace with your application code */
    DDRB |= (1<<DDB0);
    while (1)
    {
	    PORTB |= (1<<PORTB0);
	    _delay_ms(1000);
	    PORTB &= ~ (1<<PORTB0);
	    _delay_ms(1000);
    }
}

