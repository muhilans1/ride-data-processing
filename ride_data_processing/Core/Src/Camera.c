/*
 * CAMelerometer.c
 *
 *  Created on: Mar 1, 2023
 *      Author: Erik Pineda-A
 */

#ifndef __CAMERA_C
#define __CAMERA_C

/******************************************************
 Includes
 Note:
 ******************************************************/

#include "Camera.h"
#include "ArducamCamera.h"
#include <string.h>

/******************************************************
 Global Variables
 Note:
 ******************************************************/

extern RTC_HandleTypeDef hrtc;
CAM_STATUS_REG CAM;

/******************************************************
 Define Controls
 Note:
 ******************************************************/

#define Arducamera CAM.Arducamera
#define State CAM.STATE
#define Command CAM.COMMAND
#define Camera_Rdy CAM.Camera_rdy
#define Picture CAM.Picture
#define Camera_Entity CAM.CAMERA
#define Pic_Size CAM.Size

#define Encoded_Picture _Encoded_Picture
#define Encoded_Size _Encoded_Size


/******************************************************/
void CAM_Init ( MEM_PTR *Data_Ptr )
{ /* IWDG Timer Restart */
	Refresh_Watchdog;

	if (Camera_Entity != 1)
	{
		Camera_Rdy = 1;
		Camera_Entity = 1;
		(Arducamera) = createArducamCamera ( Camera_Entity );

		begin ( &(Arducamera) );
		CAM_Refresh ( Data_Ptr );

		setAutoExposure ( &(Arducamera) , 1 );
		CAM_Refresh ( Data_Ptr );

		setAutoISOSensitive ( &(Arducamera) , 1 );
		CAM_Refresh ( Data_Ptr );

		setAutoWhiteBalance ( &(Arducamera) , 1 );
		CAM_Refresh ( Data_Ptr );

		setAutoWhiteBalanceMode ( &(Arducamera) , CAM_WHITE_BALANCE_MODE_OFFICE );
		CAM_Refresh ( Data_Ptr );

		setColorEffect ( &(Arducamera) , CAM_COLOR_FX_NONE );
		CAM_Refresh ( Data_Ptr );

		setSaturation ( &(Arducamera) , CAM_STAURATION_LEVEL_DEFAULT );
		CAM_Refresh ( Data_Ptr );

		setEV ( &(Arducamera) , CAM_EV_LEVEL_DEFAULT );
		CAM_Refresh ( Data_Ptr );

		setContrast ( &(Arducamera) , CAM_CONTRAST_LEVEL_DEFAULT );
		CAM_Refresh ( Data_Ptr );

		setBrightness ( &(Arducamera) , CAM_BRIGHTNESS_LEVEL_DEFAULT );
		CAM_Refresh ( Data_Ptr );

		setSharpness ( &(Arducamera) , CAM_SHARPNESS_LEVEL_AUTO );
		CAM_Refresh ( Data_Ptr );

		setImageQuality ( &(Arducamera) , LOW_QUALITY );
		CAM_Refresh ( Data_Ptr );

//		lowPowerOn ( &(Arducamera) );
//		CAM_Refresh ( Data_Ptr );
//
//		lowPowerOff ( &(Arducamera) );
//		CAM_Refresh ( Data_Ptr );
//
//		cameraHeartBeat ( &(Arducamera) );
//		CAM_Refresh ( Data_Ptr );

		HAL_Delay ( 500 );
		stopPreview ( &(Arducamera) );
		CAM_Refresh ( Data_Ptr );
	}
	else HAL_Delay ( 5 );
}

void CAM_Refresh ( MEM_PTR *Data_Ptr )
{
	Refresh_Watchdog;

	if (State == CAM_OK) Log_Single ( CAM_Success );
	else Log_Single ( CAM_Fail );

	HAL_Delay ( 130 );
}

/******************************************************/
void CAM_COMMAND ( MEM_PTR *Data_Ptr )
{
	Refresh_Watchdog; // required to not self restart in the middle of your function

	switch (Command)
	{
		case TAKE_IMG:
			Camera_Rdy = 0;

			takePicture ( &(Arducamera) , CAM_IMAGE_MODE_QVGA , CAM_IMAGE_PIX_FMT_JPG );
//			takePicture ( &(Arducamera) , CAM_IMAGE_MODE_HD , CAM_IMAGE_PIX_FMT_JPG );
			HAL_Delay ( 100 );

			buf = 0;
			while (Arducamera.receivedLength)
			{
				readBuff ( &(Arducamera) , &(Picture [ buf ]) , picXferSize );
				buf += picXferSize;
			}

			// KCS ADD XPS SAVE for multiple pictures taken per PIR event

			Disable_Extra_Power ( Data_Ptr );

			buf = PIC_MAX;
			base64_encode ( Encoded_Picture , (size_t*) &buf , (const unsigned char*) Picture ,
			Arducamera.totalLength );

			Pic_Size = buf;
			Encoded_Size = Pic_Size;

#ifdef Log_Level_1
			Log_Single ( LOG_Image_Data );
#ifdef CAMERA_RAW_OUT
			for (buf = 0; buf <= Pic_Size; buf += UART_BUF_SIZE)
			{
				vcom_Trace ( &Encoded_Picture [ buf ] , UART_BUF_SIZE , 1 );
			}
			vcom_Trace ( (uint8_t*) "\r\n\r\n" , 4 , 1 );
#endif
#endif
			Camera_Rdy = 1;
			break;
	}

	return;
}

void CAM_Set_Command ( CAM_CMD_TYPE Input )
{
	Command = Input;
}

CAM_STATE CAM_Get_State ( void )
{
	return State;
}

CAM_READY CAM_Get_Ready ( void )
{
	return Camera_Rdy;
}

#endif
