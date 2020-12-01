#include "switch.h"
#include "xc.h"


void SWITCH_init() {
    TRISAbits.TRISA4 = 1;
    AD1PCFG = 0xFF;
};

bool SWITCH_polyphonicSelected() {
    return PORTAbits.RA4 == 1;
};
