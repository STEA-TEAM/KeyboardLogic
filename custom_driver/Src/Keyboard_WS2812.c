/*
 * Keyboard_WS2812.c
 *
 *  Created on: Nov 20, 2021
 *      Author: CafuuChino
 */

#include "Keyboard_WS2812.h"
#include "WS2812_RGB.h"
#include "main.h"

/*Key WS2812 Address Binding*/
/* None-Key Place filled with {0xFF,0xFF}*/
WS2812_Position Key_WS2812_Bind[SCAN_OUTPUT_NUM * SCAN_INPUT_NUM] = {
        {0x00, 0x00},
        {0x00, 0x01},
        {0x00, 0x02},
        {0x00, 0x03},
        {0x00, 0x04},
        {0x00, 0x05},
        {0x00, 0x06},
        {0x00, 0x07},
        {0x00, 0x08},
        {0x00, 0x09},
        {0x00, 0x0A},
        {0x00, 0x0B},
        {0x00, 0x0C},
        {0x00, 0x0D},
        {0x00, 0x0E},
        {0x00, 0x0F}
};

void KeyLight(const uint8_t *Key_Pressed_Index) {
    WS2812_ResetAll();
    SerialPrintUint8(0xCC);
    SerialPrintUint8Array(Key_Pressed_Index, 0, Key_Pressed_Index[0] + 1);
    for (uint8_t i = 1; i <= Key_Pressed_Index[0]; i++) {
        WS2812_SetColor(&Key_WS2812_Bind[Key_Pressed_Index[i]], 0xFF, 0xFF, 0xFF);
    }
    WS2812_Update();
}
