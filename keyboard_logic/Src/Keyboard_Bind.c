//
// Created by ParticleG on 2021/12/1.
//

#include "Keyboard_Bind.h"

uint8_t now_layer = 0;

/*Key Binding. Binding setting in */
/* None-Key Place filled with 0xFFFF*/
uint16_t Key_Bind[KEY_BIND_LAYER][KEY_BIND_NUMBER] = {
    {
        KEYBOARD_Up,    KEYBOARD_D,   KEYBOARD_D,   KEYBOARD_I,
        KEYBOARD_Down,  KEYBOARD_F,   KEYBOARD_F,   KEYBOARD_J,
        KEYBOARD_Left,  KEYBOARD_J,   KEYBOARD_J,   KEYBOARD_K,
        KEYBOARD_Right, KEYBOARD_K,   KEYBOARD_K,   KEYBOARD_L
    }
};
