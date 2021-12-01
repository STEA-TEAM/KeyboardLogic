//
// Created by CafuuChino on 2021/11/23.
//

#include <stdlib.h>
#include <memory.h>
#include "Keyboard_Keycode_Proccess.h"
#include "matrix_keyboard.h"
#include "universal_func.h"


void Key_Process_Init(){
}

uint16_t* All_Code_List_Init(){
    uint16_t *new_all_code_list;
    new_all_code_list = (uint16_t*)calloc(sizeof(uint16_t) , 1);
    new_all_code_list[0] = 0x0000;
    return new_all_code_list;
}


uint16_t* KeyPress_to_KeyCode(const uint8_t* Key_Pressed_Index, uint16_t* all_code_list){
    //count key_code number and add to all_code_list

    uint8_t keycode_list_count = 0;
    for (uint8_t i = 1; i <= Key_Pressed_Index[0]; i++){
        keycode_list_count += (Key_Bind[Key_Pressed_Index[i]] <= MACRO_CODE_MINIMUM || Key_Bind[Key_Pressed_Index[i]] >= MACRO_CODE_MAXIMUM);
    }
    uint16_t* keycode_list = (uint16_t*)malloc(sizeof(uint16_t)*(keycode_list_count+1));
    keycode_list[0] = keycode_list_count;

    for (uint8_t i = 1; i <= Key_Pressed_Index[0]; i++){
        keycode_list[i] = Key_Bind[Key_Pressed_Index[i]];
    }
    all_code_list = MergeUint16Array(keycode_list, all_code_list);
    return all_code_list;
}

uint16_t* KeyCode_Remove_Redundent(uint16_t* all_code_list){
    if (!all_code_list[0]) return all_code_list;
    uint16_t* buffer = NULL;
    buffer = (uint16_t*)malloc(sizeof(uint16_t) * all_code_list[0]);
    uint16_t ct = 0;
    for(uint16_t i = 1; i <= all_code_list[0]; i++){
        if (!has_uint16(all_code_list[i], buffer, 0, ct)){
            buffer[ct] = all_code_list[i];
            ct ++;
        }
    }
    free(all_code_list);
    uint16_t* new_all_code_list = NULL;
    new_all_code_list = (uint16_t*)malloc(sizeof(uint16_t) * (ct+1));
    new_all_code_list[0] = ct;
    memcpy(new_all_code_list+1, buffer, sizeof(uint16_t) * ct);
    free(buffer);
    return new_all_code_list;
}