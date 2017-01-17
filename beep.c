/* 
 * Beep
 * 
 * V1.0  
 * 
 * By: Lars Ivar Miljeteig, September 2011
 * Platform: AVR ATtiny85 (avr-gcc)
 * Dependencies: globals.h
 *
 * A simple timer interrupt driven piezo buzzer
 * beeping library. Written for 16MHz.
 */


#include "beep.h"
#include "globals.h"

volatile uint8_t beeptime = 0;

void beep(uint8_t freq)
{
    beeptime = 150;
    OCR0A = freq;
}

void beep_init()
{
   // Use normal timer mode, no PWM or fancy stuff enabled
    TCCR0A = 0;

    // Timer0 prescaler = 256, 8MHz/256
    TCCR0B = (1<<CS00)|(1<<CS01);

    // Enable timer comparator interrupt A
    TIMSK |= (1<<OCIE0A);

    // Set comparator time
    OCR0A = 30;
};

ISR(TIM0_COMPA_vect)
{ 
    if(beeptime>0) 
    {
        PORTB ^= (1<<PB4);
        beeptime--;
    }
    TCNT0 = 0; 
}
