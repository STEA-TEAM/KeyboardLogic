//
// Created by ParticleG on 2021/12/1.
//

#include "Keyboard_Bind.h"

/*Key Binding, just for matrix setting. Binding setting in */
/* None-Key Place filled with 0xFFFF*/
uint16_t Key_Bind[SCAN_OUTPUT_NUM * SCAN_INPUT_NUM] = {
        KEYBOARD_D, KEYBOARD_D, KEYBOARD_D, KEYBOARD_D,
        KEYBOARD_F, KEYBOARD_F, KEYBOARD_F, KEYBOARD_F,
        KEYBOARD_J, KEYBOARD_J, KEYBOARD_J, KEYBOARD_J,
        KEYBOARD_K, KEYBOARD_K, KEYBOARD_K, KEYBOARD_K
};
