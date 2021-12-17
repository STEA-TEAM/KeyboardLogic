//
// Created by CafuuChino on 2021/12/4.
//

#ifndef KEYBOARD_LOGIC_USB_HID_RECEIVE_H
#define KEYBOARD_LOGIC_USB_HID_RECEIVE_H

#include "main.h"
#include "usbd_custom_hid_if.h"
#include "SerialPrint.h"


extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t* USB_HID_Received(uint16_t size);

#endif //KEYBOARD_LOGIC_USB_HID_RECEIVE_H
