//
// Created by CafuuChino on 2021/12/1.
//

#include "Keyboard_Physical_Detect.h"
#include "malloc.h"

uint8_t* Key_Pressed_Index_Init(){
    uint8_t *new_Key_Pressed_Index = NULL;
    new_Key_Pressed_Index = (uint8_t*)malloc(sizeof(uint8_t) * 1);
    new_Key_Pressed_Index[0] = 0;
    return new_Key_Pressed_Index;
}