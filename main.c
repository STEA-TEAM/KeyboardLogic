#include "macros.h"
#include "Keyboard_Task.h"
#include <unistd.h>
#include <stdio.h>

uint8_t HID_OutCompleteFlag;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    Keyboard_Init();
    uint8_t uct[4];
    while (1) {
        uint8_t *detected_key;
        uint16_t *all_code_list;

        Keyboard_Begin_Loop();
        detected_key = Keyboard_detect_key();
#if DEBUG
        printf("Detected keys:    ");
        for(int i = 0; i <= detected_key[0]; i++) {
            printf("%02X ", detected_key[i]);
        }
        printf("%c", '\n');
#endif
        all_code_list = Keyboard_Key_Process(detected_key);
#if DEBUG
        printf("All code list:    ");
        for(int i = 0; i <= all_code_list[0]; i++) {
            printf("%02X ", all_code_list[i]);
        }
        printf("%c", '\n');
#endif
        Keyboard_USB_HID_Send(all_code_list);
        Keyboard_End_Loop();
#if DEBUG
        printf("%c", '\n');
#endif
//        usleep(1);
    }
}