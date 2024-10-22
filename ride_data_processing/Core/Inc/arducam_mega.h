/*
 * This file is part of the Arducam SPI Camera project.
 *
 * Copyright 2021 Arducam Technology co., Ltd. All Rights Reserved.
 *
 * This work is licensed under the MIT license, see the file LICENSE for
 * details.
 *
 */

#ifndef __SMARTSPICAM_H
#define __SMARTSPICAM_H

#include "arducam_camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file SmartSpiCam.h
 * @author Arducam
 * @date 2023/3/3
 * @version V2.0.1
 * @copyright Arducam
 */

/* Camera instance structure */
typedef struct {
    ArducamCamera cameraInfo;  // Camera drive interface and information
} Arducam_Mega;

/**
 * @brief Initialize a new camera instance
 * @param cs enable pin
 * @return Pointer to new Arducam_Mega instance
 */
Arducam_Mega* Arducam_Mega_create(int cs);

/**
 * @brief Destroy camera instance and free resources
 * @param camera Pointer to Arducam_Mega instance
 */
void Arducam_Mega_destroy(Arducam_Mega* camera);

/**
 * @brief reset camera
 * @param camera Pointer to Arducam_Mega instance
 * @return Operation status
 */
CamStatus Arducam_Mega_reset(Arducam_Mega* camera);

/**
 * @brief Initialize the configuration of the camera module
 * @param camera Pointer to Arducam_Mega instance
 * @return Operation status
 */
CamStatus Arducam_Mega_begin(Arducam_Mega* camera);

/**
 * @brief Start a snapshot with specified resolution and pixel format
 * @param camera Pointer to Arducam_Mega instance
 * @param mode Resolution of the camera module
 * @param pixel_format Output image pixel format (JPEG, RGB, YUV)
 * @return Operation status
 * @note The mode parameter must be the resolution which the current camera supports
 */
CamStatus Arducam_Mega_takePicture(Arducam_Mega* camera, CAM_IMAGE_MODE mode, CAM_IMAGE_PIX_FMT pixel_format);

/**
 * @brief Start multi capture with specified number of images
 * @param camera Pointer to Arducam_Mega instance
 * @param mode Resolution of the camera module
 * @param pixel_format Output image pixel format (JPEG, RGB, YUV)
 * @param number Number of pictures to take
 * @return Operation status
 */
CamStatus Arducam_Mega_takeMultiPictures(Arducam_Mega* camera, CAM_IMAGE_MODE mode, CAM_IMAGE_PIX_FMT pixel_format, uint8_t number);

/**
 * @brief Start preview with specified resolution mode
 * @param camera Pointer to Arducam_Mega instance
 * @param mode Resolution of the camera module
 * @return Operation status
 * @note Requires registered callback function. Default format is JPEG
 */
CamStatus Arducam_Mega_startPreview(Arducam_Mega* camera, CAM_VIDEO_MODE mode);

/**
 * @brief Camera's stream processing thread
 * @param camera Pointer to Arducam_Mega instance
 */
void Arducam_Mega_captureThread(Arducam_Mega* camera);

/**
 * @brief Stop preview
 * @param camera Pointer to Arducam_Mega instance
 * @return Operation status
 */
CamStatus Arducam_Mega_stopPreview(Arducam_Mega* camera);

/**
 * @brief Set the exposure mode
 * @param camera Pointer to Arducam_Mega instance
 * @param val 0: Auto exposure on, 1: Auto exposure off
 * @return Operation status
 */
CamStatus Arducam_Mega_setAutoExposure(Arducam_Mega* camera, uint8_t val);

/**
 * @brief Set absolute exposure manually
 * @param camera Pointer to Arducam_Mega instance
 * @param val Value of exposure line
 * @return Operation status
 * @note Requires auto exposure to be off
 */
CamStatus Arducam_Mega_setAbsoluteExposure(Arducam_Mega* camera, uint32_t val);

/**
 * @brief Set the gain mode
 * @param camera Pointer to Arducam_Mega instance
 * @param val 0: Auto gain on, 1: Auto gain off
 * @return Operation status
 */
CamStatus Arducam_Mega_setAutoISOSensitive(Arducam_Mega* camera, uint8_t val);

/**
 * @brief Set gain manually
 * @param camera Pointer to Arducam_Mega instance
 * @param val Value of gain
 * @return Operation status
 * @note Requires auto gain to be off
 */
CamStatus Arducam_Mega_setISOSensitivity(Arducam_Mega* camera, int val);

/**
 * @brief Set white balance mode
 * @param camera Pointer to Arducam_Mega instance
 * @param val 0: Auto white balance on, 1: Auto white balance off
 * @return Operation status
 */
CamStatus Arducam_Mega_setAutoWhiteBalance(Arducam_Mega* camera, uint8_t val);

/**
 * @brief Set white balance mode manually
 * @param camera Pointer to Arducam_Mega instance
 * @param mode White balance mode
 * @return Operation status
 */
CamStatus Arducam_Mega_setAutoWhiteBalanceMode(Arducam_Mega* camera, CAM_WHITE_BALANCE mode);

/**
 * @brief Set special effects
 * @param camera Pointer to Arducam_Mega instance
 * @param effect Special effects mode
 * @return Operation status
 */
CamStatus Arducam_Mega_setColorEffect(Arducam_Mega* camera, CAM_COLOR_FX effect);

/**
 * @brief Set auto focus mode
 * @param camera Pointer to Arducam_Mega instance
 * @param val Mode of autofocus
 * @return Operation status
 * @note Only 5MP cameras support auto focus
 */
CamStatus Arducam_Mega_setAutoFocus(Arducam_Mega* camera, uint8_t val);

/**
 * @brief Get auto focus status
 * @param camera Pointer to Arducam_Mega instance
 * @return 0x10: focus is finished
 * @note Only 5MP cameras support auto focus
 */
uint8_t Arducam_Mega_getAutoFocusSta(Arducam_Mega* camera);

/**
 * @brief Set manual focus
 * @param camera Pointer to Arducam_Mega instance
 * @param val Value of VCM code
 * @return Operation status
 * @note Only 5MP cameras support manual focus
 */
CamStatus Arducam_Mega_setManualFocus(Arducam_Mega* camera, uint16_t val);

/**
 * @brief Set saturation level
 * @param camera Pointer to Arducam_Mega instance
 * @param level Saturation level
 * @return Operation status
 */
CamStatus Arducam_Mega_setSaturation(Arducam_Mega* camera, CAM_STAURATION_LEVEL level);

/**
 * @brief Set EV level
 * @param camera Pointer to Arducam_Mega instance
 * @param level EV level
 * @return Operation status
 */
CamStatus Arducam_Mega_setEV(Arducam_Mega* camera, CAM_EV_LEVEL level);

/**
 * @brief Set Contrast level
 * @param camera Pointer to Arducam_Mega instance
 * @param level Contrast level
 * @return Operation status
 */
CamStatus Arducam_Mega_setContrast(Arducam_Mega* camera, CAM_CONTRAST_LEVEL level);

/**
 * @brief Set Brightness level
 * @param camera Pointer to Arducam_Mega instance
 * @param level Brightness level
 * @return Operation status
 */
CamStatus Arducam_Mega_setBrightness(Arducam_Mega* camera, CAM_BRIGHTNESS_LEVEL level);

/**
 * @brief Set Sharpness level
 * @param camera Pointer to Arducam_Mega instance
 * @param level Sharpness level
 * @return Operation status
 * @note Only 3MP cameras support sharpness control
 */
CamStatus Arducam_Mega_setSharpness(Arducam_Mega* camera, CAM_SHARPNESS_LEVEL level);

/**
 * @brief Set jpeg image quality
 * @param camera Pointer to Arducam_Mega instance
 * @param quality Image Quality
 * @return Operation status
 */
CamStatus Arducam_Mega_setImageQuality(Arducam_Mega* camera, IMAGE_QUALITY quality);

/**
 * @brief Read image data with specified length to buffer
 * @param camera Pointer to Arducam_Mega instance
 * @param buff Buffer for storing camera data
 * @param length Length of data to read
 * @return Length actually read
 * @note Length should be less than 255
 */
uint8_t Arducam_Mega_readBuff(Arducam_Mega* camera, uint8_t* buff, uint8_t length);

/**
 * @brief Read a byte from FIFO
 * @param camera Pointer to Arducam_Mega instance
 * @return Camera data byte
 * @note Ensure data is available in buffer first
 */
uint8_t Arducam_Mega_readByte(Arducam_Mega* camera);

/**
 * @brief Debug mode register write
 * @param camera Pointer to Arducam_Mega instance
 * @param buff 4 bytes: device address, register high byte, register low byte, value
 */
void Arducam_Mega_debugWriteRegister(Arducam_Mega* camera, uint8_t* buff);

/**
 * @brief Register callback functions
 * @param camera Pointer to Arducam_Mega instance
 * @param callback Buffer callback function
 * @param blockSize Length of data for callback (max 255)
 * @param handle Stop handle callback
 */
void Arducam_Mega_registerCallBack(Arducam_Mega* camera, BUFFER_CALLBACK callback, uint8_t blockSize, STOP_HANDLE handle);

/**
 * @brief Enable low power mode
 * @param camera Pointer to Arducam_Mega instance
 */
void Arducam_Mega_lowPowerOn(Arducam_Mega* camera);

/**
 * @brief Disable low power mode
 * @param camera Pointer to Arducam_Mega instance
 */
void Arducam_Mega_lowPowerOff(Arducam_Mega* camera);

/**
 * @brief Get total picture length
 * @param camera Pointer to Arducam_Mega instance
 * @return Total picture length
 */
uint32_t Arducam_Mega_getTotalLength(Arducam_Mega* camera);

/**
 * @brief Get remaining unread image length
 * @param camera Pointer to Arducam_Mega instance
 * @return Unread image length
 */
uint32_t Arducam_Mega_getReceivedLength(Arducam_Mega* camera);

/**
 * @brief Get camera instance
 * @param camera Pointer to Arducam_Mega instance
 * @return Pointer to ArducamCamera instance
 */
ArducamCamera* Arducam_Mega_getCameraInstance(Arducam_Mega* camera);

#ifdef __cplusplus
}
#endif

#endif /*__SMARTSPICAM_H*/
