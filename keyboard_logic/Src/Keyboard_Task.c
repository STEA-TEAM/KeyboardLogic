//
// Created by CafuuChino on 2021/11/23.
//

//include standard libraries
#include <stdlib.h>
#include <stdio.h>
//include logical functions
#include "universal_func.h"
#include "Keyboard_Task.h"
#include "Keyboard_Physical_Detect.h"
#include "Keyboard_Keycode_Proccess.h"
#include "Keyboard_Report_Send.h"
//include hardware drivers
#include "USB_Send.h"
#include "Keyboard_WS2812.h"
#include "WS2812_RGB.h"
#include "matrix_keyboard.h"


void Keyboard_Init() {
    //WS2812_Init();
    Matrix_Keyboard_Init();
    USB_Keyboard_Send_Init();
    Key_Process_Init();
}

void Keyboard_Begin_Loop() {

}

uint8_t *Keyboard_Phycial_Detect(uint8_t *Key_Pressed_Index) {
    /*
     * You can add any kinds of physical keys
     * Just append Key Pressed Index and change matrix_conf.c/.h for keycode binding
     * Every handler merge their own Key_Pressed_Index into Global Key_Pressed_Index
     * by using MergeUint8Array() in "universal_func.h"
     * Key index is the index you bind your keys in matrix_conf.c/.h
     */
    //Key_Pressed_Index init as size 1 array
    Key_Pressed_Index_Init(Key_Pressed_Index);

    Key_Pressed_Index = Matrix_Keyboard_Read_Keys(Key_Pressed_Index);

    return Key_Pressed_Index;
}

uint16_t *Keyboard_Keycode_Process(uint8_t *Key_Pressed_Index,
                                   uint16_t *all_code_list) {
    //all_code_list is NULL

    //init all_code_list
    All_Code_List_Init(all_code_list);
    //handle Keyboard code in Key_Pressed_Index and add to all_code_list
    all_code_list = Key_Process(Key_Pressed_Index, all_code_list);
    return all_code_list;
}

void Keyboard_Report_Send(uint16_t *all_code_list) {

    uint16_t *filter_ret = NULL;

    filter_ret = Keycode_Filter(all_code_list);
    //decode filter array to each kind of keycode header index
    //report_head[6] is {5,kbd,ms,cc,sc,rhid}
    uint8_t *report_head = NULL;
    report_head = decode_Uint16reportPack(filter_ret);

    //handle Keyboard Report;
    uint8_t *KeyboardReport = NULL;
    KeyboardReport = USB_HID_Keyboard_Code_Process(filter_ret, report_head[1]);
    USB_HID_SendReport(KeyboardReport);
    free(KeyboardReport);

    free(report_head);
    free(filter_ret);

}

void Keyboard_End_Loop() {

}

//Keyboard Logical Loop
void Keyboard_Logic_Loop() {
    uint8_t *Key_Pressed_Index = NULL;
    uint16_t *All_Code = NULL;

    Keyboard_Begin_Loop();

    Key_Pressed_Index = Keyboard_Phycial_Detect(Key_Pressed_Index);

    All_Code = Keyboard_Keycode_Process(Key_Pressed_Index, All_Code);
    free(Key_Pressed_Index);

    Keyboard_Report_Send(All_Code);
    free(All_Code);

    Keyboard_End_Loop();
}