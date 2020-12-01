#include "leds.h"
#include "xc.h"

void LEDS_init() {
  TRISBbits.TRISB13 = 0; 
  TRISBbits.TRISB2 = 0;
  TRISBbits.TRISB3 = 0;
  LATBbits.LATB13 = 0;
  LATBbits.LATB2 = 0;
  LATBbits.LATB3 = 0;
}

void LEDS_keyboardAttached() {
  LATBbits.LATB2 = 0;
  LATBbits.LATB3 = 1;
}

void LEDS_keyboardDetached() {
  LATBbits.LATB2 = 1;
  LATBbits.LATB3 = 0;
}

void LEDS_gateOn() {
    LATBbits.LATB13 = 1;
}

void LEDS_gateOff() {
    LATBbits.LATB13 = 0;
}
