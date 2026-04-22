#include "at32f403a_407_wk_config.h"

extern void mode_0_process(void);
extern void mode_1_process(void);
extern void mode_3_process(void);
extern void mode_4_process(void);
extern void mode_5_process(void);
extern void mode_6_process(void);

uint32_t tick;
void TMR7_GLOBAL_IRQHandler(void)
{
  TMR7->ists_bit.ovfif = 0;
  tick++;
}

// 全局变量：存储系统时钟频率（如72MHz、168MHz）
static uint32_t SystemCoreClockFreq = 0;

/**
  * @brief  初始化DWT延时模块（必须在系统时钟初始化后调用）
  * @retval 无
  */
void DWT_DelayInit(void)
{
    // 1. 使能DWT模块（内核Debug寄存器配置）
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    // 2. 清零CYCCNT计数器
    DWT->CYCCNT = 0;
    // 3. 使能CYCCNT计数功能
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    // 4. 获取系统时钟频率
    SystemCoreClockFreq = SystemCoreClock;
}

/**
  * @brief  微秒级精准延时
  * @param  us: 延时微秒数
  * @retval 无
  */
void DWT_DelayUs(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    // 计算需要计数的CPU周期数：us * 每微秒时钟数
    uint32_t cnt = us * (SystemCoreClockFreq / 1000000);
    
    // 等待计数器达到目标值
    while((DWT->CYCCNT - start) < cnt);
}

/**
  * @brief  毫秒级精准延时
  * @param  ms: 延时毫秒数
  * @retval 无
  */
void DWT_DelayMs(uint32_t ms)
{
    while(ms--)
    {
        DWT_DelayUs(1000);  // 1ms = 1000us
    }
}

#define MODE_0  0x00
#define MODE_1  0x01
#define MODE_2  0x02
#define MODE_3  0x03
#define MODE_4  0x04
#define MODE_5  0x05
#define MODE_6  0x06

void test_process(void) {
  uint8_t mode = 0;
  if ((GPIOC->idt & GPIO_PINS_0)) mode |= 1;
  if ((GPIOC->idt & GPIO_PINS_1)) mode |= 2;
  if ((GPIOC->idt & GPIO_PINS_2)) mode |= 4;
  switch(mode) {
    case MODE_0:
      mode_0_process();
    break;
    case MODE_1:
      mode_1_process();
    break;
    case MODE_3:
      mode_3_process();
    break;
    case MODE_4:
      mode_4_process();
    break;
    case MODE_5:
      mode_5_process();
    break;
    case MODE_6:
      mode_6_process();
    break;
    default:
      while(1);
    break;
  }

}