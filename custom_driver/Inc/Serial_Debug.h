//
// Created by CafuuChino on 2021/12/2.
//

#ifndef KEYBOARD_LOGIC_SERIALDEBUG_H
#define KEYBOARD_LOGIC_SERIALDEBUG_H

#include "main.h"

void SerialPrintUint8(uint8_t data);
void SerialPrintUint16(uint16_t data);
void SerialPrintStr(const char* str);
void SerialPrintUint8Array(const uint8_t* array,uint8_t begin_index,uint16_t size);
void SerialPrintUint16Array(const uint16_t* array,uint8_t begin_index,uint16_t size);

#endif //KEYBOARD_LOGIC_SERIALDEBUG_H
