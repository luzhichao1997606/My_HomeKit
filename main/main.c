/*
 * @fileName:
 * @description:
 * @version:
 * @author: lzc
 * @date: Do not edit
 * @lastEditors: lzc
 * @lastEditTime: Do not Edit
 */
/******************************************************************************/
/***        头文件  Include files                                            ***/
/******************************************************************************/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "driver/gpio.h"
#include "sdkconfig.h"

/******************************************************************************/
/***        宏定义  Macro Definitions                                        ***/
/******************************************************************************/
#define LED_Power_GPIO 32

/******************************************************************************/
/***        数据类型定义  Type Definitions                                   ***/
/******************************************************************************/
//创建任务的任务句柄
TaskHandle_t APP_Init_CreatedTask;  // 初始化任务
TaskHandle_t LED_Power_CreatedTask; // LED任务
// 二值句柄
SemaphoreHandle_t xSemaphore_Init_Task_over;

/******************************************************************************/
/***        静态函数声明  Local Function Prototypes                          ***/
/******************************************************************************/
static void app_Init_Task(void);    // 初始化任务
static void LED_Power_Task(void);   // LED任务

static void my_Init_fuc(void);
static void LED_Pin_Init(void);

/******************************************************************************/
/***        本地变量定义  Exported Variables                                 ***/
/******************************************************************************/

/******************************************************************************/
/***        静态变量定义  Local Variables                                    ***/
/******************************************************************************/

/******************************************************************************/
/***         主函数定义  Exported Functions                                 ***/
/******************************************************************************/

void app_main(void)
{
    my_Init_fuc();
    // LED供应电源任务
    xTaskCreate((void *)LED_Power_Task, "LED_Power_Task_Task", 4096, NULL, 1, &LED_Power_CreatedTask);
}
/******************************************************************************/
/***        静态函数定义  Local Functions                                    ***/
/******************************************************************************/

/**
 * @name: LED_Pin_Init
 * @brief: 初始化LED引脚
 * @author: lzc
 * @param {*}
 * @return {*}
 * @note: 修改记录：初次创建
 */
static void LED_Pin_Init(void)
{
    gpio_reset_pin(LED_Power_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_Power_GPIO, GPIO_MODE_OUTPUT);
}

/**
 * @name: app_Task
 * @brief: 初始化任务
 * @author: lzc
 * @param {*}
 * @return {*}
 * @note: 修改记录：初次创建
 */
static void app_Init_Task()
{
    // 创建二值信号量
    // 创建事件组
    // 完成初始化任务
    LED_Pin_Init();
    // 打印字符串
    printf("初始化任务完成,删除初始化任务\r\n");
    // 二值赋值
    xSemaphoreGive(xSemaphore_Init_Task_over);
    // 删除初始化任务
    vTaskDelete(APP_Init_CreatedTask);
}

/**
 * @name:LED_Power_Task
 * @brief:LED_Power 任务
 * @author: lzc
 * @param {*}
 * @return {*}
 * @note: 修改记录：初次创建
 */
static void LED_Power_Task()
{
    // 打印字符串
    printf("LED_Power 任务启动\r\n");
    while (1)
    {
        /* Blink on (output high) */
        printf("Turning on the LED\n");
        gpio_set_level(LED_Power_GPIO, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /* Blink off (output low) */
        printf("Turning off the LED\n");
        gpio_set_level(LED_Power_GPIO, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


/**
 * @name:my_Init_fuc
 * @brief:my_Init_fuc
 * @author: lzc
 * @param {*}
 * @return {*}
 * @note: 修改记录：初次创建
 */
static void my_Init_fuc()
{
    // 创建二值
    xSemaphore_Init_Task_over   = xSemaphoreCreateBinary();
    // 初始化任务
    xTaskCreate((void *)app_Init_Task, "APP_Init_Task", 4096, NULL, 4, &APP_Init_CreatedTask);
    // 确保初始化任务不被打断
    xSemaphoreTake(xSemaphore_Init_Task_over, portMAX_DELAY);
}
/******************************************************************************/
/***        END OF FILE                                                     ***/
/******************************************************************************/