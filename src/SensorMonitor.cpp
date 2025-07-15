#include "SensorMonitor.h"

SensorMonitor::SensorMonitor(int sensorPin, int relePin, unsigned long tempoLimite)
    : sensorPin(sensorPin), relePin(relePin), tempoLimite(tempoLimite)
{
    continuarEnvio = true;
    contador = 0;
    sensorAnterior = false;
    tempoInicio = 0;
    onAlertaCallback = nullptr; // callback ainda não definido
}

void SensorMonitor::begin()
{
    pinMode(sensorPin, INPUT);
    pinMode(relePin, OUTPUT);
    digitalWrite(relePin, LOW);
    sensorAnterior = digitalRead(sensorPin);
    tempoInicio = millis();
}

void SensorMonitor::update()
{
    bool sensorAtual = digitalRead(sensorPin);
    Serial.print(sensorAtual);

    // Verifica variação no sensor
    if (sensorAtual != sensorAnterior)
    {
        tempoLimite = 300000; // Volta para 5 minutos
        Serial.println("Variação detectada! Resetando temporizador.");
        tempoInicio = millis();
        if (contador != 0)
            contador = 0;
    }

    if ((millis() - tempoInicio >= tempoLimite) && continuarEnvio)
    {
        if (contador < 2)
        {
            Serial.println("ALERTA: O filamento pode ter parado!");
            tempoLimite -= 60000; // Diminui 1 min no tempo Limite para a impressão ser desligada mais rapidamente quando não houver variação
            if (onAlertaCallback != nullptr)
                onAlertaCallback("⚠ ALERTA: O filamento pode ter parado!");

            tempoInicio = millis();
            contador++;
        }
        else if (contador == 2)
        {
            Serial.println("ALERTA: Impressora desligada!");
            digitalWrite(relePin, HIGH);
            delay(10);

            if (onAlertaCallback != nullptr)
                onAlertaCallback("ALERTA: Impressora Desligada por falta de filamento!");

            continuarEnvio = false;
            contador++;
        }
    }

    sensorAnterior = sensorAtual;
}

void SensorMonitor::onAlerta(void (*callback)(const String &mensagem))
{
    onAlertaCallback = callback;
}
