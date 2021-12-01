/*
 * USB_Keyboard_Send.c
 *
 *  Created on: Nov 22, 2021
 *      Author: CafuuChino
 */

//include standard library
#include <stdlib.h>
//include universal library
#include "universal_func.h"
//include functional library
#include "Keyboard_Report_Send.h"
#include "Keyboard_Keycode_Proccess.h"
//include driver library



uint16_t* Keycode_Filter(uint16_t *all_code_list) {

    uint16_t* ret;

    uint8_t keycode_size[5] = {0,0,0,0,0};
    //all kinds of key counting
    for (uint16_t i = 1; i <= all_code_list[0]; i++) {
        if (in_range(all_code_list[i], KEYBOARD_CODE_MINIMUM, KEYBOARD_CODE_MAXIMUM)) {
            keycode_size[0]++;
        } else if (in_range(all_code_list[i], MOUSE_CODE_MINIMUM, MOUSE_CODE_MAXIMUM)) {
            keycode_size[1]++;
        } else if (in_range(all_code_list[i], CUSTOM_CONTROL_CODE_MINIMUM, CUSTOM_CONTROL_CODE_MAXIMUM)) {
            keycode_size[2]++;
        } else if (in_range(all_code_list[i], SYSTEM_CONTROL_CODE_MINIMUM, SYSTEM_CONTROL_CODE_MAXIMUM)) {
            keycode_size[3]++;
        } else if (in_range(all_code_list[i], RAW_HID_REPORT_CODE_MINIMUM, RAW_HID_REPORT_CODE_MAXIMUM)) {
            keycode_size[4]++;
        } else {}
    }

    uint8_t ret_size = 1 + 5 +
                    keycode_size[0] +
                    keycode_size[1] +
                    keycode_size[2] +
                    keycode_size[3] +
                    keycode_size[4];

    ret = (uint16_t*)calloc(sizeof(uint16_t), ret_size);
    //0s---s---s---s---s---
    //0 1 2+s1 3+s1+s2 4+s1+s2+s3 5+s1+s2+s3+s4

    uint8_t ret_pt[5] = {1,
                         2+keycode_size[0],
                         3+keycode_size[0]+keycode_size[1],
                         4+keycode_size[0]+keycode_size[1]+keycode_size[2],
                         5+keycode_size[0]+keycode_size[1]+keycode_size[2]+keycode_size[3]};

    ret[0] = 5;
    ret[ret_pt[0]] = keycode_size[0];
    ret[ret_pt[1]] = keycode_size[1];
    ret[ret_pt[2]] = keycode_size[2];
    ret[ret_pt[3]] = keycode_size[3];
    ret[ret_pt[4]] = keycode_size[4];




    uint8_t count[5] = {1, 1, 1, 1, 1};
    for (uint16_t i = 1; i <= all_code_list[0]; i++) {
        if (in_range(all_code_list[i], KEYBOARD_CODE_MINIMUM, KEYBOARD_CODE_MAXIMUM)) {
            ret[ret_pt[0]+count[0]] = (uint8_t) all_code_list[i];
            count[0]++;
        } else if (in_range(all_code_list[i], MOUSE_CODE_MINIMUM, MOUSE_CODE_MAXIMUM)) {
            ret[ret_pt[1]+count[1]] = all_code_list[i];
            count[1]++;
        } else if (in_range(all_code_list[i], CUSTOM_CONTROL_CODE_MINIMUM, CUSTOM_CONTROL_CODE_MAXIMUM)) {
            ret[ret_pt[2]+count[2]] = all_code_list[i];
            count[2]++;
        } else if (in_range(all_code_list[i], SYSTEM_CONTROL_CODE_MINIMUM, SYSTEM_CONTROL_CODE_MAXIMUM)) {
            ret[ret_pt[3]+count[3]] = all_code_list[i];
            count[3]++;
        } else if (in_range(all_code_list[i], RAW_HID_REPORT_CODE_MINIMUM, RAW_HID_REPORT_CODE_MAXIMUM)) {
            ret[ret_pt[4]+count[4]] = all_code_list[i];
            count[4]++;
        } else {}
    }

    return ret;

}


