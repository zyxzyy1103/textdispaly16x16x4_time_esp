#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "font/Big5Font15.h"

// ESP32 接腳
const uint8_t DATA_D[8] = {2,0,4,16,17,5,18,19};
const uint8_t DATA_S[2] = {27,14};
const uint8_t SCAN_D[4] = {32,33,25,26};
const uint8_t SCAN_S[3] = {15,12,13};

// ic 真值表
const uint8_t ic74138[8][3]  = {{0,0,0},{1,0,0},{0,1,0},{1,1,0},{0,0,1},{1,0,1},{0,1,1},{1,1,1}};
const uint8_t ic74154[16][4] = {{0,0,0,0},{1,0,0,0},{0,1,0,0},{1,1,0,0},{0,0,1,0},{1,0,1,0},{0,1,1,0},{1,1,1,0},{0,0,0,1},{1,0,0,1},{0,1,0,1},{1,1,0,1},{0,0,1,1},{1,0,1,1},{0,1,1,1},{1,1,1,1}};

// 顯示 buffer
uint8_t patternBuffer[32*99];
uint8_t displayBuffer[16][64];

class CDisplay {
  public:
    void InitDisplay();
    void LoopDisplay();
    void UpdataBit(uint8_t);
    void SetFont(uint8_t, uint16_t);
}display;

void CDisplay::SetFont(uint8_t FontIndex, uint16_t Font) {
  uint16_t i, high, low, DataIndex, tempP[32];
  
  high = Font / 0x100;
  low  = Font % 0x100;
  high = high - 0xA4;
  if(low <= 0x7E) low = low - 0x40; else low = low - 0xA1 + 63;
  DataIndex = high * 157 + low;
  
  for(i=0; i<2 ; i++) tempP[i] = 0x00;
  for(i=0; i<30; i++) tempP[i + 2] = Big5Font15[DataIndex * 30 + i];
  
  for(i=0; i<32; i++) {
    uint8_t t[8], j;
    uint8_t n = 0;
    
    if(i < 16) {
      if(i % 2 == 0)
        for(j=0; j<8; j++) if(((tempP[2 * j + 16] >> (7 - ((i - 0 ) / 2))) % 2) == 1) t[j] = 1; else t[j] = 0;
      else
        for(j=0; j<8; j++) if(((tempP[2 * j + 0 ] >> (7 - ((i - 0 ) / 2))) % 2) == 1) t[j] = 1; else t[j] = 0;
    }else{
      if(i % 2 == 0)
        for(j=0; j<8; j++) if(((tempP[2 * j + 17] >> (7 - ((i - 16) / 2))) % 2) == 1) t[j] = 1; else t[j] = 0;
      else
        for(j=0; j<8; j++) if(((tempP[2 * j + 1 ] >> (7 - ((i - 16) / 2))) % 2) == 1) t[j] = 1; else t[j] = 0;
    }
    
    for(j=0; j<8; j++) n = n + t[j] * (1 << j);
    
    for(j=0; j<2 ; j++) patternBuffer[j] = 0x00;
    patternBuffer[32 * FontIndex + i + 2] = n;
  }
}

void CDisplay::UpdataBit(uint8_t offset) {
  uint8_t t0[8];
  uint8_t t1[8];
  uint8_t i, j, k;
  for(i = 0; i < 64; i++) {
    for(j = 0; j < 8; j++) {
      t0[j] = patternBuffer[0 + (2 * (i + offset))] >> (7 - j);
      t1[j] = patternBuffer[1 + (2 * (i + offset))] >> (7 - j);
    }
    for(j = 0; j < 8; j++) {
      if(t1[7 - j] % 2) displayBuffer[j + 0][i] = 1; else displayBuffer[j + 0][i] = 0;
      if(t0[7 - j] % 2) displayBuffer[j + 8][i] = 1; else displayBuffer[j + 8][i] = 0;
    }
  }
}

void CDisplay::InitDisplay() {
  uint8_t i;
  
  for(i = 0; i < 8; i++) pinMode(DATA_D[i], OUTPUT);
	for(i = 0; i < 2; i++) pinMode(DATA_S[i], OUTPUT);
	for(i = 0; i < 4; i++) pinMode(SCAN_D[i],	OUTPUT);
	for(i = 0; i < 3; i++) pinMode(SCAN_S[i], OUTPUT);
  
  UpdataBit(0);
}

void CDisplay::LoopDisplay() {
  static uint8_t clear = 0;
  static uint8_t line = 0;
	static uint8_t block = 0;
	uint8_t i, j;

	for(i = 0; i < 3; i++) digitalWrite(SCAN_S[i], ic74138[block][i]);
	for(i = 0; i < 4; i++) digitalWrite(SCAN_D[i], ic74154[line][i]);
	
  // 輸出 tick
  if(clear == 0) {
    // data 高低位元組
    for(i = 0; i < 2; i++) {
      // 輸出 data
      for(j = 0; j < 8; j++) {
        if(i == 0) {
          if(displayBuffer[j + 0][line + 16 * block] == 1) digitalWrite(DATA_D[j], 1); else digitalWrite(DATA_D[j], 0);
        }else{ 
          if(displayBuffer[j + 8][line + 16 * block] == 1) digitalWrite(DATA_D[j], 1); else digitalWrite(DATA_D[j], 0);
        }
      }
			
			digitalWrite(DATA_S[i], 0);
			digitalWrite(DATA_S[i], 1);		
		}
  // 清空 tick
  }else{
    for(i = 0; i < 2; i++) {
			for(j = 0; j < 8; j++) digitalWrite(DATA_D[j + 8 * i], 0);
			digitalWrite(DATA_S[i], 0);
			digitalWrite(DATA_S[i], 1);
		}
  }

  if(++clear == 2) {
		clear = 0;
		if(++line == 16) {
			line = 0;
			if(++block == 4) {
				block = 0;
			}
		}
	}
}

#endif
