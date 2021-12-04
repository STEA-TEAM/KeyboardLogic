//
// Created by CafuuChino on 2021/12/4.
//

#include "USB_receive.h"

USBD_CUSTOM_HID_HandleTypeDef *hhid;

/*
 * Using in Task Proc:
    uint8_t* ret = NULL;
    size = 65 //HID_Report ID:06 Report Size
    if (HID_OutCompleteFlag){
        ret = USB_HID_Received(size);
    }
    HID_OutCompleteFlag = 0;
*/

uint8_t* USB_HID_Received(uint16_t size){
    uint8_t* HID_ReceiveBuffer = NULL;
    HID_ReceiveBuffer = (uint8_t*)malloc(sizeof(uint8_t) * size);
    hhid = (USBD_CUSTOM_HID_HandleTypeDef*)hUsbDeviceFS.pClassData;
    for (uint16_t i = 0; i < size; i++){
        HID_ReceiveBuffer[i] = hhid->Report_buf[i];
    }
    SerialPrintUint8(0xAA);
    SerialPrintUint8Array(HID_ReceiveBuffer,0,size);
    return HID_ReceiveBuffer;
}