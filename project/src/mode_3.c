#include "at32f403a_407_wk_config.h"
#include "system.h"

/*
  气压传感器板
*/

#define PUMP_ON() do{ GPIOB->clr = GPIO_PINS_13; }while(0)
#define PUMP_OFF() do{ GPIOB->clr = GPIO_PINS_13; }while(0)

static uint16_t adc_values[3];
float read_pump(void) {
  float result;
  wk_dma_channel_config(DMA1_CHANNEL1, (uint32_t)&ADC1->odt, (uint32_t)adc_values, 3);
  adc_ordinary_software_trigger_enable(ADC1, TRUE);
  dma_flag_clear(DMA1_FDT1_FLAG);
  while(dma_flag_get(DMA1_FDT1_FLAG) == RESET);
  result = adc_values[2] * 3.3 / 4096;
  return result;
}

void mode_3_process(void) {
  float vol_off, vol_on;
  while(1) {
    if(!(GPIOC->idt & GPIO_PINS_2)) {
      DWT_DelayMs(100);
      if(!(GPIOA->idt & GPIO_PINS_2)) {
        LED_PASS_ON();
        LED_NG_ON();
        while(!(GPIOA->idt & GPIO_PINS_2));
        LED_PASS_OFF();
        LED_NG_OFF();
        // Pump off
        PUMP_OFF();
        vol_off = read_pump();
        if ((vol_off < 0.01) || (vol_off > 0.3)) {
          LED_NG_ON();
          continue;
        }
        PUMP_ON();
        vol_on = read_pump();
        if ((vol_on - vol_off) < 1) {
          LED_NG_ON();
          continue;
        }
        LED_PASS_ON();
      }
    }
  }
}