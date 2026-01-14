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

static uint8_t slave_rx[10];
static uint8_t slave_tx[10];
void W25Q64BeingRead()
{
    status = HAL_SPI_Receive(&hspi3, slave_rx, 2, 1000);
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    status = HAL_SPI_TransmitReceive_IT(&hspi3, slave_tx, slave_rx, 1);
}