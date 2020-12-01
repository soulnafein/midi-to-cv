#include "cv.h"
#include "spi.h"
#include "xc.h"
#include "keyboard.h"
#include "switch.h"

const float maxVoltage = 10.0;

void CV_select(unsigned short cvNumber) {
    if (cvNumber == 0) {
      LATBbits.LATB7 = 0;
    } else if (cvNumber == 1) {
      LATBbits.LATB8 = 0;
    } else if (cvNumber == 2) {
      LATBbits.LATB9 = 0; 
    }
}

void CV_deSelect(unsigned short cvNumber) {
    if (cvNumber == 0) {
      LATBbits.LATB7 = 1;
    } else if (cvNumber == 1) {
      LATBbits.LATB8 = 1;
    } else if (cvNumber == 2) {
      LATBbits.LATB9 = 1; 
    }
}

void CV_init() {
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB7 = 1;
    LATBbits.LATB8 = 1;
    LATBbits.LATB9 = 1;
}

float limitVoltage(float voltage) {
    if (voltage > maxVoltage) {
        voltage = 10;    
    } else if (voltage < 0) {
        voltage = 0;
    }
    return voltage;
}

float applyScalingCorrection(float voltage) {
    return voltage * 0.990 - 0.01;
}

void CV_changeVoltage(unsigned short cvNumber, float voltage) {
    const int maxDacValue = 4095;
    const unsigned short options = 0x3000;
    
    voltage = limitVoltage(voltage);
    
    CV_select(cvNumber);
    
    float valuePerVoltage = (maxDacValue / maxVoltage);
    unsigned short value = valuePerVoltage * applyScalingCorrection(voltage);
    SPI_write(options + value);

    CV_deSelect(cvNumber);
}

float midiNoteToVoltage(unsigned short note) {
    const float voltagePerNote = 1.0 / 12.0;
    const int octave = note / 12;
    const int relativeNote = note % 12; 
    return octave + (relativeNote * voltagePerNote); 
}

void CV_update() {
    int i;
    for(i = 0; i < 3; i++) {
        unsigned short noteNumber = 0;
        if (SWITCH_polyphonicSelected()) {
            noteNumber = i;
        }
        unsigned short note = KEYBOARD_getNotePressed(noteNumber);
        
        float voltage = midiNoteToVoltage(note);
        CV_changeVoltage(i, voltage);
    }
}




