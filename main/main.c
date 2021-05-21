#include "button.h"
#include "display.h"
#include "timer.h"
#include "wifi.h"

const    uint8_t mode = 3;
volatile uint8_t modeIndex = 0;

void SysModeHH_MM_SS() {
  display.InitFont();
  
  display.AddFont(0x30 + systime.hour / 10);
  display.AddFont(0x30 + systime.hour % 10);
  if(systime.half) display.AddFont(0x00); else display.AddFont(0x3A);
  display.AddFont(0x30 + systime.minute / 10);
  display.AddFont(0x30 + systime.minute % 10);
  if(systime.half) display.AddFont(0x00); else display.AddFont(0x3A);
  display.AddFont(0x30 + systime.second / 10);
  display.AddFont(0x30 + systime.second % 10);
  
  display.BytToBit();
  
  if(button.btn[0].status == press) if(++modeIndex == mode) modeIndex = 0;
}

void SysModeDD_HH_MM() {
  display.InitFont();
  
  display.AddFont(0x30 + systime.day / 10);
  display.AddFont(0x30 + systime.day % 10);
  display.AddFont(0x2D);
  display.AddFont(0x30 + systime.hour / 10);
  display.AddFont(0x30 + systime.hour % 10);
  if(systime.second % 2) display.AddFont(0x00); else display.AddFont(0x3A);
  display.AddFont(0x30 + systime.minute / 10);
  display.AddFont(0x30 + systime.minute % 10);
  
  display.BytToBit();
  
  if(button.btn[0].status == press) if(++modeIndex == mode) modeIndex = 0;
}

void SysModeYYYYMMDD() {
  display.InitFont();
  
  display.AddFont(0x30 + systime.year % 100 / 10);
  display.AddFont(0x30 + systime.year % 10);
  display.AddFont(0x2D);
  display.AddFont(0x30 + systime.month / 10);
  display.AddFont(0x30 + systime.month % 10);
  display.AddFont(0x2D);
  display.AddFont(0x30 + systime.day / 10);
  display.AddFont(0x30 + systime.day % 10);
  
  display.BytToBit();
  
  if(button.btn[0].status == press) if(++modeIndex == mode) modeIndex = 0;
}

void SysMode() {
  switch(modeIndex) {
    case 0: SysModeHH_MM_SS(); break;
    case 1: SysModeDD_HH_MM(); break;
    case 2: SysModeYYYYMMDD(); break;
  }
}

void setup() {
  wifi.Init();
  systime.Init();
  display.Init();
  button.Init();
}

void loop() {
  SysMode();
  
  wifi.Loop();
  button.Loop();
  display.Loop();
}
