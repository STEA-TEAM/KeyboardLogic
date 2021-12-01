/*
 * matrix_keyboard.c
 *
 *  Created on: Nov 20, 2021
 *      Author: CafuuChino
 */

//include std library
#include <stdio.h>
#include <malloc.h>
//include global header
#include "main.h"
#include "universal_func.h"
//include functional header
#include "matrix_keyboard.h"
#include "matrix_conf.h"

//def global array
uint8_t Key_Status[JITTER_SCAN_FRAME + 1][SCAN_OUTPUT_NUM * SCAN_INPUT_NUM] = {};
//def global counter
uint8_t Key_Pressed_Count = 0;
uint8_t last_frame = 0;
uint8_t now_frame = 0;

void Matrix_Keyboard_Init() {
    //Zero key status
    for (uint8_t i = 0; i <= JITTER_SCAN_FRAME; i++) {
        for (uint8_t j = 0; j < SCAN_OUTPUT_NUM * SCAN_INPUT_NUM; j++) {
            Key_Status[i][j] = 0x00;
        }
    }
    //Reset Output GPIO
    for (uint8_t output_scan_init = 0; output_scan_init < SCAN_OUTPUT_NUM; output_scan_init++) {
        HAL_GPIO_WritePin(
                Scan_OutputGPIO[output_scan_init].GPIO_Type,
                Scan_OutputGPIO[output_scan_init].GPIO_Num,
                0x00);
    }
    //Initialize global var
    now_frame = 0;
    last_frame = JITTER_SCAN_FRAME;
}



void Matrix_Keyboard_Scan_Keys() {
    Key_Pressed_Count = 0;
    now_frame = last_frame;
    last_frame = (last_frame == JITTER_SCAN_FRAME ? 0 : (last_frame + 1));
    //Scan All Output GPIO
    for (uint8_t output_scan = 0; output_scan < SCAN_OUTPUT_NUM; output_scan++) {
        //Set Scan Output GPIO High
        HAL_GPIO_WritePin(
                Scan_OutputGPIO[output_scan].GPIO_Type,
                Scan_OutputGPIO[output_scan].GPIO_Num,
                0x01);
        //Read Input GPIO
        for (uint8_t input_scan = 0; input_scan < SCAN_INPUT_NUM; input_scan++) {
            Key_Status[now_frame][output_scan * SCAN_INPUT_NUM + input_scan] = HAL_GPIO_ReadPin(
                    Scan_InputGPIO[input_scan].GPIO_Type,
                    Scan_InputGPIO[input_scan].GPIO_Num);
        }
        //Reset Output GPIO to LOW
        HAL_GPIO_WritePin(
                Scan_OutputGPIO[output_scan].GPIO_Type,
                Scan_OutputGPIO[output_scan].GPIO_Num,
                0x00);
    }
}

uint8_t* Matrix_Keyboard_Comp_Keys(uint8_t *Key_Pressed_Index){
    //for removing JITTER by compare now_frame & last_frame
    Key_Pressed_Count = 0;
    //count Pressed Key for calloc size
    for (uint8_t comp_bit = 0; comp_bit < SCAN_INPUT_NUM * SCAN_OUTPUT_NUM; comp_bit++) {
        //both pressed in now_frame and last_frame
        Key_Pressed_Count += Key_Status[now_frame][comp_bit] && Key_Status[last_frame][comp_bit];
        Key_Pressed_Count += Key_Status[now_frame][comp_bit] && Key_Status[last_frame][comp_bit];
    }
    //calloc space for Inner_Key_Pressed_Index
    uint8_t* Inner_Key_Pressed_Index;
    Inner_Key_Pressed_Index = (uint8_t *) malloc(sizeof(uint8_t)* (Key_Pressed_Count + 1));
    Inner_Key_Pressed_Index[0] = Key_Pressed_Count;
    //add pressed key to Key_Pressed_index
    uint8_t ct = 1;
    for (uint8_t comp_bit = 0; comp_bit < SCAN_INPUT_NUM * SCAN_OUTPUT_NUM; comp_bit++) {
        if (Key_Status[now_frame][comp_bit] && Key_Status[last_frame][comp_bit]) {
            Inner_Key_Pressed_Index[ct] = comp_bit;
            ct++;
        }
    }
    Key_Pressed_Index = MergeUint8Array(Inner_Key_Pressed_Index,Key_Pressed_Index);
    return Key_Pressed_Index;
}

uint8_t *Matrix_Keyboard_Read_Keys(uint8_t *Key_Pressed_Index){
    Matrix_Keyboard_Scan_Keys();
    Key_Pressed_Index = Matrix_Keyboard_Comp_Keys(Key_Pressed_Index);
    return Key_Pressed_Index;
}

