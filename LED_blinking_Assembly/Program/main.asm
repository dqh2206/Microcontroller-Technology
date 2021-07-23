/*
    AVR Assembler Tutorial Example

    Author: Duong Quang Ha
    Date:    6/7/2021
    Hardware:     Arduino UNO R3
	Microcontroller : ATmega328P
    Purpose: First assembly program (LED blinking)

    Although this is a very simple example of an assmbler program it contains many of the elements that are needed in most real assembler applications.  
*/
.NOLIST
.include "m328pdef.inc"
.LIST
/*
    Macro to set the Stack Pointer to end of ram
    Input Parameters: none
*/
.macro SET_STACK
    ldi    r16, LOW(RAMEND)
    out    spl, r16
    ldi    r16, HIGH(RAMEND)
    out    sph, r16
.endmacro
/*
    Data segment
    All we can do here is reserve a portion of the data segment for our target string.  We cannot initialize data in this segment. We are setting aside 32 bytes 
	(0x20) for our target string.
*/
.dseg
; String declaration
msgd:
    .byte    0x20
; Define Registers
; 
.def	loopCt	= r18		; delay loop count
.def	iLoopRl = r24		; inner loop register low
.def	iLoopRh = r25		; inner loop register high
;
; Define constants
;
.equ	iVal 	= 39998		; inner loop value
/*
    Code Segment
    Use .org to set the base address in code segment where we want the code to begin, in this case 0 or beginning of the segment.  
	The first part of the code segment is reserved for the interrupt/jump table and the first item in the table is the reset vector which we put a 
    jump instruction to the first line of our code..  Since we are not declaring any other interrupts we can ignore the rest of the table and just add a 2nd .org setting 
    the start label or beginning of the code at location  0x20.
*/
.cseg
.org 0
    rjmp    init
/*
    End of Jump table and start of our code.
*/
; Reserved memory location for interrupts, subroutines, ...
.org 0x20
; Replace with your application code
;
; Program loop
;
init : 
	sbi DDRB,DDB0 ; Port pin PB0 as output
start:
	ldi loopCt, 5	;initialize delay multiple for 0.5 sec
	sbi PORTB, PORTB0 ; set PINA0 - A0 analog
	rcall delay10ms
	ldi loopCt, 5	;initialize delay multiple for 0.5 sec
	cbi PORTB, PORTB0 ; clear PINA0
	rcall delay10ms
	; Cycle end
	rjmp start ; start from the beginning, 2 clock cycles
;
; delay subroutine 
;
delay10ms:
	ldi	iLoopRl,LOW(iVal)	; intialize inner loop count in inner
	ldi	iLoopRh,HIGH(iVal)	; loop high and low registers
iLoop:	
	sbiw	iLoopRl,1		; decrement inner loop registers
	brne	iLoop			; branch to iLoop if iLoop registers != 0
	dec	loopCt			; decrement outer loop register
	brne	delay10ms		; branch to oLoop if outer loop register != 0
	nop				; no operation
	ret				; return from subroutine
; End of source code
;
