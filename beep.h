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

#include "globals.h"

void beep(uint8_t freq);
void beep_init();
