/**
 * @file UserTask.cpp
 * @author JIANG Yicheng  RM2023 (EthenJ@outlook.sg)
 * @brief Create user tasks with cpp support
 * @version 0.1
 * @date 2022-08-20
 *
 * @copyright Copyright (c) 2022
 */
#include "AppConfig.h" // Include our customized configuration
#include "FreeRTOS.h"
#include "gpio.h"
#include "main.h"
#include "task.h"

#include "W25Q64.h"

StackType_t uxMainTaskStack[configMINIMAL_STACK_SIZE];
StaticTask_t xMainTaskTCB;
static bool btn_status = 0;
static uint8_t W25Q64_MID = 0;
static uint16_t W25Q64_DID = 0;
void mainTask(void *pvPara)
{

  while (1)
  {
    btn_status = HAL_GPIO_ReadPin(btn_GPIO_Port, btn_Pin);

    // W25Q64ReadID(&W25Q64_MID, &W25Q64_DID);
    W25Q64BeingRead();

    vTaskDelay(1000);
  }
}

/**
 * @brief Intialize all the drivers and add task to the scheduler
 * @todo  Add your own task in this file
 */
void startUserTasks()
{

  xTaskCreateStatic(mainTask, "mainTask", configMINIMAL_STACK_SIZE, NULL, 0,
                    uxMainTaskStack, &xMainTaskTCB);
}
