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

#ifdef IS_STM32
//include hardware drivers
#include "USB_Send.h"
#include "Keyboard_WS2812.h"
#include "WS2812_RGB.h"
#include "matrix_keyboard.h"
#include "usbd_custom_hid_if.h"

#endif

void Keyboard_Init() {
#ifdef IS_STM32
    WS2812_Init();
    Matrix_Keyboard_Init();
    USB_Keyboard_Send_Init();
    Key_Process_Init();
#endif
}

void Keyboard_Begin_Loop() {

}

uint8_t *Keyboard_Physical_Detect(uint8_t *Key_Pressed_Index) {
    /*
     * You can add any kinds of physical keys
     * Just append Key Pressed Index and change matrix_conf.c/.h for keycode binding
     * Every handler merge their own Key_Pressed_Index into Global Key_Pressed_Index
     * by using MergeUint8Array() in "universal_func.h"
     * Key index is the index you bind your keys in matrix_conf.c/.h
     */
    //Key_Pressed_Index init as size 1 array
    Key_Pressed_Index = Key_Pressed_Index_Init();
#ifdef IS_STM32
    Key_Pressed_Index = Matrix_Keyboard_Read_Keys(Key_Pressed_Index);
#else
    uint8_t testKeyList[8];
    testKeyList[0] = 0;
    testKeyList[1] = 2;
    testKeyList[2] = 4;
    testKeyList[3] = 6;
    testKeyList[4] = 8;
    testKeyList[5] = 10;
    testKeyList[6] = 12;
    testKeyList[7] = 14;

    Key_Pressed_Index = MergeUint8Array(testKeyList, Key_Pressed_Index);
#endif
    return Key_Pressed_Index;
}

uint16_t *Keyboard_Keycode_Process(uint8_t *Key_Pressed_Index,
                                   uint16_t *all_code_list) {
    //all_code_list is NULL

    //init all_code_list

    all_code_list = All_Code_List_Init();
    //handle Keyboard code in Key_Pressed_Index and add to all_code_list
    //add Keyboard_WS2812
    KeyLight(Key_Pressed_Index);


    uint8_t* filter_ret = NULL;
    filter_ret = Key_Pressed_Index_Filter(Key_Pressed_Index);

    uint8_t* filter_head = NULL;
    filter_head = decode_Uint8reportPack(filter_ret);
//    SerialPrintUint8(0xCC);
//    SerialPrintUint8Array(filter_ret,0,16);
//    SerialPrintUint8(0xDD);
//    SerialPrintUint8Array(filter_head,0,3);
    sysctl_command_handle(filter_ret,filter_head[1+0]);

    all_code_list = KeyPress_to_KeyCode2(filter_ret, filter_head[1+1], all_code_list);

    free(filter_ret);
    free(filter_head);
    all_code_list = KeyCode_Remove_Redundent(all_code_list);

    return all_code_list;
}

void Keyboard_Report_Send(uint16_t *all_code_list) {

    uint16_t *filter_ret = NULL;
    filter_ret = Keycode_Filter(all_code_list);
    //decode filter array to each kind of keycode header index
    //report_head[6] is {5,kbd,ms,cc,sc,rhid}
#ifdef IS_STM32
    uint16_t *report_head = NULL;
    report_head = decode_Uint16reportPack(filter_ret);
    //handle Keyboard Report;
    uint8_t *KeyboardReport = NULL;
    KeyboardReport = USB_HID_Keyboard_Code_Process(filter_ret, report_head[1]);
    USB_HID_SendReport(KeyboardReport);
    free(KeyboardReport);
    free(report_head);
#else
    printf("all_code_list: ");
    for (uint16_t i = 1; i <= all_code_list[0]; i++) {
        printf("%02X ", all_code_list[i]);
    }
    printf("\n");
#endif
    free(filter_ret);
}

void Keyboard_End_Loop() {
    HAL_Delay(1);
}

//Keyboard Logical Loop
void Keyboard_Logic_Loop() {

    uint8_t *Key_Pressed_Index = NULL;
    uint16_t *All_Code = NULL;
    Keyboard_Begin_Loop();

    Key_Pressed_Index = Keyboard_Physical_Detect(Key_Pressed_Index);

    All_Code = Keyboard_Keycode_Process(Key_Pressed_Index, All_Code);
    free(Key_Pressed_Index);
    Keyboard_Report_Send(All_Code);
    free(All_Code);
    Keyboard_End_Loop();


//    uint8_t DR1[8] = {0x01,0x04,0x05,0x06,0x07,0x08,0x09,0x0A};
//    uint8_t DR2[8] = {0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//    uint8_t ER1[15] = {0x02,0x00};
//    uint8_t ER2[15] = {0x02,0x01};
//    uint8_t ER3[15] = {0x02,0x80};


}