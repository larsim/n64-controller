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

#define N64_A 0
#define N64_B 1
#define N64_Z 2
#define N64_START 3
#define N64_UP 4
#define N64_DOWN 5
#define N64_LEFT 6
#define N64_RIGHT 7
#define N64_L 10
#define N64_R 11
#define N64_CUP 12
#define N64_CDOWN 13
#define N64_CLEFT 14
#define N64_CRIGHT 15

#define N64_ZEROLEN 7

extern volatile unsigned char buttons[33];
extern volatile char xaxis, yaxis;

void n64_poll();
char n64_isConnected();
void n64_init();
