#include "at32f403a_407_wk_config.h"
#include "system.h"

/*
  抽屉检测
*/

static void hall_test(void) {
  if(GPIOC->idt & GPIO_PINS_5)
    LED_3_OFF();
  else
    LED_3_ON();
}
 
void mode_4_process(void) {
  while(1) {
		hall_test();
  }
}