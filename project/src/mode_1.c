#include "at32f403a_407_wk_config.h"
#include "system.h"

/*
  按键板测试
*/

#define LED_R_ON()  do{ GPIOE->scr = GPIO_PINS_13; }while(0);
#define LED_G_ON()  do{ GPIOE->scr = GPIO_PINS_14; }while(0);
#define LED_B_ON()  do{ GPIOE->scr = GPIO_PINS_15; }while(0);

#define LED_R_OFF()  do{ GPIOE->clr = GPIO_PINS_13; }while(0);
#define LED_G_OFF()  do{ GPIOE->clr = GPIO_PINS_14; }while(0);
#define LED_B_OFF()  do{ GPIOE->clr = GPIO_PINS_15; }while(0);

void hall_test(void) {
  if(GPIOA->idt & GPIO_PINS_3)
    LED_3_OFF();
  else
    LED_3_ON();
  if(GPIOA->idt & GPIO_PINS_6)
    LED_4_OFF();
  else
    LED_4_ON();
}
 
void mode_1_process(void) {
  while(1) {
    if(!(GPIOA->idt & GPIO_PINS_2)) {
      DWT_DelayMs(100);
      if(!(GPIOA->idt & GPIO_PINS_2)) {
        while(!(GPIOA->idt & GPIO_PINS_2)) {
          hall_test();
        }
        LED_R_ON();
        DWT_DelayMs(300);
        LED_R_OFF();
        LED_G_ON();
        DWT_DelayMs(300);
        LED_G_OFF();
        LED_B_ON();
        DWT_DelayMs(300);
        LED_B_OFF();
      }
    }
  }
  hall_test();
}