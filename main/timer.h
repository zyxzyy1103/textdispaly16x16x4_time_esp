#ifndef _TIMER_H_
#define _TIMER_H_


hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer(void);


class CSystime {
  public:
    void Init();
    void Loop();
    //
    volatile uint16_t millis;
    volatile uint8_t  second;
    volatile uint8_t  minute;
    uint8_t  hour;
    uint8_t  day;
    uint8_t  month;
    uint16_t year;
    //
    volatile bool half;
    volatile bool quarter;
    volatile bool eight;
    volatile bool deci;
}systime;

void CSystime::Init() {
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 10, true);
  timerAlarmEnable(timer);
}

void CSystime::Loop() {
  if(++millis > 999) {
		millis = 0;
		if(++second > 59) {
			second = 0;
			if(++minute > 59) {
				minute = 0;
				if(++hour > 23) {
					hour = 0;
				}
			}
		}
	}
	
	half	  = (millis / 500 % 2) ? true : false;
	quarter = (millis / 250 % 2) ? true : false;
	eight	  = (millis / 125 % 2) ? true : false;
	deci	  = (millis / 100 % 2) ? true : false;
}

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  
  static uint8_t offset = 0;
  
	if(++offset == 100) {
		systime.Loop();
		offset = 0;
	}
  
  portEXIT_CRITICAL_ISR(&timerMux);
}


#endif
