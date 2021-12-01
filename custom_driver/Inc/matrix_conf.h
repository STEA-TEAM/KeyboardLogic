/*
 * matrix_conf.h
 *
 *  Created on: Nov 20, 2021
 *      Author: CafuuChino
 */

#ifndef MATRIX_CONF_H_
#define MATRIX_CONF_H_

#include <stm32f1xx_hal.h>

typedef struct GPIO_Package_def {
    GPIO_TypeDef *GPIO_Type;
    uint16_t GPIO_Num;
} GPIO_Package;

#define SCAN_INPUT_NUM 4
#define SCAN_OUTPUT_NUM 4

extern GPIO_Package Scan_InputGPIO[SCAN_INPUT_NUM];
extern GPIO_Package Scan_OutputGPIO[SCAN_OUTPUT_NUM];
extern uint16_t Key_Bind[SCAN_OUTPUT_NUM * SCAN_INPUT_NUM];

#endif /* MATRIX_CONF_H_ */