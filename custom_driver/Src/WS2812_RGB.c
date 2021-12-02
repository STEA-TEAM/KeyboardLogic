#include <malloc.h>
#include "main.h"
#include "WS2812_RGB.h"

extern SPI_HandleTypeDef hspi2;

SPI_HandleTypeDef hspi_list[WS2812_STRIP_NUM];

uint8_t WS2812_LED_NUM[WS2812_STRIP_NUM] = {16};
uint8_t *WS2812_RGB_StatusPtrList[WS2812_STRIP_NUM];

uint8_t WS2812_ValidPosition(WS2812_Position *pos_struct) {
    if (pos_struct->strip_index > WS2812_STRIP_NUM - 1) {
        return 0x00;
    } else {
        if (pos_struct->led_addr > WS2812_LED_NUM[pos_struct->strip_index] - 1) {
            return 0x00;
        }
    }
    return 0x01;
}

void WS2812_Init() {
    for (uint8_t strip_index = 0; strip_index < WS2812_STRIP_NUM; strip_index++) {
        WS2812_RGB_StatusPtrList[strip_index] = (uint8_t *) calloc(sizeof(uint8_t), WS2812_LED_NUM[strip_index] * 3);
    }
    hspi_list[0] = hspi2;
    WS2812_Update();
}

void WS2812_SetColor(WS2812_Position *position, uint8_t R, uint8_t G, uint8_t B) {

    WS2812_RGB_StatusPtrList[position->strip_index][position->led_addr * 3] = G;
    WS2812_RGB_StatusPtrList[position->strip_index][position->led_addr * 3 + 1] = R;
    WS2812_RGB_StatusPtrList[position->strip_index][position->led_addr * 3 + 2] = B;
}

void WS2812_ResetAll() {
    for (uint8_t strip_index = 0; strip_index < WS2812_STRIP_NUM; strip_index++) {
        for (uint16_t led_status_index = 0; led_status_index < WS2812_LED_NUM[strip_index] * 3; led_status_index++) {
            WS2812_RGB_StatusPtrList[strip_index][led_status_index] = 0x00;
        }
    }
    WS2812_Update();
}

void WS2812_Update() {
    //SerialPrintUint8(0xDD);
    //SerialPrintUint8Array(WS2812_RGB_StatusPtrList[0],0,48);
    for (uint8_t strip_index = 0; strip_index < WS2812_STRIP_NUM; strip_index++) {
        uint16_t SPI_Data_Len = (WS2812_LED_NUM[strip_index] * 3 + 1) * 8 + 1;
        uint8_t SPI_Buffer[SPI_Data_Len];
        for (uint8_t i = 0; i < 8; i++) {
            SPI_Buffer[i] = 0x00;
        } //reset spi to LOW

        uint8_t buffer_pt = 8;
        // |00000000| 8|8|8|8|8|8|8|8 |
        for (uint8_t set_pt = 0; set_pt < WS2812_LED_NUM[strip_index] * 3; set_pt++) {
            uint8_t bit_mask = 0b00000001;
            for (uint8_t i = 0; i < 8; i++) {
                SPI_Buffer[1 + set_pt * 8 + i] = ((WS2812_RGB_StatusPtrList[strip_index][set_pt] >> (7 - i)) & bit_mask)
                                                 ? WS2812_H : WS2812_L;
            }
        }
        //SerialPrintUint8(strip_index);
        //SerialPrintUint8(WS2812_LED_NUM[strip_index]);
        //SerialPrintUint16(SPI_Data_Len);
        SPI_Buffer[SPI_Data_Len - 1] = WS2812_L;
        HAL_SPI_Transmit_DMA(&hspi2, SPI_Buffer, SPI_Data_Len);
        HAL_Delay(1);
    }
}
