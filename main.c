#include "Keyboard_Task.h"
#include <unistd.h>
#include <stdio.h>

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    Keyboard_Init();
    while (1) {
        uint8_t *detected_key;
        uint16_t *all_code_list;

        Keyboard_Init();
        Keyboard_Logic_Loop();

        usleep(1);
    }
}