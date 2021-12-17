/*
 * matrix_keyboard.h
 *
 *  Created on: Nov 20, 2021
 *      Author: CafuuChino
 */

#ifndef INC_MATRIX_KEYBOARD_H_
#define INC_MATRIX_KEYBOARD_H_

#include "hardware_structure_define.h"



#define SCAN_INPUT_NUM 4
#define SCAN_OUTPUT_NUM 4

//#define SCAN_INTERVAL 1U
#define JITTER_SCAN_FRAME 1U //do not set a large number!Jitter Time is in FRAME Unit, Per Frame Time is SCAN_INVERVAL(ms)



extern uint8_t Key_Status[JITTER_SCAN_FRAME + 1][SCAN_OUTPUT_NUM * SCAN_INPUT_NUM];

extern uint8_t last_frame;
extern uint8_t now_frame;

void Matrix_Keyboard_Init();

void Matrix_Keyboard_Scan_Keys();

uint8_t *Matrix_Keyboard_Comp_Keys(uint8_t *Key_Pressed_Index);

uint8_t *Matrix_Keyboard_Read_Keys(uint8_t *Key_Pressed_Index);

#endif /* INC_MATRIX_KEYBOARD_H_ */
