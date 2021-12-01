//
// Created by CafuuChino on 2021/12/2.
//

#include "Serial_Debug.h"
#include <memory.h>

void SerialPrintUint8(uint8_t data){
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
}