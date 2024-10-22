/*
 * This file is part of the Arducam SPI Camera project.
 *
 * Copyright 2021 Arducam Technology co., Ltd. All Rights Reserved.
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 */
#include <string.h>
#include <stdio.h>
#include "arducamlink.h"
#include "arducam_uart.h"

static void arducamUartWrite(uint8_t data);
static void arducamUartWriteBuff(uint8_t* buff, uint16_t length);
static void printfWrapper(const char* buff);

void arducamUartBegin(uint32_t baudRate) {
    SerialBegin(baudRate);
}

void reportVerInfo(Arducam_Mega* myCamera) {
    ArducamCamera* cameraInstance = getCameraInstance(myCamera);
    uint8_t headAndtail[] = {0xff, 0xaa, 0x03, 0xff, 0xbb};

    uint32_t len = 6;
    arducamUartWriteBuff(&headAndtail[0], 3);
    arducamUartWriteBuff((uint8_t*)&len, 4);
    arducamUartWriteBuff(cameraInstance->verDateAndNumber, 4);
    printfWrapper("\r\n");
    arducamUartWriteBuff(&headAndtail[3], 2);
}

void reportSdkVerInfo(Arducam_Mega* myCamera) {
    ArducamCamera* cameraInstance = getCameraInstance(myCamera);
    uint8_t headAndtail[] = {0xff, 0xaa, 0x05, 0xff, 0xbb};

    uint32_t len = 6;
    arducamUartWriteBuff(&headAndtail[0], 3);
    arducamUartWriteBuff((uint8_t*)&len, 4);
    arducamUartWriteBuff((uint8_t*)&cameraInstance->currentSDK->sdkVersion, 5);
    printfWrapper("\r\n");
    arducamUartWriteBuff(&headAndtail[3], 2);
}

void reportCameraInfo(Arducam_Mega* myCamera) {
    ArducamCamera* cameraInstance = getCameraInstance(myCamera);
    uint8_t headAndtail[] = {0xff, 0xaa, 0x02, 0xff, 0xbb};

    uint32_t len = 0;
    char buff[400];
    arducamUartWriteBuff(&headAndtail[0], 3);
    sprintf(buff,
            "ReportCameraInfo\r\nCamera Type:%s\r\nCamera Support Resolution:%d\r\nCamera Support "
            "specialeffects:%d\r\nCamera Support Focus:%d\r\nCamera Exposure Value Max:%ld\r\nCamera Exposure Value "
            "Min:%d\r\nCamera Gain Value Max:%d\r\nCamera Gain Value Min:%d\r\nCamera Support Sharpness:%d\r\n",
            cameraInstance->myCameraInfo.cameraId,
            cameraInstance->myCameraInfo.supportResolution,
            cameraInstance->myCameraInfo.supportSpecialEffects,
            cameraInstance->myCameraInfo.supportFocus,
            cameraInstance->myCameraInfo.exposureValueMax,
            cameraInstance->myCameraInfo.exposureValueMin,
            cameraInstance->myCameraInfo.gainValueMax,
            cameraInstance->myCameraInfo.gainValueMin,
            cameraInstance->myCameraInfo.supportSharpness);
    len = strlen(buff);
    arducamUartWriteBuff((uint8_t*)&len, 4);
    printfWrapper(buff);
    arducamUartWriteBuff(&headAndtail[3], 2);
}

void cameraGetPicture(Arducam_Mega* myCamera) {
    ArducamCamera* cameraInstance = getCameraInstance(myCamera);
    uint8_t headAndtail[] = {0xff, 0xaa, 0x01, 0xff, 0xbb};
    uint8_t buff[READ_IMAGE_LENGTH] = {0};

    uint8_t rtLength = 0;
    uint32_t len = getTotalLength(myCamera);
    arducamUartWriteBuff(&headAndtail[0], 3);
    arducamUartWriteBuff((uint8_t*)(&len), 4);
    arducamUartWrite(((cameraInstance->currentPictureMode & 0x0f) << 4) | 0x01);
    while (getReceivedLength(myCamera)) {
        rtLength = readBuff(cameraInstance, buff, READ_IMAGE_LENGTH);
        arducamUartWriteBuff(buff, rtLength);
    }
    arducamUartWriteBuff(&headAndtail[3], 2);
}

void send_data_pack(char cmd_type, char* msg) {
    uint8_t headAndtail[] = {0xff, 0xaa, 0x07, 0xff, 0xbb};
    headAndtail[2] = cmd_type;
    uint32_t len = strlen(msg) + 2;
    arducamUartWriteBuff(&headAndtail[0], 3);
    arducamUartWriteBuff((uint8_t*)&len, 4);
    printfWrapper(msg);
    printfWrapper("\r\n");
    arducamUartWriteBuff(&headAndtail[3], 2);
}

uint8_t uartCommandProcessing(Arducam_Mega* myCAM, uint8_t* commandBuff) {
    ArducamCamera* cameraInstance = getCameraInstance(myCAM);
    CamStatus state;
    uint16_t gainValue = 0;
    uint32_t exposureValue = 0;
    uint32_t exposureLen1 = 0;
    uint32_t exposureLen2 = 0;
    uint32_t exposureLen3 = 0;

    uint8_t cameraResolution = cameraInstance->currentPictureMode;
    uint8_t cameraFormat = cameraInstance->currentPixelFormat;

    switch (commandBuff[0]) {
        case SET_PICTURE_RESOLUTION:
            cameraResolution = commandBuff[1] & 0x0f;
            cameraFormat = (commandBuff[1] & 0x70) >> 4;
            takePicture(myCAM, (CAM_IMAGE_MODE)cameraResolution, (CAM_IMAGE_PIX_FMT)cameraFormat);
            break;
        case SET_VIDEO_RESOLUTION:
            cameraResolution = commandBuff[1] & 0x0f;
            state = startPreview(myCAM, (CAM_VIDEO_MODE)cameraResolution);
            if (state == CAM_ERR_NO_CALLBACK) {
                printfWrapper("callback function is not registered\n");
            }
            break;
        case SET_BRIGHTNESS:
            setBrightness(myCAM, (CAM_BRIGHTNESS_LEVEL)commandBuff[1]);
            break;
        case SET_CONTRAST:
            setContrast(myCAM, (CAM_CONTRAST_LEVEL)commandBuff[1]);
            break;
        case SET_SATURATION:
            setSaturation(myCAM, (CAM_STAURATION_LEVEL)commandBuff[1]);
            break;
        case SET_EV:
            setEV(myCAM, (CAM_EV_LEVEL)commandBuff[1]);
            break;
        case SET_WHITEBALANCE:
            setAutoWhiteBalanceMode(myCAM, (CAM_WHITE_BALANCE)commandBuff[1]);
            break;
        case SET_SPECIAL_EFFECTS:
            setColorEffect(myCAM, (CAM_COLOR_FX)commandBuff[1]);
            break;
        case SET_FOCUS_CONTROL:
            setAutoFocus(myCAM, commandBuff[1]);
            if (commandBuff[1] == 0) {
                setAutoFocus(myCAM, 0x02);
            }
            break;
        case SET_EXPOSUREANDGAIN_CONTROL:
            setAutoExposure(myCAM, commandBuff[1] & 0x01);
            setAutoISOSensitive(myCAM, commandBuff[1] & 0x01);
            break;
        case SET_WHILEBALANCE_CONTROL:
            setAutoWhiteBalance(myCAM, commandBuff[1] & 0x01);
            break;
        case SET_SHARPNESS:
            setSharpness(myCAM, (CAM_SHARPNESS_LEVEL)commandBuff[1]);
            break;
        case SET_MANUAL_GAIN:
            gainValue = (commandBuff[1] << 8) | commandBuff[2];
            setISOSensitivity(myCAM, gainValue);
            break;
        case SET_MANUAL_EXPOSURE:
            exposureLen1 = commandBuff[1];
            exposureLen2 = commandBuff[2];
            exposureLen3 = commandBuff[3];
            exposureValue = (exposureLen1 << 16) | (exposureLen2 << 8) | exposureLen3;
            setAbsoluteExposure(myCAM, exposureValue);
            break;
        case GET_CAMERA_INFO:
            reportCameraInfo(myCAM);
            break;
        case TAKE_PICTURE:
            takePicture(myCAM, (CAM_IMAGE_MODE)cameraResolution, (CAM_IMAGE_PIX_FMT)cameraFormat);
            cameraGetPicture(myCAM);
            break;
        case DEBUG_WRITE_REGISTER:
            debugWriteRegister(myCAM, commandBuff + 1);
            break;
        case STOP_STREAM:
            stopPreview(myCAM);
            break;
        case GET_FRM_VER_INFO:
            reportVerInfo(myCAM);
            break;
        case GET_SDK_VER_INFO:
            reportSdkVerInfo(myCAM);
            break;
        case RESET_CAMERA:
            resetCamera(myCAM);
            break;
        case SET_IMAGE_QUALITY:
            setImageQuality(myCAM, (IMAGE_QUALITY)commandBuff[1]);
            break;
        default:
            break;
    }
    return CAM_ERR_SUCCESS;
}

static void arducamUartWrite(uint8_t data) {
    SerialWrite(data);
    delayUs(12);
}

static void arducamUartWriteBuff(uint8_t* buff, uint16_t length) {
    for (uint16_t i = 0; i < length; i++) {
        arducamUartWrite(buff[i]);
    }
}

static void printfWrapper(const char* buff) {
    uint16_t len = strlen(buff);
    arducamUartWriteBuff((uint8_t*)buff, len);
}

uint32_t arducamUartAvailable(void) {
    return SerialAvailable();
}

uint8_t arducamUartRead(void) {
    return SerialRead();
}

void arducamFlush(void) {
    while (arducamUartAvailable()) {
        arducamUartRead();
    }
}
