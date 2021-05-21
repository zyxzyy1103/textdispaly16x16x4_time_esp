#ifndef _WIFI_H_
#define _WIFI_H_


#include <WiFi.h>
#include "time.h"


//const char* ssid     = "Zhan";
//const char* password = "0923722565";
const char* ssid     = "zyxzyy1103";
const char* password = "00000000";


const char* ntpServer = "time.windows.com";
const long  gmtOffset = 28800;
const int   daylightOffset = 0;

uint16_t cenSec = 0;
uint16_t preSec = 0;


class CWiFi {
  public:
    //
    void Init();
    void Loop();
}wifi;


void CWiFi::Init() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  configTime(gmtOffset, daylightOffset, ntpServer);
}

void CWiFi::Loop() {
  struct tm timeinfo;
  
  getLocalTime(&timeinfo);
  
  cenSec = timeinfo.tm_sec;
  if(cenSec != preSec) systime.millis = 0;
  preSec = cenSec;
  
  systime.second = timeinfo.tm_sec;
  systime.minute = timeinfo.tm_min;
  systime.hour   = timeinfo.tm_hour;
  systime.day    = timeinfo.tm_mday;
  systime.month  = timeinfo.tm_mon + 1;
  systime.year   = timeinfo.tm_year + 1900;
}


#endif
