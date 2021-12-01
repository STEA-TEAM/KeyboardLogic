/*
 * matrix_conf.c
 *
 *  Created on: Nov 20, 2021
 *      Author: CafuuChino
 */

#include "matrix_conf.h"

GPIO_Package Scan_InputGPIO[SCAN_INPUT_NUM] = {
        {GPIOA,GPIO_PIN_0},
        {GPIOA,GPIO_PIN_1},
        {GPIOA,GPIO_PIN_2},
        {GPIOA,GPIO_PIN_3}
};

GPIO_Package Scan_OutputGPIO[SCAN_OUTPUT_NUM] = {
        {GPIOA,GPIO_PIN_8},
        {GPIOB,GPIO_PIN_8},
        {GPIOB,GPIO_PIN_9},
        {GPIOB,GPIO_PIN_10}
};


