#include "TimeManager.h"
#include <TimeLib.h> // para hour(), minute(), etc.

TimeManager::TimeManager(int timeZoneOffsetHours)
    : timeClient(ntpUDP, "pool.ntp.org", timeZoneOffsetHours * 3600, 60000) // 60s de atualização
{
}

void TimeManager::begin()
{
    timeClient.begin();
    timeClient.update();
    setTime(timeClient.getEpochTime());
}

String TimeManager::getFormattedDateTime()
{
    timeClient.update();
    setTime(timeClient.getEpochTime());

    int horaAtual = hour();
    int minutoAtual = minute();
    int segundoAtual = second();
    int diaAtual = day();
    int mesAtual = month();
    int anoAtual = year();

    char dataHora[32];
    sprintf(dataHora, "%02d/%02d/%04d %02d:%02d:%02d",
            diaAtual, mesAtual, anoAtual, horaAtual, minutoAtual, segundoAtual);

    return String(dataHora);
}
