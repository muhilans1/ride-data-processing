/*
 * This file is part of the Arducam SPI Camera project.
 *
 * Copyright 2021 Arducam Technology co., Ltd. All Rights Reserved.
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 */
#ifndef __ARDUCAMLINK_H
#define __ARDUCAMLINK_H

#include "arducam_mega.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Command definitions */
#define RESET_CAMERA                0XFF
#define SET_PICTURE_RESOLUTION      0X01
#define SET_VIDEO_RESOLUTION        0X02
#define SET_BRIGHTNESS              0X03
#define SET_CONTRAST                0X04
#define SET_SATURATION              0X05
#define SET_EV                      0X06
#define SET_WHITEBALANCE           0X07
#define SET_SPECIAL_EFFECTS        0X08
#define SET_FOCUS_CONTROL          0X09
#define SET_EXPOSUREANDGAIN_CONTROL 0X0A
// #define SET_GAIN_CONTROL        0X0B
#define SET_WHILEBALANCE_CONTROL   0X0C
#define SET_MANUAL_GAIN            0X0D
#define SET_MANUAL_EXPOSURE        0X0E
#define GET_CAMERA_INFO            0X0F
#define TAKE_PICTURE               0X10
#define SET_SHARPNESS              0X11
#define DEBUG_WRITE_REGISTER       0X12
#define STOP_STREAM                0X21
#define GET_FRM_VER_INFO           0X30
#define GET_SDK_VER_INFO           0X40
#define SET_IMAGE_QUALITY          0X50
#define READ_IMAGE_LENGTH          255

/* Function declarations */
void arducamUartBegin(uint32_t baudRate);
void reportCameraInfo(Arducam_Mega* camera);
void reportVerInfo(Arducam_Mega* camera);
void reportSdkVerInfo(Arducam_Mega* camera);
void cameraGetPicture(Arducam_Mega* camera);
void arducamFlush(void);
void send_data_pack(char cmd_type, char* msg);
uint8_t uartCommandProcessing(Arducam_Mega* camera, uint8_t* commandBuff);
uint32_t arducamUartAvailable(void);
uint8_t arducamUartRead(void);

#ifdef __cplusplus
}
#endif

#endif /*__ARDUCAMLINK_H*/
