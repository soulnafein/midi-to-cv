#include "system.h"
#include "keyboard.h"
#include "leds.h"
#include "cv.h"

int main(void) {
    SYSTEM_Initialize();
    LEDS_keyboardDetached();  
    
    while(1)
    {
        KEYBOARD_tasks();

        if (KEYBOARD_isButtonPressed()) {
            LEDS_gateOn();
        } else {
            LEDS_gateOff();
        }
        
        CV_update();
        
    }
    return 0;
}






