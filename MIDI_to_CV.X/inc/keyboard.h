#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>

void KEYBOARD_tasks();
bool KEYBOARD_isButtonPressed();
unsigned short KEYBOARD_getNotePressed();

#endif //KEYBOARD_H