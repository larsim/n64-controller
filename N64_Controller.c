#include "globals.h"
#include "n64.h"
#include "beep.h"

void _delay_s(uint8_t sec);

int main()
{
    // PLL to 16Mhz
    PLLCSR = (1<<PLLE);

    // IO
    DDRB = 0xff;
    PORTB = 0xff;
    
    // Inits
    beep_init();
    n64_init();

    int8_t ana = 0;

    while(n64_isConnected() == 0) 
    {
        beep(100);
        _delay_s(1);
    }

    _delay_ms(100);

    while(1)
    {  
        n64_poll();
        ana = xaxis/4;
        if(buttons[N64_A] < N64_ZEROLEN) beep(160+ana);
        if(buttons[N64_B] < N64_ZEROLEN) beep(210+ana);
        if(buttons[N64_Z] < N64_ZEROLEN) beep(128+ana);
        if(buttons[N64_START] < N64_ZEROLEN) beep(64+ana);

        if(buttons[N64_UP] < N64_ZEROLEN) beep(250);
        if(buttons[N64_DOWN] < N64_ZEROLEN) beep(240);
        if(buttons[N64_LEFT] < N64_ZEROLEN) beep(230);
        if(buttons[N64_RIGHT] < N64_ZEROLEN) beep(220);

        if(buttons[N64_CUP] < N64_ZEROLEN) beep(210);
        if(buttons[N64_CDOWN] < N64_ZEROLEN) beep(200);
        if(buttons[N64_CLEFT] < N64_ZEROLEN) beep(190);
        if(buttons[N64_CRIGHT] < N64_ZEROLEN) beep(180);

        if(buttons[N64_L] < N64_ZEROLEN) beep(170);
        if(buttons[N64_R] < N64_ZEROLEN) beep(160);

        _delay_ms(100);
    }

    return 0;
}

// Seconds delay
void _delay_s(uint8_t sec)
{
    uint8_t i;
    for(i=0; i<sec; i++)
    {
        _delay_ms(250);
        _delay_ms(250);
        _delay_ms(250);
        _delay_ms(250);
    }
}
