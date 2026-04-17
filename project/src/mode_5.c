#include "at32f403a_407_wk_config.h"
#include "system.h"

/*
  XY传感器板
*/


#define CENTER  (100000)
#define DELTA   (100)
#define THRESHOLD_H (CENTER + DELTA)
#define THRESHOLD_L (CENTER - DELTA)

uint16_t counter;
void clear() {
  TMR2->cval = 0;
}

void compare() {
  if( (TMR2->cval > THRESHOLD_L) && (TMR2->cval < THRESHOLD_H))
    LED_PASS_ON();
  else
    LED_NG_ON();
}

void mode_5_process(void) {
  while(1) {
    if(!(KEY2_PORT->idt & KEY2_PIN)) {
      DWT_DelayMs(100);
      if(!(KEY2_PORT->idt & KEY2_PIN)) {
        while(!(KEY2_PORT->idt & KEY2_PIN));
        clear();
      }
    }
    if(!(KEY1_PORT->idt & KEY1_PIN)) {
      DWT_DelayMs(100);
      if(!(KEY1_PORT->idt & KEY1_PIN)) {
        LED_PASS_ON();
        LED_NG_ON();
        while(!(KEY1_PORT->idt & KEY1_PIN));
        LED_PASS_OFF();
        LED_NG_OFF();
        compare();
      }
    }  
  }
}