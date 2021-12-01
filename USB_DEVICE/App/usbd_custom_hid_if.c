/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v2.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
        0x05, 0x01, //Usage Page (Generic Desktop)
        0x09, 0x06, //Usage (Keyboard)
        0xA1, 0x01, //Collection (Application)
        0x85, 0x01, //Report ID (1)
        0x05, 0x07, //Usage Page (Keyboard/Keypad)
        0x19, 0xE0, //Usage Minimum (Keyboard Left Control)
        0x29, 0xE7, //Usage Maximum (Keyboard Right GUI)
        0x15, 0x00, //Logical Minimum (0)
        0x25, 0x01, //Logical Maximum (1)
        0x95, 0x08, //Report Count (8)
        0x75, 0x01, //Report Size (1)
        0x81, 0x02, //Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
        0x95, 0x06, //Report Count (7)
        0x75, 0x08, //Report Size (8)
        0x15, 0x00, //Logical Minimum (0)
        0x26, 0xFF, 0x00, //Logical Maximum (255)
        0x05, 0x07, //Usage Page (Keyboard/Keypad)
        0x19, 0x00, //Usage Minimum (Undefined)
        0x2A, 0xFF, 0x00, //Usage Maximum
        0x81, 0x00, //Input (Data,Ary,Abs)
        0xC0, //End Collection

        0x05, 0x01, //Usage Page (Generic Desktop)
        0x09, 0x06, //Usage (Keyboard)
        0xA1, 0x01, //Collection (Application)
        0x85, 0x02, //Report ID (2)
        0x05, 0x07, //Usage Page (Keyboard/Keypad)
        0x19, 0x04, //Usage Minimum (Keyboard a and A)
        0x29, 0x73, //Usage Maximum (Keyboard F21)
        0x15, 0x00, //Logical Minimum (0)
        0x25, 0x01, //Logical Maximum (1)
        0x75, 0x01, //Report Size (1)
        0x95, 0x70, //Report Count (112)
        0x81, 0x02, //Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
        0xC0, //End Collection

        0x05, 0x01, //Usage Page (Generic Desktop)
        0x09, 0x02, //Usage (Mouse)
        0xA1, 0x01, //Collection (Application)
        0x85, 0x03, //Report ID (3)
        0x09, 0x01, //Usage (Pointer)
        0xA1, 0x00, //Collection (Physical)
        0x05, 0x09, //Usage Page (Button)
        0x15, 0x00, //Logical Minimum (0)
        0x25, 0x01, //Logical Maximum (1)
        0x19, 0x01, //Usage Minimum (Button 1)
        0x29, 0x05, //Usage Maximum (Button 5)
        0x75, 0x01, //Report Size (1)
        0x95, 0x05, //Report Count (5)
        0x81, 0x02, //Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
        0x95, 0x03, //Report Count (3)
        0x81, 0x01, //Input (Cnst,Ary,Abs)
        0x05, 0x01, //Usage Page (Generic Desktop)
        0x16, 0x00, 0x80, //Logical Minimum (-32768)
        0x26, 0xFF, 0x7F, //Logical Maximum (32767)
        0x09, 0x30, //Usage (X)
        0x09, 0x31, //Usage (Y)
        0x75, 0x10, //Report Size (16)
        0x95, 0x02, //Report Count (2)
        0x81, 0x06, //Input (Data,Var,Rel,NWrp,Lin,Pref,NNul,Bit)
        0x15, 0x81, //Logical Minimum (-127)
        0x25, 0x7F, //Logical Maximum (127)
        0x09, 0x38, //Usage (Wheel)
        0x75, 0x08, //Report Size (8)
        0x95, 0x01, //Report Count (1)
        0x81, 0x06, //Input (Data,Var,Rel,NWrp,Lin,Pref,NNul,Bit)
        0x05, 0x0C, //Usage Page (Consumer Devices)
        0x0A, 0x38, 0x02, //Usage (AC Pan)
        0x95, 0x01, //Report Count (1)
        0x81, 0x06, //Input (Data,Var,Rel,NWrp,Lin,Pref,NNul,Bit)
        0xC0, //End Collection
        0xC0, //End Collection

        0x05, 0x0C, //Usage Page (Consumer Devices)
        0x09, 0x01, //Usage (Consumer Control)
        0xA1, 0x01, //Collection (Application)
        0x85, 0x04, //Report ID (4)
        0x19, 0x00, //Usage Minimum (Undefined)
        0x2A, 0xFF, 0x02, //Usage Maximum
        0x15, 0x00, //Logical Minimum (0)
        0x26, 0xFF, 0x7F, //Logical Maximum (32767)
        0x95, 0x01, //Report Count (1)
        0x75, 0x10, //Report Size (16)
        0x81, 0x00, //Input (Data,Ary,Abs)
        0xC0, //End Collection

        0x06, 0x01, 0x00, //Usage Page (Generic Desktop)
        0x09, 0x80, //Usage (System Control)
        0xA1, 0x01, //Collection (Application)
        0x85, 0x05, //Report ID (5)
        0x19, 0x81, //Usage Minimum (System Power Down)
        0x29, 0x83, //Usage Maximum (System Wake Up)
        0x15, 0x00, //Logical Minimum (0)
        0x25, 0x01, //Logical Maximum (1)
        0x95, 0x03, //Report Count (3)
        0x75, 0x01, //Report Size (1)
        0x81, 0x02, //Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
        0x95, 0x01, //Report Count (1)
        0x75, 0x05, //Report Size (5)
        0x81, 0x01, //Input (Cnst,Ary,Abs)
        0xC0, //End Collection

        0x06, 0x00, 0xFF, //Usage Page (Vendor-Defined 1)
        0x09, 0x01, //Usage (Vendor-Defined 1)
        0xA1, 0x01, //Collection (Application)
        0x85, 0x06, //Report ID (6)
        0x15, 0x00, //Logical Minimum (0)
        0x26, 0xFF, 0x00, //Logical Maximum (255)
        0x19, 0x01, //Usage Minimum (Vendor-Defined 1)
        0x29, 0x02, //Usage Maximum (Vendor-Defined 2)
        0x75, 0x08, //Report Size (8)
        0x95, 0x40, //Report Count (64)
        0x91, 0x02, //output (Data,Var,Abs,NWrp,Lin,Pref,NNul,NVol,Bit)
        0xC0, //End Collection

        0x06, 0x00, 0xFF, //Usage Page (Vendor-Defined 1)
        0x09, 0x01, //Usage (Vendor-Defined 1)
        0xA1, 0x01, //Collection (Application)
        0x85, 0x07, //Report ID (7)
        0x15, 0x00, //Logical Minimum (0)
        0x26, 0xFF, 0x00, //Logical Maximum (255)
        0x19, 0x01, //Usage Minimum (Vendor-Defined 1)
        0x29, 0x02, //Usage Maximum (Vendor-Defined 2)
        0x75, 0x08, //Report Size (8)
        0x95, 0x08, //Report Count (8)
        0x81, 0x02, //Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
        0xC0 //End Collection


        /* USER CODE END 0 */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */
//extern HID_OutCompleteFlag;
/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */

static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
	//HID_OutCompleteFlag = 1;
  return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */

uint8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}

/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

