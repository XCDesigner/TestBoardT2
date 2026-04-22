#include "at32f403a_407_wk_config.h"
#include "system.h"

/*
  喷嘴检测
*/

static void hall_test(void) {
  if(GPIOB->idt & GPIO_PINS_0)
    LED_3_OFF();
  else
    LED_3_ON();
}
 
void mode_6_process(void) {
  while(1) {
		hall_test();
  }
}