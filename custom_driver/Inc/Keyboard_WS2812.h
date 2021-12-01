/*
 * Keyboard_WS2812.h
 *
 *  Created on: Nov 20, 2021
 *      Author: CafuuChino
 */

#ifndef KEYBOARD_WS2812_H_
#define KEYBOARD_WS2812_H_

#include "WS2812_RGB.h"
#include "matrix_conf.h"

extern WS2812_Position Key_WS2812_Bind[SCAN_OUTPUT_NUM*SCAN_INPUT_NUM];
void KeyLight(const uint8_t* Key_Pressed_Index);

#endif /* KEYBOARD_WS2812_H_ */
