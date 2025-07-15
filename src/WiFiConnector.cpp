#include "WiFiConnector.h"
#include <Arduino.h>

WiFiConnector::WiFiConnector(const char *ssid, const char *password, int ledPinBlue)
{
    this->ssid = ssid;
    this->password = password;
    this->ledPinBlue = ledPinBlue;
}

// Conecta ao WiFi
void WiFiConnector::connect()
{
    pinMode(ledPinBlue, OUTPUT);

    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    int tentativas = 0;
    while (WiFi.status() != WL_CONNECTED && tentativas < 20)
    {
        delay(500);
        Serial.print(".");
        tentativas++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        digitalWrite(ledPinBlue, LOW); // WiFi conectado
        Serial.println();
        Serial.println("WiFi connected.");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        digitalWrite(ledPinBlue, HIGH); // WiFi Caiu
        Serial.println("\nFalha ao conectar no WiFi.");
    }
}

// Tenta Reconectar o WiFi se cair a conexão
void WiFiConnector::ensureConnection()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("[WiFi] Conexão perdida. Tentando reconectar...");

        WiFi.begin(ssid, password);

        bool ledState = false;
        int tentativas = 0;
        while (WiFi.status() != WL_CONNECTED && tentativas < 10)
        {
            // Pisca o LED
            ledState = !ledState;
            digitalWrite(ledPinBlue, ledState);
            delay(500);
            Serial.print(".");
            tentativas++;
        }

        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("\n[WiFi] Reconectado com sucesso.");
            digitalWrite(ledPinBlue, LOW); // Desliga o LED ao reconectar
        }
        else
        {
            Serial.println("\n[WiFi] Falha na reconexão.");
            digitalWrite(ledPinBlue, HIGH); // Liga o LED como indicação de problema
        }
    }
}

IPAddress WiFiConnector::getLocalIP()
{
    return WiFi.localIP();
}
