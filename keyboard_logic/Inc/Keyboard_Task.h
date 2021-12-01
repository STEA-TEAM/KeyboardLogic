//
// Created by CafuuChino on 2021/11/23.
//

#ifndef MATRIXKEYBOARD_KEYBOARD_PROC_H
#define MATRIXKEYBOARD_KEYBOARD_PROC_H

#include <stdint-gcc.h>

void Keyboard_Init();

void Keyboard_Begin_Loop();

uint8_t *Keyboard_Physical_Detect(uint8_t *Key_Pressed_Index);

uint16_t *Keyboard_Keycode_Process(
        uint8_t *Key_Pressed_Index,
        uint16_t *all_code_list
);

void Keyboard_Report_Send(uint16_t *all_code_list);

void Keyboard_End_Loop();

void Keyboard_Logic_Loop();

#endif //MATRIXKEYBOARD_KEYBOARD_PROC_H
