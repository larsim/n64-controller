/* 
 * Nintendo 64 Controller
 * 
 * V1.0  
 * 
 * By: Lars Ivar Miljeteig, September 2011
 * Platform: AVR ATtiny85 (avr-gcc)
 * Dependencies: globals.h
 *
 * Requires 16MHz or more to run correctly
 */

#include "n64.h"
#include "globals.h"

#define N64_TIMEOUT 100

/*
 * Define PIN/PORT etc here
 *  This is to make it easier to port the code 
 *  to another AVR later
 */
#define P PB2
#define PORT PORTB
#define DDR DDRB
#define PMASK 0x40
#define PIN PINB

volatile unsigned char buttons[33], i;
volatile char xaxis=0, yaxis=0;

/*
 * n64_init
 * Initiates the N64 Controller driver
 * Enables Pin interrupts and sets the correct pin as output
 */
void n64_init()
{
    // Enable pin-interrupt (INT0) for falling edge
    MCUCR |= (1<<ISC01);

    // Setting interrupt pin as input
    DDR &= ~(1<<P);
}

/*
 * n64_writePoll
 * Writes 000000011 to the N64 Controller
 * This is a data request message
 */
void n64_writePoll()
{
    // 0
    PORT &= ~(1<<P);
    _delay_us(3);
    PORT |=  (1<<P);
    _delay_us(1);

    // 0
    PORT &= ~(1<<P);
    _delay_us(3);
    PORT |=  (1<<P);
    _delay_us(1);

    // 0
    PORT &= ~(1<<P);
    _delay_us(3);
    PORT |=  (1<<P);
    _delay_us(1);

    // 0
    PORT &= ~(1<<P);
    _delay_us(3);
    PORT |=  (1<<P);
    _delay_us(1);

    // 0
    PORT &= ~(1<<P);
    _delay_us(3);
    PORT |=  (1<<P);
    _delay_us(1);

    // 0
    PORT &= ~(1<<P);
    _delay_us(3);
    PORT |=  (1<<P);
    _delay_us(1);

    // 0
    PORT &= ~(1<<P);
    _delay_us(3);
    PORT |=  (1<<P);
    _delay_us(1);

    // 1
    PORT &= ~(1<<P);
    _delay_us(1);
    PORT |=  (1<<P);
    _delay_us(3);

    // 1
    PORT &= ~(1<<P);
    _delay_us(1);
    PORT |=  (1<<P);
    _delay_us(3);
}

/*
 * n64_isConnected checks if the controller is connected 
 * to the chosen pin by sending a dummy poll message
 *
 * Returns 1 if something is connected and 0 otherwise
 */
char n64_isConnected()
{
    char timeout = N64_TIMEOUT;

    cli();

    // Write mode
    DDR |= (1<<P);

    // Output bits "000000011"
    n64_writePoll();

    // Clear external interrupt flag
    GIFR |= (1<<INTF0);

    // Read mode
    DDR &= ~(1<<P);

    // Wait for falling edge
    while((GIFR & PMASK) != PMASK && --timeout > 0); 

    if(timeout > 0)
    {
        // Wait for another falling edge to be sure
        timeout = 100;
        GIFR |= (1<<INTF0);
        while((GIFR & PMASK) != PMASK && --timeout > 0); 
        GIFR |= (1<<INTF0);
    }
        
    sei();

     // If it didn't time out, something is connected
    if(timeout > 0) return 1;   
    else return 0;
}

void n64_poll()
{
    uint8_t time = 0;

    // I'm still alive
    /*
    PORT ^= (1<<PB4);
    _delay_ms(10);
    PORT ^= (1<<PB4); 
    */

    cli();

    // Write mode
    DDR |= (1<<P);

    // Output bits "000000011"
    n64_writePoll();

    // Clear external interrupt flag
    GIFR |= (1<<INTF0);

    // Read mode
    DDR &= ~(1<<P);

    // Receive first pulse (button A)

    // Count time while pulse is low
    while((PIN & 0x04) != 0x04) time++;  
    
    // Store time while pulse is high
    buttons[0] = time;
    time = 0;  

    // Receive remaining pulses (all other buttons) 

    // Read button status
    for(i=1; i<32; i++)
    {
        // Wait for falling edge
        while((GIFR & PMASK) != PMASK); 

        // Clear external interrupt flag for next
        GIFR |= (1<<INTF0); 

        // Count time while pulse is low
        while((PIN & 0x04) != 0x04) time++;  
        
        // Store time while pulse is high
        buttons[i] = time;
        time = 0;      
    }

    // Sort out x- and y-axis
    xaxis = 0;
    yaxis = 0;
    for(i=0; i<8; i++)
    {
        if(buttons[16+i] < 8) xaxis |= 1<<(7-i);
        if(buttons[24+i] < 8) yaxis |= 1<<(7-i);
    }

    // Reactivate interrupts
    sei();
}


