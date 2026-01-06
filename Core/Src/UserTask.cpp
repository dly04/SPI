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
#include "ws2812.hpp"

StackType_t uxMainTaskStack[configMINIMAL_STACK_SIZE];
StaticTask_t xMainTaskTCB;
void mainTask(void *pvPara)
{
}

StackType_t uxEchoTaskStack[256];
StaticTask_t xEchoTaskTCB;
void EchoTask(void *pvPara)
{
}

StackType_t uxTestTaskStack[256];
StaticTask_t xTestTaskTCB;
void TestTask(void *pvPara)
{
}

/**
 * @brief Intialize all the drivers and add task to the scheduler
 * @todo  Add your own task in this file
 */
void startUserTasks()
{

  xTaskCreateStatic(mainTask, "mainTask", configMINIMAL_STACK_SIZE, NULL, 0,
                    uxMainTaskStack, &xMainTaskTCB);

  xTaskCreateStatic(EchoTask, "EchoTask", configMINIMAL_STACK_SIZE, NULL, 0,
                    uxEchoTaskStack, &xEchoTaskTCB);

  // xTaskCreateStatic(TestTask, "testTask", configMINIMAL_STACK_SIZE, NULL, 0,
  //                   uxTestTaskStack, &xTestTaskTCB);
}
