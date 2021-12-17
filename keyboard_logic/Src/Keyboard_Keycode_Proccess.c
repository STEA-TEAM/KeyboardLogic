//
// Created by CafuuChino on 2021/11/23.
//

#include <stdlib.h>
#include <memory.h>
#include "Keyboard_Bind.h"
#include "Keyboard_Keycode_Proccess.h"
#include "universal_func.h"

#include "SerialPrint.h"

uint8_t keep_index = 0;
uint8_t temp_index = 0;
uint8_t keep_index_flag = 0;
uint8_t temp_index_flag = 0;

void Key_Process_Init() {
}

uint16_t *All_Code_List_Init() {
    uint16_t *new_all_code_list;
    new_all_code_list = (uint16_t *) calloc(sizeof(uint16_t), 1);
    new_all_code_list[0] = 0x0000;
    return new_all_code_list;
}

uint8_t* Key_Pressed_Index_Filter(const uint8_t* Key_Pressed_Index){
    uint8_t no_keep = 1;
    uint8_t no_temp = 1;
    uint8_t* filter_ret = (uint8_t*)malloc(sizeof(uint8_t) * (Key_Pressed_Index[0]+4));
    uint8_t ki_ct[3] = {0,0,0}; //sysctl,keycode,macro
    for (uint8_t i = 1; i <= Key_Pressed_Index[0]; i++){
        if (!((keep_index_flag && (Key_Pressed_Index[i] == keep_index)) || (temp_index_flag && (Key_Pressed_Index[i] == temp_index)))){
            if (in_range(Key_Bind[now_layer][Key_Pressed_Index[i]], KEYCODE_MINIMUM, KEYCODE_MAXIMUM)){
                ki_ct[1] ++;
            }
            else if (in_range(Key_Bind[now_layer][Key_Pressed_Index[i]], SYSCTL_MINIMUM, SYSCTL_MAXIMUM)){
                ki_ct[0]++;
            }
            else if (in_range(Key_Bind[now_layer][Key_Pressed_Index[i]], MACRO_MINIMUM, MACRO_MAXIMUM)){
                ki_ct[2]++;
            }
        }
        else{
            if (Key_Pressed_Index[i] == keep_index){
                no_keep = 0;
            }
            else {
                no_temp = 0;
            }
        }
    }
    filter_ret[0] = 3;
    filter_ret[1] = ki_ct[0];
    filter_ret[2+ki_ct[0]] = ki_ct[1];
    filter_ret[3+ki_ct[0]+ki_ct[1]] = ki_ct[2];
    uint8_t fr_pt[3] = {1,1,1};
    for (uint8_t i = 1; i <= Key_Pressed_Index[0]; i++){
        if (!((keep_index_flag && (Key_Pressed_Index[i] == keep_index)) || (temp_index_flag && (Key_Pressed_Index[i] == temp_index)))){
            if (in_range(Key_Bind[now_layer][Key_Pressed_Index[i]], KEYCODE_MINIMUM, KEYCODE_MAXIMUM)) {
                filter_ret[2 + ki_ct[0] + fr_pt[1]] = Key_Pressed_Index[i];
                fr_pt[1]++;
            } else if (in_range(Key_Bind[now_layer][Key_Pressed_Index[i]], SYSCTL_MINIMUM, SYSCTL_MAXIMUM)) {
                filter_ret[1 + fr_pt[0]] = Key_Pressed_Index[i];
                fr_pt[0]++;
            } else if (in_range(Key_Bind[now_layer][Key_Pressed_Index[i]], MACRO_MINIMUM, MACRO_MAXIMUM)) {
                filter_ret[3 + ki_ct[0] + ki_ct[1] + fr_pt[2]] = Key_Pressed_Index[i];
                fr_pt[2]++;
            }
        }
    }
    if (no_keep){
        keep_index_flag = 0;
    }
    if (no_temp){
        temp_index_flag = 0;
    }
    return filter_ret;
}



void sysctl_command_handle(const uint8_t *Keycode_filter,uint8_t head){
    uint8_t keep_flag = 0;
    uint8_t temp_flag = 0;

    for (uint8_t i = 1; i <= Keycode_filter[head]; i++) {
        if (in_range(Key_Bind[now_layer][Keycode_filter[head+i]], SYSCTL_KEEP_CHANGE_LAYER_MINIMUM,
                     SYSCTL_KEEP_CHANGE_LAYER_MAXIMUM) && (!keep_flag)) {
            keep_flag = 1;
            keep_layer = (uint8_t) Key_Bind[now_layer][Keycode_filter[head+i]];

            keep_index = Keycode_filter[head+i];
            keep_index_flag = 1;

        } else if (in_range(Key_Bind[now_layer][Keycode_filter[head+i]], SYSCTL_TEMP_CHANGE_LAYER_MINIMUM,
                            SYSCTL_TEMP_CHANGE_LAYER_MAXIMUM)) {
            temp_flag = 1;
            temp_layer = (uint8_t) Key_Bind[now_layer][Keycode_filter[head+i]];

            temp_index = Keycode_filter[head+i];
            temp_index_flag = 1;
        }
    }
    if (temp_flag ||temp_index_flag){
        now_layer = temp_layer;
    }
    else{
        now_layer = keep_layer;
    }

}

uint16_t *KeyPress_to_KeyCode(const uint8_t *Key_Pressed_Index, uint16_t *all_code_list) {
    //count key_code number and add to all_code_list

    uint8_t keycode_list_count = 0;
    for (uint8_t i = 1; i <= Key_Pressed_Index[0]; i++) {
        keycode_list_count += (Key_Bind[now_layer][Key_Pressed_Index[i]] <= MACRO_CODE_MINIMUM ||
                               Key_Bind[now_layer][Key_Pressed_Index[i]] >= MACRO_CODE_MAXIMUM);
    }
    uint16_t *keycode_list = (uint16_t *) malloc(sizeof(uint16_t) * (keycode_list_count + 1));
    keycode_list[0] = keycode_list_count;

    for (uint8_t i = 1; i <= Key_Pressed_Index[0]; i++) {
        keycode_list[i] = Key_Bind[now_layer][Key_Pressed_Index[i]];
    }
    all_code_list = MergeUint16Array(keycode_list, all_code_list);
    return all_code_list;
}

uint16_t *KeyPress_to_KeyCode2(const uint8_t *Keycode_filter,uint8_t head, uint16_t *all_code_list){
    //count key_code number and add to all_code_list

    uint16_t *keycode_list = (uint16_t *) malloc(sizeof(uint16_t) * (Keycode_filter[head] + 1));
    keycode_list[0] = Keycode_filter[head];

    for (uint8_t i = 1; i <= Keycode_filter[head]; i++) {
        keycode_list[i] = Key_Bind[now_layer][Keycode_filter[head+i]];
    }
    all_code_list = MergeUint16Array(keycode_list, all_code_list);
    return all_code_list;
}
uint16_t *KeyCode_Remove_Redundent(uint16_t *all_code_list) {
    if (!all_code_list[0]) return all_code_list;
    uint16_t *buffer = NULL;
    buffer = (uint16_t *) malloc(sizeof(uint16_t) * all_code_list[0]);
    uint16_t ct = 0;
    for (uint16_t i = 1; i <= all_code_list[0]; i++) {
        if (!has_uint16(all_code_list[i], buffer, 0, ct)) {
            buffer[ct] = all_code_list[i];
            ct++;
        }
    }
    free(all_code_list);
    uint16_t *new_all_code_list = NULL;
    new_all_code_list = (uint16_t *) malloc(sizeof(uint16_t) * (ct + 1));
    new_all_code_list[0] = ct;
    memcpy(new_all_code_list + 1, buffer, sizeof(uint16_t) * ct);
    free(buffer);
    return new_all_code_list;
}