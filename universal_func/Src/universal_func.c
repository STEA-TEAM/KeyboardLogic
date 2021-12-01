//
// Created by CafuuChino on 2021/11/30.
//

#include <malloc.h>
#include <memory.h>
#include "universal_func.h"


uint8_t in_range(uint16_t target, uint16_t minimum, uint16_t maximum) {
    if (target >= minimum && target <= maximum) return 0x01;
    return 0x00;
}

uint16_t elem_find(uint8_t elem, const uint8_t *source, uint16_t source_size, uint8_t begin_find_index) {
    for (uint16_t i = begin_find_index; i < source_size; i++) {
        if (source[i] == elem) return i + 1;
    }
    return 0x00;
}

uint8_t has_uint16(uint16_t code, const uint16_t* code_list, uint16_t begin, uint16_t end){
    //size of code_list is in code_list[0], so i begin with 1
    for(uint16_t i = begin; i < end; i++){
        if (code_list[i] == code) return 0x01;
    }
    return 0x00;
}

// TODO: Move these functions to STM32 specific folder
/*void SerialPrintUint8(uint8_t data){
    uint8_t rp[1] = {data};
    HAL_UART_Transmit(&huart1,rp,1,0xFFFF);
}

void SerialPrintUint16(uint16_t data){
    uint8_t rp[2] = {(uint8_t)(data>>8),(uint8_t)data};
    HAL_UART_Transmit(&huart1,rp,2,0xFFFF);
}

void SerialPrintStr(const char* str){
    HAL_UART_Transmit(&huart1,(uint8_t*)str,strlen(str),0xFFFF);
}

void SerialPrintUint8Array(const uint8_t* array,uint8_t begin_index,uint16_t size){
    HAL_UART_Transmit(&huart1,(uint8_t*)array+begin_index,size,0xFFFF);
    HAL_Delay(1);
}

void SerialPrintUint16Array(const uint16_t* array,uint8_t begin_index,uint16_t size){
    uint8_t hlb[2];
    for(uint16_t i = 0; i < size; i++){
        hlb[0] = (uint8_t)array[begin_index+i]>>8;
        hlb[1] = (uint8_t)array[begin_index+i];
        HAL_UART_Transmit(&huart1,hlb,2,0xffff);
    }
}*/

uint8_t* MergeUint8Array(uint8_t* source, uint8_t* target){
    uint8_t* new = NULL;
    if (!source[0]){
        free(source);
        return target;
    }
    else if((!target[0]) && source[0]){
        free(target);
        return source;
    }
    else{
        new = (uint8_t*)malloc(sizeof(uint8_t) * (1+source[0]+target[0]));
        new[0] = source[0] + target[0];
        memcpy(new+1, target, target[0]);
        memcpy(new+2+target[0], source, source[0]);
        free(source);
        free(target);
        return new;
    }

}

uint8_t* MergeLongUint8Array(uint8_t* source, uint16_t source_size,
                             uint8_t* target, uint16_t target_size){
    uint8_t* new = NULL;
    new = (uint8_t*)malloc(sizeof(uint8_t) * (source_size+target_size));
    memcpy(new, target, target[0]);
    memcpy(new+target_size+1, source, source_size);
    free(source);
    free(target);
    return new;
}

uint16_t* MergeUint16Array(uint16_t* source, uint16_t* target){
    uint16_t* new = NULL;
    if (!source[0]){
        free(source);
        return target;
    }
    else if((!target[0]) && source[0]){
        free(target);
        return source;
    }
    else{
        new = (uint16_t*)malloc(sizeof(uint16_t) * (1+source[0]+target[0]));
        new[0] = source[0] + target[0];
        memcpy(new+1, target, target[0]);
        memcpy(new+2+target[0], source, source[0]);
        free(source);
        free(target);
        return new;
    }

}

uint8_t* decode_Uint8reportPack(const uint8_t* reportPack){
    uint8_t* ret = (uint8_t*)malloc(sizeof(uint8_t) * (reportPack[0]+1));
    ret[0] = reportPack[0];
    uint16_t pt = 1;
    for(uint8_t i = 1; i <= reportPack[0]; i++){
        ret[i] = pt;
        pt += 1 + reportPack[pt];
    }
    return ret;
}

uint8_t* decode_Uint16reportPack(const uint16_t* reportPack){
    uint8_t* ret = (uint8_t*)malloc(sizeof(uint8_t) * (reportPack[0]+1));
    ret[0] = reportPack[0];
    uint16_t pt = 1;
    for(uint8_t i = 1; i <= reportPack[0]; i++){
        ret[i] = pt;
        pt += 1 + reportPack[pt];
    }
    return ret;
}