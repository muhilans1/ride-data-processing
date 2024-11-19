
/*
 * This file is part of the Arducam SPI Camera project.
 *
 * Copyright 2021 Arducam Technology co., Ltd. All Rights Reserved.
 *
 * This work is licensed under the MIT license, see the file LICENSE for
 * details.
 *
 */

#include "ArducamSpi.h"
// remove these as not necessary?
//#include <Arduino.h>
//#include <SPI.h>

//void arducamSpiBegin(void)
//{
//    return SPI.begin();
//}
//
//uint8_t arducamSpiTransfer(uint8_t data)
//{
//    return SPI.transfer(data);
//}
//
//void arducamSpiTransferBlock(uint8_t *buff,uint16_t len){
//    return SPI.transfer(buff,len);
//}
//
//void arducamSpiCsHigh(int pin)
//{
//    digitalWrite(pin, HIGH);
//}
//
//void arducamSpiCsLow(int pin)
//{
//    digitalWrite(pin, LOW);
//}
//
//void arducamSpiCsOutputMode(int pin)
//{
//    pinMode(pin, OUTPUT);
//}
//
//void arducamDelayMs(uint16_t num)
//{
//    delay(num);
//}
//void arducamDelayUs(uint16_t num)
//{
//    delayMicroseconds(num);
//}

/*
 * This file is part of the Arducam SPI Camera project.
 *
 * Copyright 2021 Arducam Technology co., Ltd. All Rights Reserved.
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 */

#include "ArducamSpi.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;  // assuming SPI1 used, adjust if different

void arducamSpiBegin(void)
{
    //SPI already initialized by HAL_Init()
    return;
}

uint8_t arducamSpiTransfer(uint8_t data)
{
    uint8_t received;
    HAL_SPI_TransmitReceive(&hspi1, &data, &received, 1, HAL_MAX_DELAY);
    return received;
}

void arducamSpiTransferBlock(uint8_t *buff, uint16_t len)
{
    uint8_t *rxBuff = (uint8_t*)malloc(len);
    if (rxBuff != NULL) {
        HAL_SPI_TransmitReceive(&hspi1, buff, rxBuff, len, HAL_MAX_DELAY);
        memcpy(buff, rxBuff, len);
        free(rxBuff);
    }
}

void arducamSpiCsHigh(int pin)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // adjust port/pin as needed
}

void arducamSpiCsLow(int pin)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // adjust port/pin needed?
}

void arducamSpiCsOutputMode(int pin)
{
    //CS pin is already configured as output in MX_GPIO_Init()
}

void arducamDelayMs(uint16_t num)
{
    HAL_Delay(num);
}

void arducamDelayUs(uint16_t num)
{
    uint32_t loops = (HAL_RCC_GetHCLKFreq() / 1000000) * num / 4;
    while(loops--) {
        __NOP();
    }
}
