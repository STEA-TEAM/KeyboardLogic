//
// Created by ParticleG on 2021/12/1.
//

#ifndef MATRIXKEYBOARD_KEYBOARD_BIND_H
#define MATRIXKEYBOARD_KEYBOARD_BIND_H

#include <stdint.h>

#define KEY_BIND_NUMBER 16
#define KEY_BIND_LAYER 1

extern uint8_t now_layer;
extern uint16_t Key_Bind[KEY_BIND_LAYER][KEY_BIND_NUMBER];

#endif //MATRIXKEYBOARD_KEYBOARD_BIND_H
