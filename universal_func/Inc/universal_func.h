//
// Created by CafuuChino on 2021/11/30.
//

#ifndef KEYBOARDLOGIC_UNIVERSAL_FUNC_H
#define KEYBOARDLOGIC_UNIVERSAL_FUNC_H

#endif //KEYBOARDLOGIC_UNIVERSAL_FUNC_H

#include <stdint.h>

uint8_t in_range(uint16_t target, uint16_t minimum, uint16_t maximum);

uint16_t elem_find(uint8_t elem, const uint8_t *source, uint16_t source_size, uint16_t begin_find_index);

uint8_t has_uint8(uint8_t code, const uint8_t *code_list, uint16_t begin, uint16_t end);

uint8_t has_uint16(uint16_t code, const uint16_t *code_list, uint16_t begin, uint16_t end);

uint8_t key_status_cmp(const uint8_t *cmp_key_status_now, const uint8_t *cmp_Keyboard_Last_Key_Status);

uint8_t array_cmp(const uint8_t* arr1, const uint8_t* arr2, uint16_t cmp_size);

uint8_t *MergeUint8Array(uint8_t *source, uint8_t *target);

uint8_t *MergeLongUint8Array(uint8_t *source, uint16_t source_size,
                             uint8_t *target, uint16_t target_size);

uint16_t *MergeUint16Array(uint16_t *source, uint16_t *target);

uint8_t *decode_Uint8reportPack(const uint8_t *reportPack);

uint16_t *decode_Uint16reportPack(const uint16_t *reportPack);

