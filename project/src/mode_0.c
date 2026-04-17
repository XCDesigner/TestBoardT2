#include "at32f403a_407_wk_config.h"
#include "system.h"

/*
  PD板
*/

#define MASK() do{TMR1->c1dt = 75;} while(0);
#define UNMASK() do{TMR1->c1dt = 25;} while(0);

#define Z_LIMIT_PORT  GPIOA
#define Z_LIMIT_PIN   GPIO_PINS_1

static uint16_t adc_values[3];

// 电压高于1.5V，返回0代表OK
uint8_t test_pd() {
  float result;

  LED_3_ON();
  DWT_DelayMs(50);
  wk_dma_channel_config(DMA1_CHANNEL1, (uint32_t)&ADC1->odt, (uint32_t)adc_values, 3);
  adc_ordinary_software_trigger_enable(ADC1, TRUE);
  dma_flag_clear(DMA1_FDT1_FLAG);
  while(dma_flag_get(DMA1_FDT1_FLAG) == RESET);
  result = adc_values[0] * 3.3 / 4096;
  if (result < 1.5) return 1;
  else return 0;
  LED_3_OFF();
}

uint8_t test_z_limit() {
  MASK();
  DWT_DelayMs(10);
  if(!(Z_LIMIT_PORT->idt & Z_LIMIT_PIN)) return 1;
  UNMASK();
  DWT_DelayMs(10);
  if(Z_LIMIT_PORT->idt & Z_LIMIT_PIN) return 1;
  return 0;
}

void mode_0_process(void) {
  uint8_t result = 0;
  UNMASK();
  while(1) {
    if(!(KEY1_PORT->idt & KEY1_PIN)) {
      DWT_DelayMs(100);
      if(!(KEY1_PORT->idt & KEY1_PIN)) {
        LED_PASS_ON();
        LED_NG_ON();
        while(!(KEY1_PORT->idt & KEY1_PIN));
        LED_PASS_OFF();
        LED_NG_OFF();
        result = 0;
        if (test_z_limit())
          result = 1;
        if (test_pd())
          result = 1;
        if (result) LED_NG_ON();
        else LED_PASS_ON();
      }
    }
  }
}