#include "Keyboard_Task.h"
#include <unistd.h>
#include <stdio.h>

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    while (1) {
        Keyboard_Logic_Loop();
        usleep(1);
    }
}