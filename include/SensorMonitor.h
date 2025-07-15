#ifndef SENSOR_MONITOR_H
#define SENSOR_MONITOR_H

#include <Arduino.h>

class SensorMonitor
{
private:
    int sensorPin;
    int relePin;
    bool continuarEnvio;
    bool sensorAnterior;
    int contador;
    unsigned long tempoInicio;
    unsigned long tempoLimite;

    void (*onAlertaCallback)(const String &mensagem); // ponteiro para função de alerta

public:
    SensorMonitor(int sensorPin, int relePin, unsigned long tempoLimite);

    void begin();
    void update();                                           // Deve ser chamado periodicamente no loop()
    void onAlerta(void (*callback)(const String &mensagem)); // Registrar função de envio de alerta
};

#endif
