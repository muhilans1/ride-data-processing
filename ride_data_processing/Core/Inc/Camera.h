/*
 * Camera.h
 *
 *  Created on: Jul 25, 2023
 *      Author: Gage VanHaverbeke
 */

#ifndef __CAMERA_H
#define __CAMERA_H

/******************************************************
 File Includes
 Note: n/a
 ******************************************************/

#include "Functions.h"
#include "ArducamCamera.h"

/******************************************************
 Define Values
 Note: Values Gathered from Datasheet
 ******************************************************/

#define LOG_Image_Data "\1 Base64 Encoded data \r\n __________________________________________________ \r\n\0"
#define CAM_Success "\1 Camera Setting Success\r\n\0"
#define CAM_Fail "\1 Camera Setting Fail\r\n\0"
#define picXferSize 1024

/******************************************************
 Global Enum
 Note: Values are used for error codes,
 command types, and XPS state
 ******************************************************/

typedef enum
{							// Error codes used for Memage debugging
	CAM_OK = 0,  						// Chip OK - Execution fine
	CAM_NOT_OK,  						// Chip NOT OK - Execution NOTE fine
} CAM_STATE;

typedef enum
{							// Error codes used for Memage debugging
	CAM_IS_READY = 0,  						// Chip OK - Execution fine
	CAM_IS_NOT_READY,  						// Chip NOT OK - Execution NOTE fine
} CAM_READY;

typedef enum
{
	TAKE_IMG = 0,
} CAM_CMD_TYPE;

typedef struct
{
	uint8_t Picture [ PIC_MAX ], CAMERA;                        //Camera storage buffer
	uint32_t Size;
	CAM_READY Camera_rdy;                      // Camera device ID
	CAM_STATE STATE;
	CAM_CMD_TYPE COMMAND;
	ArducamCamera Arducamera;
} CAM_STATUS_REG;

/******************************************************
 Function Prototypes
 Note: Typical void functions are placed with ptr
 pointer due to logic flaw in the ucontroller
 ******************************************************/

void CAM_Init ( MEM_PTR *Mem );
void CAM_Refresh ( MEM_PTR *Mem );
void CAM_COMMAND ( MEM_PTR *Mem );
void CAM_Set_Command ( CAM_CMD_TYPE Input );
CAM_STATE CAM_Get_State ( void );
CAM_READY CAM_Get_Ready ( void );

/******************************************************
 Shared Global Variables
 Note:
 ******************************************************/
extern I2C_HandleTypeDef hi2c1;			// External SPI configuration
extern IWDG_HandleTypeDef hiwdg;		// External IWDG configuration

#endif

