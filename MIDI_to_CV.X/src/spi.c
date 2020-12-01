#include "spi.h"
#include "xc.h"

void SPI_write(unsigned short data)
{
    // wait until transmit buffer is empty
    while(SPI1STATbits.SPITBF!=0);
    // write some data to the SPI1BUF
    SPI1BUF=data;
    // wait while the recieve buffer is empty
    while(SPI1STATbits.SPIRBF==0);
    // when the recieve buffer is not empty anymore, read what is in the buffer
    data=SPI1BUF;
    // wait until the recieve complete flag is set
    while(SPI1STATbits.SPIRBF!=0);
}


void SPI_init() {
    //unlock registers 
    __builtin_write_OSCCONL(OSCCON & 0xBF);

    // SPI Clock is pin 26
    TRISBbits.TRISB15 = 0;
    LATBbits.LATB15 = 0;
    RPOR7bits.RP15R = 8;
    
    // SPI Data Out is pin 3
    TRISAbits.TRISA1 = 0;
    LATAbits.LATA1 = 0;
    RPOR3bits.RP6R = 7;

    
    //lock registers 
    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    SPI1STATbits.SPIEN = 0;

    // if using interrupts
    IFS0bits.SPI1IF = 0;        // clear the interrupt flag
    IEC0bits.SPI1IE = 0;        // enable interrupt
    // write the desired settings to SPI1CON1 and SPI1CON2 (MSTEN = 1 for master)
    SPI1CON1bits.DISSCK = 0;    // disable SCK1 pin bit (SPI Master modes only)[enabled]
    SPI1CON1bits.DISSDO = 0;    // disables SDO1 pin bit[controlled by module]
    SPI1CON1bits.MODE16 = 1;    // word/byte communication select bit[byte wide]
    SPI1CON1bits.SMP = 0;       // SPI1 data input sample phase bit[middle]
    SPI1CON1bits.CKE = 0;       // SPI1 clock edge select bit
    SPI1CON1bits.SSEN = 0;      // slave select enable bit (slave mode)
    SPI1CON1bits.CKP = 1;       // clock polarity set bit[idle high]
    
    
    SPI1CON1bits.MSTEN = 1;     // master mode enable bit
    SPI1CON1bits.SPRE = 0; // 1:2    // secondary prescale bits (master mode)[8:1]
    SPI1CON1bits.PPRE = 0; // 1:1     // primary prescale bits (master mode)[64:1]

    SPI1CON2bits.FRMEN = 0;     // frame SPI1 support bit[disabled]
    SPI1CON2bits.SPIFSD = 0;    // frame sync pulse direction control on SS1 pin bit
    SPI1CON2bits.SPIFPOL = 0;   // frame sync pulse polarity bit (frame mode only)
    SPI1CON2bits.SPIFE = 0;     // frame sync pulse edge select bit
    SPI1CON2bits.SPIBEN = 0;    // enhanced buffer enable bit

    // clear the SPIROV bit
    SPI1STATbits.SPIROV = 0;    // receive overflow flag bit
    
    SPI1CON2 = 0x0000;
    SPI1STAT = 0x8000;

    // enable SPI operation by setting the SPIEN bit
    SPI1STATbits.SPIEN = 1;     // SPI1 enable bit
}
