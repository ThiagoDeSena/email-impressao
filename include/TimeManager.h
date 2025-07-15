#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

class TimeManager
{
private:
    WiFiUDP ntpUDP;
    NTPClient timeClient;

public:
    TimeManager(int timeZoneOffsetHours = -3); // Padrão: UTC-3 (Brasil)
    void begin();
    String getFormattedDateTime(); // Retorna a hora atual formatada
};

#endif
