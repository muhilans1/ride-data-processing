/*
 * FUNCTIONS.h
 *
 *  Created on: Mar 15, 2023
 *      Author: Erik Pineda-A
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

/******************************************************
 Includes
 Note:
 ******************************************************/

#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"
#include "Main.h"

/******************************************************
 Define Values
 Note:
 ******************************************************/
#define UNIQUE_Device_ID (*(volatile uint32_t*)0x0BFA0700)
#define Is_Pin_High(port,pin) (HAL_GPIO_ReadPin ( port , pin ) == GPIO_PIN_SET)
#define Is_Pin_Low(port,pin) (HAL_GPIO_ReadPin ( port , pin ) == GPIO_PIN_RESET)

// Mem size in MB-bit
#define MEM_FLASH_SIZE 256U 				// 256 MB-bit
#define MEMORY_MAX 60000//2049 					//2049 for the rsa standdard size
#define PIC_MAX MEMORY_MAX//2049 					//2049 for the rsa standdard size
#define DEVICE_ID_SIZE 15
#define Log_MSG_SIZE 250
#define UART_BUF_SIZE 64
#define CMD_FLASH_SIZE 100
#define I2C_CMD_SIZE 20
#define SPI_CMD_SIZE 20
#define INSTRUCT_SIZE 150
#define TIMSTRNGT_SIZE 100
#define Log_Size_Limit 250// Max Log list size
#define DECIMAL 10
#define Perecent_Threshold 10
#define PIR_COUNTER_LIM 10
#define Itteration_Limit 8
#define Itteration_Start_Trigger 2
#define FLASH_Limit 127
#define MODEM_START_CD  0x1500
#define CAMERA_START_CD 0x00FF

/*****************  Bit definition for BUZZER Mode register  ******************/
#define BUZZ_MODE_STARTMOTION_Pos 	(0U)
#define BUZZ_MODE_STOPMOTION_Pos		(1U)
#define BUZZ_MODE_NIGHT_Pos    			(2U)
#define BUZZ_MODE_Join_Pos					(3U)
#define BUZZ_MODE_Orphan_Pos				(4U)
#define BUZZ_MODE_TEST_Pos   				(8U)

#define BUZ_LENGTH_MOTION_msec     3001

#define BUZ_LENGTH_JOIN_msec       130
#define BUZ_LENGTH_ORPHAN_msec     90

// Up to 8 bits of space for control intializer
#define XPS_INIT 		0b00000001
#define CELL_INIT 		0b00000010
#define TEMP_INIT 		0b00000100
#define ACCEL_INIT 		0b00001000
#define CAM_INIT 		0b00010000
#define INTERRUPT_INIT 	0b00100000
#define PIR_INIT 		0b01000000
#define SYS_INIT 		0b11111111

// Up to 8 bits of space for control settings
#define AVOID_MSG_SPAM	0b00000001
#define LOG_LEVEL_1		0b00000010
#define LOG_LEVEL_2		0b00000100
#define LOG_LEVEL_3		0b00001000

// control STATE configuration
#define UPDATE_SERVER 	0b00000000000000000000000000000001
#define SERVER_COMMAND	0b00000000000000000000000000000010
#define DEVICE_LISTEN	0b00000000000000000000000000000100
#define FLASH_START		0b00000000000000000000000000001000
#define FLASH_COMPLETE	0b00000000000000000000000000010000
#define FAIL_FLASH		0b00000000000000000000000000100000
#define SLEEP_STATE 	0b00000000000000000000000001000000
#define WAKE_STATE 		0b00000000000000000000000010000000
#define PARAM_UPDT		0b00000000000000000000000100000000
#define ACCEL_UPDT		0b00000000000000000000001000000000
#define TEMP_UPDT		0b00000000000000000000010000000000
#define HUMD_UPDT		0b00000000000000000000100000000000
#define PWR_UPDT		0b00000000000000000001000000000000
#define GPS_UPDT		0b00000000000000000010000000000000
#define PIC_UPDT		0b00000000000000000100000000000000
#define GPIO_UPDT 		0b00000000000000001000000000000000
#define CELL_UPDT 		0b00000000000000010000000000000000
#define PIR_UPDT 		0b00000000000000100000000000000000
#define PIR_START 		0b00000000000001000000000000000000
#define PIC_SEND 		0b00000000000010000000000000000000
#define PIR_SEND 		0b00000000000100000000000000000000
#define BUZZER_TOGGLE 	0b00000000001000000000000000000000
#define CHARGER_DETECT 	0b00000000010000000000000000000000
#define PIC_SAVE 		0b00000000100000000000000000000000
#define DEFAULT_STATE 	WAKE_STATE

#define INSTRUCTION_EXIT_A '\0'
#define INSTRUCTION_EXIT_B '0'
#define INSTRUCTION_LOG_A '/'
#define INSTRUCTION_LOG_B '?'
#define INSTRUCTION_GPS '#'
#define INSTRUCTION_SAVE '&'
#define INSTRUCTION_ACCELERATION '^'
#define INSTRUCTION_TEMPERATURE '>'
#define INSTRUCTION_POWER '*'
#define INSTRUCTION_HUMIDITY '%'
#define INSTRUCTION_PARAM_UPDT '|'
#define INSTRUCTION_MODE_UPDT '!'
#define INSTRUCTION_HARD_SHTDOWN 'X'

#define DEFAULT_Motion_Confirm_Window 0
#define DEFAULT_Motion_Threshhold 0
#define DEFAULT_Motion_Blackout 0
#define DEFAULT_No_Motion_Detection 0
#define DEFAULT_Near_Motion 0
#define DEFAULT_Day_Night_Filter 0

#define DEFAULT_Start_Motion_Cycles 0
#define DEFAULT_Stop_Motion_Cycles 0
#define DEFAULT_Buzzer_Mode 0

#define DEFAULT_Temperature_Timer 0
#define DEFAULT_Failed_Temperature_ID_Check 0
#define DEFAULT_Default_Temperature_Timer 0
#define DEFAULT_Device_ID 0
#define DEFAULT_Temperature 0
#define DEFAULT_Humidity 0

#define DEFAULT_Device_ID 0
#define DEFAULT_Accel_X 0
#define DEFAULT_Accel_Y 0
#define DEFAULT_Accel_Z 0
#define DEFAULT_Threshold_Level 0
#define DEFAULT_Time_Window 0

#define DEFAULT_Hysteresis 0
#define DEFAULT_Threshold 0
#define DEFAULT_Timing 0
#define DEFAULT_Rage 0

#define LED_GPIO_PORT
#define LED_PIN
#define DEBUG_LED

//#define BPS240_Pin GPIO_PIN_1			// Controll for BPS240
//#define BPS240_GPIO_Port GPIOC			// Control for BPS240

#define TEST_MODE 0xFF	// Test value address
#define Value_PTR_A 0x00				// Default test value for start 1
#define Value_PTR_B 0xFF				// Default test value for start 2

#define LOG_START "\r\n\r\n\r\n\r\nDevice Start\0\r\n"	// Start of UART MSG
#define LOG_INITIALIZE "\1 Device Intialize Toggled\0"
#define LOG_ERROR "\1 Issue\0"
#define LOG_SUCCESS "\1 Success\0"
#define LOG_SPACER "\r\n\r\n\0"

#define LOG_DEBUG "\1 ***** \r\n\0"
#define LOG_DEVICE_CYCLE "\1 Device Cycle\0"
#define LOG_IDLE_START "\1 ***** Device Idle Start Time ***** \r\n\0"
#define LOG_IDLE_END "\1 ***** Device Idle End Time ***** \r\n\0"
#define LOG_SLEEP_START "\1 ***** Device Eepy Start Time ***** \r\n\0"
#define LOG_SLEEP_END "\1 ***** Device Eepy End Time ***** \r\n\0"
#define POWER_DETECT "\1 ##### USB Power Detected ##### \r\n\0"
#define POWER_FAIL_DETECT "\1 ##### NO USB Power Detected ##### \r\n\0"
#define LOG_WAKE_CYCLE "\1 Device Grind Time \r\n\0"
#define XPS_INIT_MSG "\1 Initialize Time __________ XPS __________\r\n\0"
#define TEM_INIT_MSG "\1 Initialize Time __________ TEM __________\r\n\0"
#define ACC_INIT_MSG "\1 Initialize Time __________ ACC __________\r\n\0"
#define CELL_INIT_MSG "\1 Initialize Time __________ CELL __________\r\n\0"
#define PIR_INIT_MSG "\1 Initialize Time __________ PIR __________\r\n\0"
#define CAM_INIT_MSG "\1 Initialize Time __________ CAM __________\r\n\0"
#define CAMERA_EN_MSG "\1 *** Camera Enabled  *** \r\n\0"
#define MODEM_EN_MSG "\1 *** Start Modem Enabled  *** \r\n\0"
#define MODEM_FN_MSG "\1 *** Finish Modem Enabled  *** \r\n\0"
#define MODEM_EN_FAIL_MSG "\1 *** Modem Failed   *** \r\n\0"

#define LOG_DEVICE_ID " Device ID : \0"
#define LOG_STATE_RESULT " Result : \0"	// Start of UART MSG
#define LOG_TYPE_ID " Type ID : \0"
#define LOG_TAIL "\r\n\0"				// End of UART msg

#define MAX77801_SLAVE_ADDRESS 0x30
#define MAX77801_ID 0x00
#define MAX77801_STATUS 0x01
#define MAX77801_CNFG_1 0x02
#define MAX77801_CNFG_2 0x03
#define MAX77801_VOUT_DVS_L 0x04
#define MAX77801_VOUT_DVS_H 0x05
#define MAX77801_VOUT_4V 0x7F

#define POLARSSL_ERR_BASE64_BUFFER_TOO_SMALL               -0x002A  /**< Output buffer too small. */
#define POLARSSL_ERR_BASE64_INVALID_CHARACTER              -0x002C  /**< Invalid character in input. */

#define BUZZER_TIME 200

#define PIR_SLEEP_WAKE_PIN PWR_WAKEUP_PIN1_HIGH_0
#define INT1_SLEEP_WAKE_PIN PWR_WAKEUP_PIN6_HIGH_1
#define INT2_SLEEP_WAKE_PIN PWR_WAKEUP_PIN2_HIGH_1

#define Refresh_Watchdog if (HAL_IWDG_Refresh ( &hiwdg ) != HAL_OK) Error_Handler ();

#define buf Data_Ptr->Buffer
#define Dev_Mode memory.Mode
#define Dev_Prev_Mode memory.Prev_Mode
#define _Memory Data_Ptr->Memory
#define _Pointer Data_Ptr->PTR
#define _State Data_Ptr->State
#define _Init_Flags Data_Ptr->Init_Flags
#define _Setting Data_Ptr->Setting
#define _Size Data_Ptr->Size
#define _Temperature Data_Ptr->Temperature_Data.Temperature
#define _Humidity Data_Ptr->Temperature_Data.Humidity
#define _Temp_Device_ID Data_Ptr->Temperature_Data.Device_ID
#define _Acce_Device_ID Data_Ptr->Accelerometer_Data.Device_ID
#define _X_Axis Data_Ptr->Accelerometer_Data.Accel_X
#define _Y_Axis Data_Ptr->Accelerometer_Data.Accel_Y
#define _Z_Axis Data_Ptr->Accelerometer_Data.Accel_Z
#define _Page Data_Ptr->External_Data.Page
#define _Shift Data_Ptr->External_Data.Shift
#define _Encoded_Picture Data_Ptr->Camera_Data.Encoded
#define _Encoded_Size Data_Ptr->Camera_Data.Encoded_Size
#define _Server_Instrucions Data_Ptr->Modem_Data.Instruction
#define _Package_Page Data_Ptr->Modem_Data.Package_Page
#define _Buzzer_Control memory.Buzzer_Data.Control
#define _PIR_Control Data_Ptr->PIR_Data.Control

/******************************************************
 Global Enum
 Note:
 ******************************************************/
typedef enum
{							// Type definitions for ACC command
	DEV_Mode_A = 0,						// Default Mode
	DEV_Mode_B,							// Soft Restart Mode
	DEV_Mode_C,							// Demo Mode
	DEV_Mode_D,							//
	DEV_Mode_E,							//
} Device_Mode;

#define START_MODE DEV_Mode_C

/******************************************************
 Global Structs
 Note:
 ******************************************************/

typedef struct
{
	uint32_t Page,							// Page buffer
	        Index,							// Index buffer
	        Address,						// Address Buffer
	        Start_Address;					// Index buffer
	uint16_t Total_Size;							// Flash Total Size
//	        Buffer;						// Flash buffer counter parameter
	uint8_t Image [ FLASH_Limit * MEM_FLASH_SIZE ];				// Memory buffer
} Flash_Data;

typedef struct
{
	uint8_t Failed_Temperature_ID_Check,	// Device ID
	        Default_Temperature_Timer,		// Device ID
	        Device_ID;						// Device ID
	uint16_t Temperature,					// Stores Temperature
	        Humidity;						// Stores Humidity
} Temperature_DATA;

typedef struct
{
	uint8_t Threshold_Level,				// Device ID
	        Time_Window,					// Device ID
	        Device_ID;						// Device ID
	uint16_t Accel_X,						// Stores X-Axis speed
	        Accel_Y,						// Stores Y-Axis speed
	        Accel_Z;						// Stores Z-Axis speed
} Accelerometer_DATA;

typedef struct
{
	unsigned char Encoded [ PIC_MAX ];
	uint32_t Encoded_Size;
} Camera_DATA;

typedef struct
{
	uint8_t Instruction [ INSTRUCT_SIZE ],				// Memory buffer
	        Time_STMP [ TIMSTRNGT_SIZE ];				// Memory buffer
	uint32_t Package_Page;				// Memory buffer
} Modem_DATA;

typedef struct
{
	uint32_t Page;							// Page (limit = 131'072)
	uint8_t Shift;							// Page Shift (limit = 256 - Data Size)
} External_DATA;

typedef struct
{
	uint8_t Percent;
	uint32_t Motion_Confirm_Window, Motion_Threshhold, Motion_Blackout, No_Motion_Detection, Near_Motion,
	        Day_Night_Filter, Control;
	uint32_t Counter;
} PIR_DATA;

typedef struct
{
	uint32_t Start_Delay, Single_Delay, Cycles_Delay, Cycles_Length, Single_Length;
	uint8_t Single_Repeat, Cycles_Repeat, State, Control;
} Buzzer_DATA;

typedef struct
{
	uint8_t Hysteresis, Threshold, Timing, Rage;
} Enviorment_DATA;

typedef struct
{
	uint32_t Sensor_Warm_Up, Modem_Warm_Up;
	uint16_t Time_Calibration,				//
	        Time_Limit;					//
} HeartBeat_DATA;

typedef struct
{								// Memory Page buffer location
	Flash_Data Flash;
	Temperature_DATA Temperature_Data;
	Accelerometer_DATA Accelerometer_Data;
	Camera_DATA Camera_Data;
	Modem_DATA Modem_Data;
	External_DATA External_Data;
	PIR_DATA PIR_Data;
	Buzzer_DATA Buzzer_Data;
	Enviorment_DATA Enviorment_Data;
	HeartBeat_DATA HeartBeat_Data;

	uint32_t Buffer,						// Data buffer
	        Size,							// Memory buffer counter parameter
	        State;							// Used to Check Flags
	uint16_t Battery;						//
	uint8_t Init_Flags,						// Controls component intialize
	        Setting, Itteration,						//
	        *PTR;							//
	uint8_t Memory [ MEMORY_MAX ];			// Memory buffer
//	uint8_t Debugger;						// Memory buffer
	Device_Mode Mode,						// Device Mode
	        Prev_Mode;						// Previous Device Mode
} MEM_PTR;

typedef struct
{
	uint16_t MSG_Size;						// Size of message
	char MSG [ Log_MSG_SIZE ];				// Actual message
//	struct Log_Item *Next;
} Log_Item;

typedef struct
{
	uint8_t Buffer;
	uint64_t Debug_Val;
	Log_Item List [ Log_Size_Limit ], Curr;
} Logger_Lists;

/******************************************************
 Function Prototypes
 Note:
 ******************************************************/

void test ( MEM_PTR *Mem );

void PACKAGE_Init ( MEM_PTR *package );
void LOG_Init ( void );
void Time_Stamp ( char *MSG );
char *TimeStamp ( void );
void Log_Single ( char *MSG );
void Clear_Instruction ( MEM_PTR *package );
void Clear_Flash ( MEM_PTR *package );
bool IsError ( MEM_PTR *Mem );
void Build_MSG ( MEM_PTR *package , char *MSG );
void Word_Transfer ( char *target , char *source );
void Char_Replace ( char *target , char *source1 , char *source2 );

void Update_Battery ( uint16_t *battery_number );
void Disable_Extra_Power ( MEM_PTR *Mem );
void Enable_Modem ( MEM_PTR *Mem );
void Enable_Modem_PWR ( MEM_PTR *Data_Ptr );
void Enable_Camera ( MEM_PTR *Mem );

//void Enable_GPIO_INT ( void );
//void Disable_GPIO_INT ( void );

#ifdef VALID_PACKAGE
void Execute_Instructions ( MEM_PTR *Mem );
void Listen ( MEM_PTR *Mem );
#endif

void Component_Initalizer ( MEM_PTR *Mem );
void Update_State ( MEM_PTR *Mem );

/**
 * \brief          Encode a buffer into base64 format
 *
 * \param dst      destination buffer
 * \param dlen     size of the buffer
 * \param src      source buffer
 * \param slen     amount of data to be encoded
 *
 * \return         0 if successful, or POLARSSL_ERR_BASE64_BUFFER_TOO_SMALL.
 *                 *dlen is always updated to reflect the amount
 *                 of data that has (or would have) been written.
 *
 * \note           Call this function with *dlen = 0 to obtain the
 *                 required buffer size in *dlen
 */
int base64_encode ( unsigned char *dst , size_t *dlen , const unsigned char *src , size_t slen );

/**
 * \brief          Decode a base64-formatted buffer
 *
 * \param dst      destination buffer
 * \param dlen     size of the buffer
 * \param src      source buffer
 * \param slen     amount of data to be decoded
 *
 * \return         0 if successful, POLARSSL_ERR_BASE64_BUFFER_TOO_SMALL, or
 *                 POLARSSL_ERR_BASE64_INVALID_CHARACTER if the input data is
 *                 not correct. *dlen is always updated to reflect the amount
 *                 of data that has (or would have) been written.
 *
 * \note           Call this function with *dlen = 0 to obtain the
 *                 required buffer size in *dlen
 */
int base64_decode ( unsigned char *dst , size_t *dlen , const unsigned char *src , size_t slen );

#ifdef Log
void Log_Insert ( char *MSG , uint32_t Command );
void Log_End ( char *MSG , uint32_t Command );
void Write_Log ( char *MSG );
void vcom_Trace ( uint8_t *p_data , uint16_t size , int block );
void Read_Last_UART_Log ( MEM_PTR *Mem );
void Read_All_UART_Log ( void );

#ifdef XPS_Logs
		void Write_XPS_Log(void);
		void Read_Last_XPS_Log(void);
		void Read_All_XPS_Log(void);
	#endif
#endif

/******************************************************
 Global Shared Variables
 Note:
 ******************************************************/
static const unsigned char base64_enc_map [ 64 ] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
        'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4',
        '5', '6', '7', '8', '9', '+', '/' };

static const unsigned char base64_dec_map [ 128 ] = { 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
        127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
        127, 127, 127, 127, 127, 127, 127, 127, 62, 127, 127, 127, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 127, 127,
        127, 64, 127, 127, 127, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
        24, 25, 127, 127, 127, 127, 127, 127, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
        44, 45, 46, 47, 48, 49, 50, 51, 127, 127, 127, 127, 127 };

extern IWDG_HandleTypeDef hiwdg;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc4;
extern I2C_HandleTypeDef hi2c1;
//extern IWDG_HandleTypeDef hiwdg;
extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart2;
extern OSPI_HandleTypeDef hospi1;
//extern RNG_HandleTypeDef hrng;
//extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi1;
extern HCD_HandleTypeDef hhcd_USB_OTG_FS;
extern RTC_HandleTypeDef hrtc;

#endif /* FUNCTIONS_H_ */
