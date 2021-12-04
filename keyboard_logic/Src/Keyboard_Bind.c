//
// Created by ParticleG on 2021/12/1.
//

#include "Keyboard_Bind.h"

uint8_t now_layer = 0;

uint8_t keep_layer = 0;
uint8_t temp_layer = 0;
/*Key Binding. Binding setting in */
/* None-Key Place filled with 0xFFFF*/
uint16_t Key_Bind[KEY_BIND_LAYER][KEY_BIND_NUMBER] = {
    {
        0x8001,    KEYBOARD_A,   KEYBOARD_D,   KEYBOARD_I,
        0x8101,  KEYBOARD_B,   KEYBOARD_F,   KEYBOARD_J,
        KEYBOARD_Left,  KEYBOARD_C,   KEYBOARD_J,   KEYBOARD_K,
        KEYBOARD_Right, KEYBOARD_D,   KEYBOARD_K,   KEYBOARD_L
    },
    {
        0x8000,    KEYBOARD_D,   KEYBOARD_D,   KEYBOARD_I,
        0x8100,  KEYBOARD_F,   KEYBOARD_F,   KEYBOARD_J,
        KEYBOARD_Left,  KEYBOARD_J,   KEYBOARD_J,   KEYBOARD_K,
        KEYBOARD_Right, KEYBOARD_K,   KEYBOARD_K,   KEYBOARD_L
    }
};
