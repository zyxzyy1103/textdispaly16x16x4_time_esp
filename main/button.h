#ifndef _BUTTON_H_
#define _BUTTON_H_

// Button
uint8_t BTNS_P[] = {36,39,34,35};
#define BTNS_N 4


typedef struct btn_s {
  uint8_t  status;
  uint16_t time;
}btn_t;

enum status_e {
  idle,
  press,
  hold,
  release,
};

class CButton {
  public:
    void Init();
    void Loop();
    //
    btn_t   btn[BTNS_N];
}button;

void CButton::Init() {
  uint8_t i;
  
  for(i=0; i<BTNS_N; i++) pinMode(BTNS_P[i], 0);
}

void CButton::Loop(void) {
  uint8_t i, btnRead;
  
  for(i=0; i<BTNS_N; i++) {
    btnRead = digitalRead(BTNS_P[i]);
    switch(btn[i].status) {
      case idle: {
        if(btnRead == 0)
          btn[i].status = press;
        else
          btn[i].time = 0;
        break;
      }
      case press: {
        btn[i].status = hold;
        break;
      }
      case hold: {
        if(btnRead == 1)
          btn[i].status = release;
        else
          if(btn[i].time < 3000) btn[i].time++;
        break;
      }
      case release: {
        btn[i].status = idle;
        break;
      }
    }
  }
}

#endif
