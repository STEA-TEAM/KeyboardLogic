//
// Created by CafuuChino on 2021/12/1.
//

#include "USB_Send.h"
#include "universal_func.h"
#include "main.h"
#include "usbd_custom_hid_if.h"

void USB_HID_SendReport(uint8_t *HID_Report) {
    uint16_t pt = 0;
    if (HID_Report) {
        uint8_t total_report = HID_Report[pt];
        pt++;
        for (uint8_t i = 0; i < total_report; i++) {
            USBD_CUSTOM_HID_SendReport_FS(HID_Report + pt + 1, HID_Report[pt]);
            pt += HID_Report[pt] + 1;
        }
    }
}

//using to compare with new Key Status to calculate the report need to be changed
uint8_t *Keyboard_Last_Key_Status = NULL;

uint8_t *Keyboard_HID_Report = NULL;
uint8_t *EX_Keyboard1_HID_Report = NULL;

//using to compare with new EX_kbd_report to decide sending new EX_kbd_report
uint8_t *Last_Keyboard_HID_Report = NULL;
//using to compare with new EX_kbd_report to decide sending new EX_kbd_report
uint8_t *LastEX_Keyboard1_HID_Report = NULL;

//Key_Bit_Set is uint64 that stores Keyboard Key Status form Code 0x00 to 0x7F
//All changes are on Key_Bit_Set,when sending report,report will be summonned by Key_Bit_Set data
uint64_t Key_Bit_Set_HSB = 0;
uint64_t Key_Bit_Set_LSB = 0;
uint64_t Key_Bit_Set_Mask = 0x7FFFFFFFFFFFFFFF; //0b0111...111 (64bit)

void Key_Bit_Set_Update(uint64_t* HSB,
                        uint64_t* LSB,
                        uint8_t key_code,
                        uint8_t bit_status){
    if (key_code < 0x40) *HSB = (*HSB & (Key_Bit_Set_Mask >> key_code)) | (((uint64_t)bit_status) << (0x3F-key_code));
    else if (key_code >= 0x40) *LSB = (*LSB & (Key_Bit_Set_Mask >> (key_code - 0x40))) | (((uint64_t)bit_status) << (0x7F-key_code));
}


void get_Key_Bit_Set(const uint64_t *HSB,
                     const uint64_t *LSB,
                     uint8_t KeyCode_Begin,
                     uint8_t* ret,
                     uint8_t size) {
    uint8_t begin_pt = KeyCode_Begin;
    for (uint8_t ct = 0; ct < size; ct++) {
        //ct is ret index
        //this byte is all in HSB
        if (begin_pt + 8 <= 0x40) {

            ret[ct] = (uint8_t) *HSB >> (0x3F - begin_pt - 7);
        } else if (begin_pt >= 0x40) {
            //---dddddddd-----
            //0--bdddddddn---(7f)
            ret[ct] = (uint8_t) *LSB >> (0x7F - begin_pt - 7);
        } else {

            ret[ct] = (uint8_t) (*HSB << (begin_pt + 7 - 0x3F) | (*LSB >> 56 & (0xFF >> (0x40 - begin_pt))));
        }
    }
}

uint8_t key_status_comp(const uint8_t *cmp_key_status_now, const uint8_t *cmp_Keyboard_Last_Key_Status) {
    if (cmp_key_status_now[0] == cmp_Keyboard_Last_Key_Status[0]) {
        for (uint8_t i = 1; i < cmp_key_status_now[0]; i++) {
            if (!elem_find(cmp_key_status_now[i],
                           cmp_Keyboard_Last_Key_Status,
                           cmp_Keyboard_Last_Key_Status[0],
                           1)) {
                return 0x00;
            }
        }
        return 0x01;
    } else {
        return 0x00;
    }
}



void USB_Keyboard_Send_Init() {
    Keyboard_HID_Report = (uint8_t *) calloc(sizeof(uint8_t), HID_DEFAULT_KEYBOARD_REPORT_SIZE);
    Last_Keyboard_HID_Report = (uint8_t *) calloc(sizeof(uint8_t), HID_DEFAULT_KEYBOARD_REPORT_SIZE);

    EX_Keyboard1_HID_Report = (uint8_t *) calloc(sizeof(uint8_t), HID_EX_KEYBOARD1_REPORT_SIZE);
    LastEX_Keyboard1_HID_Report = (uint8_t *) calloc(sizeof(uint8_t), HID_EX_KEYBOARD1_REPORT_SIZE);

    Keyboard_HID_Report[0] = HID_DEFAULT_KEYBOARD_REPORT_ID;
    EX_Keyboard1_HID_Report[0] = HID_EX_KEYBOARD1_REPORT_ID;

    Keyboard_Last_Key_Status = (uint8_t *) calloc(sizeof(uint8_t), 1);
    Keyboard_Last_Key_Status[0] = 0x00;
}


uint8_t* USB_HID_Keyboard_Code_Process(const uint16_t* filter_ret, uint8_t head) {

    //get Keyboard code from filter_ret
    uint8_t Keyboard_Keycode[filter_ret[head]+1];
    Keyboard_Keycode[0] = filter_ret[head];
    for (uint8_t i = 1; i <= filter_ret[head]; i++){
        Keyboard_Keycode[i] = (uint8_t)filter_ret[head+i];
    }

    uint8_t *ret;
    //handle assistant keys
    if (!key_status_comp(Keyboard_Keycode, Keyboard_Last_Key_Status)) {
        /*
         * assistant keys always update in Default Keyboard Report Byte 2
         * assistant keys will never in new_release and new_press
         */
        for (uint8_t i = 1; i <= Keyboard_Keycode[0]; i++) {
            if (in_range(Keyboard_Keycode[i], KEYBOARD_LeftControl, KEYBOARD_RightGUI)) {
                Keyboard_HID_Report[1] |= 0b10000000 >> (Keyboard_Keycode[i] - 0xE0);
            }
        }

        //find new_press and new_release

        uint8_t new_press[Keyboard_Keycode[0]];
        uint8_t new_release[Keyboard_Last_Key_Status[0]];

        //count new releasing key number
        uint8_t new_release_size = 0;
        for (uint8_t i = 1; i <= Keyboard_Last_Key_Status[0]; i++) {
            if (!(elem_find(Keyboard_Last_Key_Status[i], Keyboard_Keycode, Keyboard_Keycode[0] + 1, 1)
                  | in_range(Keyboard_Last_Key_Status[i],KEYBOARD_LeftControl,KEYBOARD_RightGUI))) {
                new_release[new_release_size] = Keyboard_Last_Key_Status[i];
                new_release_size++;
            }
        }

        //count new pressing key number
        uint8_t new_press_size = 0;
        for (uint8_t i = 1; i <= Keyboard_Keycode[0]; i++) {
            if (!(elem_find(Keyboard_Keycode[i], Keyboard_Last_Key_Status, Keyboard_Last_Key_Status[0] + 1, 1)
                  | in_range(Keyboard_Last_Key_Status[i],KEYBOARD_LeftControl,KEYBOARD_RightGUI))) {
                new_press[new_press_size] = Keyboard_Keycode[i];
                new_press_size++;
            }
        }

        //clear new_press in Default Keyboard
        for (uint8_t i = 0; i < new_release_size; i++) {
            uint8_t place = elem_find(new_release[i], Keyboard_HID_Report, HID_DEFAULT_KEYBOARD_REPORT_SIZE, 2);
            if (place) {
                Keyboard_HID_Report[place - 1] = 0x00;
            }
        }
        //arrange Default HID Report
        uint8_t default_keyboard_hid_key[HID_DEFAULT_KEYBOARD_REPORT_SIZE - 1];
        uint8_t ct = 0;
        for (uint8_t i = 2; i < HID_DEFAULT_KEYBOARD_REPORT_SIZE; i++) {
            if (Keyboard_HID_Report[i]) {
                default_keyboard_hid_key[ct] = Keyboard_HID_Report[i];
                Keyboard_HID_Report[i] = 0;
                ct++;
            }
        }
        uint8_t default_report_free_index = ct + 2;
        memcpy(Keyboard_HID_Report + 2, default_keyboard_hid_key, ct);

        //clear new_release in extended keyboard

        for (uint8_t i = 0; i < new_release_size; i++) {
            Key_Bit_Set_Update(&Key_Bit_Set_HSB, &Key_Bit_Set_LSB, new_release[i], 0);
        }

        //add new_press to report

        //add to default keyboard

        for (uint8_t i = 0; i < new_press_size; i++) {
            //default Keyboard Report has free place
            if (default_report_free_index < HID_DEFAULT_KEYBOARD_REPORT_SIZE) {
                Keyboard_HID_Report[default_report_free_index] = new_press[i];
                default_report_free_index++;
            } else {
                Key_Bit_Set_Update(&Key_Bit_Set_HSB, &Key_Bit_Set_LSB, new_press[i], 0x01);
            }
        }

        uint8_t key_bit_set[HID_EX_KEYBOARD1_REPORT_SIZE - 1];
        get_Key_Bit_Set(&Key_Bit_Set_HSB,
                        &Key_Bit_Set_LSB,
                        0x04,
                        key_bit_set,
                        HID_EX_KEYBOARD1_REPORT_SIZE - 1);
        memcpy(EX_Keyboard1_HID_Report + 1,key_bit_set,HID_EX_KEYBOARD1_REPORT_SIZE - 1);

        free(Keyboard_Last_Key_Status);
        Keyboard_Last_Key_Status = (uint8_t *) malloc(sizeof(uint8_t) * Keyboard_Keycode[0] + 1);
        memcpy(Keyboard_Last_Key_Status, Keyboard_Keycode, Keyboard_Keycode[0] + 1);

        uint8_t send_mode = ((uint8_t)memcmp(Last_Keyboard_HID_Report,
                                             Keyboard_HID_Report,
                                             HID_DEFAULT_KEYBOARD_REPORT_SIZE) << 1)
                            + (uint8_t)memcmp(LastEX_Keyboard1_HID_Report,
                                              EX_Keyboard1_HID_Report,
                                              HID_EX_KEYBOARD1_REPORT_SIZE);
        switch (send_mode) {
            case 0:{
                return NULL;
            }
            case 1:{
                ret = (uint8_t *) malloc(sizeof(uint8_t) * (1 + 1 + HID_EX_KEYBOARD1_REPORT_SIZE));
                ret[0] = 1;
                ret[1] = HID_EX_KEYBOARD1_REPORT_SIZE;
                memcpy(ret + 2, EX_Keyboard1_HID_Report, HID_EX_KEYBOARD1_REPORT_SIZE);
            }
            case 2:{
                ret = (uint8_t *) malloc(sizeof(uint8_t) * (1 + 1 + HID_DEFAULT_KEYBOARD_REPORT_SIZE));
                ret[0] = 1;
                ret[1] = HID_DEFAULT_KEYBOARD_REPORT_SIZE;
                memcpy(ret + 2, Keyboard_HID_Report, HID_DEFAULT_KEYBOARD_REPORT_SIZE);
            }
            case 3:{
                ret = (uint8_t *)malloc(sizeof(uint8_t) * (1 + 1 + HID_DEFAULT_KEYBOARD_REPORT_SIZE + 1 + HID_EX_KEYBOARD1_REPORT_SIZE));
                ret[0] = 2;
                ret[1] = HID_DEFAULT_KEYBOARD_REPORT_SIZE;
                ret[2 + HID_DEFAULT_KEYBOARD_REPORT_SIZE] = HID_EX_KEYBOARD1_REPORT_SIZE;
                memcpy(ret + 2, Keyboard_HID_Report, HID_DEFAULT_KEYBOARD_REPORT_SIZE);
                memcpy(ret + 3 + HID_DEFAULT_KEYBOARD_REPORT_SIZE, EX_Keyboard1_HID_Report, HID_EX_KEYBOARD1_REPORT_SIZE);
            }
            default: {
                ret = (uint8_t *)malloc(sizeof(uint8_t) *1);
                ret[0] = 0;
            }
        }
        return ret;
    }
    ret = (uint8_t *)malloc(sizeof(uint8_t) *1);
    ret[0] = 0;
    return ret;

}