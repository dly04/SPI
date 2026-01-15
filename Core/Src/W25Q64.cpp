#include "main.h"
#include "spi.h"
#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"

#include "W25Q64.h"

/**
 *
 */
static uint8_t rx_value[10];
static uint8_t tx_value[10];
static HAL_StatusTypeDef status;
void W25Q64ReadID(uint8_t *MID, uint16_t *DID)
{
    tx_value[0] = W25Q64_JEDEC_ID;
    HAL_GPIO_WritePin(SPI_NSS_GPIO_Port, SPI_NSS_Pin, GPIO_PIN_RESET);

    // status = HAL_SPI_TransmitReceive(&hspi1, tx_value, rx_value, 4, portMAX_DELAY);
    HAL_SPI_Transmit(&hspi3, tx_value, 1, portMAX_DELAY);
    tx_value[0] = 0x00;
    HAL_SPI_Receive(&hspi3, rx_value, 3, portMAX_DELAY);
    *DID = 0x0000;
    *MID = 0x00;

    HAL_GPIO_WritePin(SPI_NSS_GPIO_Port, SPI_NSS_Pin, GPIO_PIN_SET);
}

#define _AD9910_REG_CFR1 0x00
void setCFR1()
{
    HAL_GPIO_WritePin(SPI_NSS_GPIO_Port, SPI_NSS_Pin, GPIO_PIN_RESET);
    tx_value[0] = _AD9910_REG_CFR1;
    tx_value[1] = 0x00;
    tx_value[2] = 0x00;
    tx_value[3] = 0x00;
    tx_value[4] = 0x02;
    HAL_SPI_Transmit(&hspi3, tx_value, 5, portMAX_DELAY);
    HAL_GPIO_WritePin(SPI_NSS_GPIO_Port, SPI_NSS_Pin, GPIO_PIN_SET);
}

#define _AD9910_REG_AUX_DAC 0x03
void readAUXDAC()
{
    HAL_GPIO_WritePin(SPI_NSS_GPIO_Port, SPI_NSS_Pin, GPIO_PIN_RESET);
    tx_value[0] = 0x80 | _AD9910_REG_AUX_DAC;
    tx_value[1] = 0x00;
    tx_value[2] = 0x00;
    tx_value[3] = 0x00;
    tx_value[4] = 0x00;
    // HAL_SPI_Transmit(&hspi3, tx_value, 1, portMAX_DELAY);
    // tx_value[0] = 0x00;
    // HAL_SPI_Receive(&hspi3, rx_value, 4, portMAX_DELAY);
    HAL_SPI_TransmitReceive(&hspi3, tx_value, rx_value, 5, portMAX_DELAY);
    HAL_GPIO_WritePin(SPI_NSS_GPIO_Port, SPI_NSS_Pin, GPIO_PIN_SET);
}

void pretendCPLD()
{
    setCFR1();

    HAL_GPIO_WritePin(IO_update_GPIO_Port, IO_update_Pin, GPIO_PIN_SET);
    vTaskDelay(1);
    HAL_GPIO_WritePin(IO_update_GPIO_Port, IO_update_Pin, GPIO_PIN_RESET);
    vTaskDelay(1);

    readAUXDAC();
}