#include "display.h"

void MainSub(void) {
  static uint32_t i = 0;
  static uint8_t j = 0;
  display.UpdataBit(j);
  if(++i == 500) {
    i = 0;
    if(++j == 10 * 16)
    j = 0;
  }
}

void setup(void) {
  
  display.SetFont(0, 0xB8E2);
  display.SetFont(1, 0xB5FA);
  display.SetFont(2, 0xB5BE);
  display.SetFont(3, 0xA46A);
  
  display.InitDisplay();
}

void loop(void) {
  //MainSub();
  
  display.LoopDisplay();
  
  delayMicroseconds(100);
}
