//
// Created by CafuuChino on 2021/12/17.
//

#ifndef KEYBOARD_LOGIC_HARDWARE_STRUCTURE_DEFINE_H
#define KEYBOARD_LOGIC_HARDWARE_STRUCTURE_DEFINE_H
#include <stm32f1xx_hal.h>

typedef struct GPIO_Package_def {
    GPIO_TypeDef *GPIO_Type;
    uint16_t GPIO_Num;
} GPIO_Package;





#endif //KEYBOARD_LOGIC_HARDWARE_STRUCTURE_DEFINE_H
