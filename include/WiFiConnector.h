#ifndef WIFI_CONNECTOR_H
#define WIFI_CONNECTOR_H

#include <WiFi.h>

class WiFiConnector
{
private:
    const char *ssid;
    const char *password;
    int ledPinBlue;

public:
    WiFiConnector(const char *ssid, const char *password, int ledPinBlue);
    void connect();
    void ensureConnection();
    IPAddress getLocalIP();
};

#endif
