/*
 * WS2812_RGB.h
 *
 *  Created on: Nov 20, 2021
 *      Author: CafuuChino
 */

#ifndef WS2812_RGB_H_
#define WS2812_RGB_H_

#include "stm32f1xx_hal.h"

#define WS2812_STRIP_NUM 1

extern uint8_t *WS2812_RGB_StatusPtrList[WS2812_STRIP_NUM];
extern uint8_t WS2812_LED_NUM[WS2812_STRIP_NUM];
extern SPI_HandleTypeDef *WS2812_SPI_Conf[WS2812_STRIP_NUM];

typedef struct {
    uint8_t strip_index;
    uint8_t led_addr;
} WS2812_Position;

void WS2812_Init();

void WS2812_SetColor(WS2812_Position *position, uint8_t R, uint8_t G, uint8_t B);

void WS2812_Update();

void WS2812_ResetAll();

uint8_t WS2812_ValidPosition(WS2812_Position *pos_struct);

#define WS2812_H 0b01111000
#define WS2812_L 0b01100000

#endif /* WS2812_RGB_H_ */
