#include <Arduino.h>
#include "config.h"
#include <WiFiConnector.h>
#include "SensorMonitor.h"
#include "TimeManager.h"
#include <EmailSender.h>
#define LED 13

WiFiConnector wifi(WIFI_SSID, WIFI_PASSWORD, LED_BLUE);
SensorMonitor sensor(SENSOR, RELE, TEMPO_LIMITE);
TimeManager timeManager(TIME_ZONE_OFFSET); // UTC-3 para o Brasil
EmailSender email;

// Callback para envio de e-mail com data/hora
void enviarAlerta(const String &mensagem)
{
  String horario = timeManager.getFormattedDateTime();
  // String mensagemFinal = mensagem + String("\nHora da detecção: ") + horario;
  String mensagemFinal = mensagem;
  mensagemFinal.concat("\nHora da detecção: ");
  mensagemFinal.concat(horario);
  email.send(mensagemFinal);
}

void setup()
{
  Serial.begin(115200);
  wifi.connect();
  Serial.print("Local IP: ");
  Serial.print(wifi.getLocalIP());
  pinMode(LED, OUTPUT);

  sensor.begin();
  sensor.onAlerta(enviarAlerta); // Registra a função de envio de alerta
  email.send("ESP32 conectado com sucesso! Monitorando o filamento.");
}

void loop()
{
  wifi.ensureConnection();
  sensor.update();
  delay(500);
}
