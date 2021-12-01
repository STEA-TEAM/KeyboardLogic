//
// Created by CafuuChino on 2021/11/30.
//

#ifndef KEYBOARDLOGIC_UNIVERSAL_FUNC_H
#define KEYBOARDLOGIC_UNIVERSAL_FUNC_H

#endif //KEYBOARDLOGIC_UNIVERSAL_FUNC_H

#include <stdint.h>

uint8_t in_range(uint16_t target, uint16_t minimum, uint16_t maximum);
uint16_t elem_find(uint8_t elem, const uint8_t *source, uint16_t source_size, uint8_t begin_find_index);
uint8_t has_uint16(uint16_t code, const uint16_t* code_list, uint16_t begin, uint16_t end);

uint8_t key_status_comp(const uint8_t *cmp_key_status_now, const uint8_t *cmp_Keyboard_Last_Key_Status);

// TODO: Move these functions to STM32 specific folder
/*void SerialPrintUint8(uint8_t data);
void SerialPrintUint16(uint16_t data);
void SerialPrintStr(const char* str);
void SerialPrintUint8Array(const uint8_t* array,uint8_t begin_index,uint16_t size);
void SerialPrintUint16Array(const uint16_t* array,uint8_t begin_index,uint16_t size);*/

uint8_t* MergeUint8Array(uint8_t* source, uint8_t* target);
uint8_t* MergeLongUint8Array(uint8_t* source, uint16_t source_size,
                             uint8_t* target, uint16_t target_size);
uint16_t* MergeUint16Array(uint16_t* source, uint16_t* target);

uint8_t* decode_Uint8reportPack(const uint8_t* reportPack);
uint8_t* decode_Uint16reportPack(const uint16_t* reportPack);
