#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "font/font_8x16.h"


// ESP32 接腳
const uint8_t DATA_D[8] = {2,0,4,16,17,5,18,19};
const uint8_t DATA_S[2] = {27,14};
const uint8_t SCAN_D[4] = {32,33,25,26};
const uint8_t SCAN_S[3] = {15,12,13};

// ic 真值表
const uint8_t ic74138[8][3]  = {{0,0,0},{1,0,0},{0,1,0},{1,1,0},{0,0,1},{1,0,1},{0,1,1},{1,1,1}};
const uint8_t ic74154[16][4] = {{0,0,0,0},{1,0,0,0},{0,1,0,0},{1,1,0,0},{0,0,1,0},{1,0,1,0},{0,1,1,0},{1,1,1,0},{0,0,0,1},{1,0,0,1},{0,1,0,1},{1,1,0,1},{0,0,1,1},{1,0,1,1},{0,1,1,1},{1,1,1,1}};


class CDisplay {
  public:
    //
    void Init();
    void Loop();
    //
    void InitFont();
    void AddFont(uint8_t);
    void BytToBit();
    //
    uint8_t index;
    uint8_t bytBuffer[32*99];
    uint8_t bitBuffer[16][64];
}display;


void CDisplay::InitFont() {
  index = 0;
}

void CDisplay::AddFont(uint8_t font) {
  uint8_t i;
  
  for(i=0; i<16; i++) bytBuffer[16 * index + i] = fontdata_8x16[16 * font + i];
  
  index++;
}

void CDisplay::BytToBit() {
  uint8_t i, j;
  
  for(i=0; i<64; i++) {
    for(j=0; j<16; j++) {
      bitBuffer[j][i] = ((bytBuffer[j + 16 * (i / 8)] >> (7 - (i % 8))) % 2 == 1) ? 1 : 0;
    }
  }
}

void CDisplay::Init() {
  uint8_t i;
  
  for(i=0; i<8; i++) pinMode(DATA_D[i], OUTPUT);
	for(i=0; i<2; i++) pinMode(DATA_S[i], OUTPUT);
	for(i=0; i<4; i++) pinMode(SCAN_D[i],	OUTPUT);
	for(i=0; i<3; i++) pinMode(SCAN_S[i], OUTPUT);
}

void CDisplay::Loop() {
  static uint8_t clear = 0;
  static uint8_t line = 0;
	static uint8_t block = 0;
  uint8_t i, j;
  
  // 更新掃描線
  for(i=0; i<3; i++) digitalWrite(SCAN_S[i], ic74138[block][i]);
	for(i=0; i<4; i++) digitalWrite(SCAN_D[i], ic74154[line][i]);
  //
  
  //
  if(clear == 1) {
    //
    for(i=0; i<2; i++) {
      //
			for(j=0; j<8; j++) digitalWrite(DATA_D[j + 8 * i], 0);
      //
			digitalWrite(DATA_S[i], 0);
			digitalWrite(DATA_S[i], 1);
      //
		}
    //
  }else{
    //
    for(i=0; i<2; i++) {
      //
			for(j=0; j<8; j++) {
        if(i == 0) {
          if(bitBuffer[j + 0][line + 16 * block] == 1) digitalWrite(DATA_D[j], 1); else digitalWrite(DATA_D[j], 0);
        }else{ 
          if(bitBuffer[j + 8][line + 16 * block] == 1) digitalWrite(DATA_D[j], 1); else digitalWrite(DATA_D[j], 0);
        }
      }
      //
			digitalWrite(DATA_S[i], 0);
			digitalWrite(DATA_S[i], 1);
      //
		}
    //
  }
  //
  
  // clear >> line >> block
  if(++clear == 2) {
		clear = 0;
		if(++line == 16) {
			line = 0;
			if(++block == 4) {
				block = 0;
			}
		}
	}
  //
}


#endif
