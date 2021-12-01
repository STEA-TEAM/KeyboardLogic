//
// Created by CafuuChino on 2021/11/23.
//

#include <stdlib.h>
#include "Keyboard_Keycode_Proccess.h"
#include "matrix_keyboard.h"
#include "universal_func.h"


void Key_Process_Init(){
}

void All_Code_List_Init(uint16_t* null_all_code_list_ptr){
    null_all_code_list_ptr = (uint16_t*)malloc(sizeof(uint16_t) * 1);
    null_all_code_list_ptr[0] = 0;
}


uint16_t* Key_Process(const uint8_t* Key_Pressed_Index,uint16_t* all_code_list){
    //count key_code number and add to all_code_list
    uint8_t keycode_list_size = 1;
    for (uint8_t i = 1; i <= Key_Pressed_Index[0]; i++){
        keycode_list_size += (Key_Bind[Key_Pressed_Index[i]] <= MACRO_CODE_MINIMUM || Key_Bind[Key_Pressed_Index[i]] >= MACRO_CODE_MAXIMUM);
    }
    uint16_t* keycode_list = (uint16_t*)malloc(sizeof(uint16_t)*keycode_list_size);
    keycode_list[0] = keycode_list_size;

    for (uint8_t i = 1; i <= Key_Pressed_Index[0]; i++){
        all_code_list[i] = Key_Bind[Key_Pressed_Index[i]];
    }
    all_code_list = MergeUint16Array(keycode_list, all_code_list);
    return all_code_list;
}
