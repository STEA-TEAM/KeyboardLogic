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

/*Key Binding, just for matrix setting. Binding setting in */
/* None-Key Place filled with 0xFFFF*/
uint16_t Key_Bind[SCAN_OUTPUT_NUM*SCAN_INPUT_NUM] = {
        KEYBOARD_D, KEYBOARD_D, KEYBOARD_D, KEYBOARD_D,
        KEYBOARD_F, KEYBOARD_F, KEYBOARD_F, KEYBOARD_F,
        KEYBOARD_J, KEYBOARD_J, KEYBOARD_J, KEYBOARD_J,
        KEYBOARD_K, KEYBOARD_K, KEYBOARD_K, KEYBOARD_K
};


