//
// Created by CafuuChino on 2021/11/23.
//
#ifndef MATRIXKEYBOARD_KEY_PROCESS_H
#define MATRIXKEYBOARD_KEY_PROCESS_H

#include <stdint.h>

#define KEYBOARD_CODE_MINIMUM 0x01
#define KEYBOARD_CODE_MAXIMUM 0xE7

#define MOUSE_CODE_MINIMUM 0x0100
#define MOUSE_CODE_MAXIMUM 0x0FFF

#define CUSTOM_CONTROL_CODE_MINIMUM 0x1000
#define CUSTOM_CONTROL_CODE_MAXIMUM 0x1FFF

#define SYSTEM_CONTROL_CODE_MINIMUM 0x2000
#define SYSTEM_CONTROL_CODE_MAXIMUM 0x2FFF

#define MACRO_CODE_MINIMUM 0x3000
#define MACRO_CODE_MAXIMUM 0x3FFF

#define RAW_HID_REPORT_CODE_MINIMUM 0x4000
#define RAW_HID_REPORT_CODE_MAXIMUM 0x4FFF


void Key_Process_Init();
uint16_t* All_Code_List_Init();
uint16_t* KeyPress_to_KeyCode(const uint8_t* Key_Pressed_Index, uint16_t* all_code_list);
uint16_t* KeyCode_Remove_Redundent(uint16_t* all_code_list);

#endif //MATRIXKEYBOARD_KEY_PROCESS_H
