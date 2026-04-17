#pragma once

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LED_PASS_ON()  do{ GPIOD->scr = GPIO_PINS_0; }while(0)
#define LED_PASS_OFF() do{ GPIOD->clr = GPIO_PINS_0; }while(0)
#define LED_NG_ON()  do{ GPIOD->scr = GPIO_PINS_1; }while(0)
#define LED_NG_OFF() do{ GPIOD->clr = GPIO_PINS_1; }while(0)
#define LED_3_ON()  do{ GPIOD->scr = GPIO_PINS_2; }while(0)
#define LED_3_OFF() do{ GPIOD->clr = GPIO_PINS_2; }while(0)
#define LED_4_ON()  do{ GPIOD->scr = GPIO_PINS_3; }while(0)
#define LED_4_OFF() do{ GPIOD->clr = GPIO_PINS_3; }while(0)

#define KEY1_PORT GPIOC
#define KEY1_PIN  GPIO_PINS_3
#define KEY2_PORT GPIOA
#define KEY2_PIN  GPIO_PINS_5
#define KEY3_PORT GPIOB
#define KEY3_PIN  GPIO_PINS_1

// 函数声明
extern void test_process(void);
extern void DWT_DelayInit(void);    // DWT初始化（必须先调用）
extern void DWT_DelayUs(uint32_t us);// 微秒级延时
extern void DWT_DelayMs(uint32_t ms);// 毫秒级延时

extern uint32_t tick;

#ifdef __cplusplus
}
#endif
