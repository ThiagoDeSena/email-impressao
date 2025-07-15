#include "EmailSender.h"
#include <Arduino.h>

const char *DESTINATARIOS[NUM_DESTINATARIOS][2] = {
    {RECIPIENT_NAME, EMAIL_RECIPIENT},
    {RECIPIENT_NAME_2, EMAIL_RECIPIENT_2}};

EmailSender::EmailSender()
{
    MailClient.networkReconnect(true);
    smtp.debug(1);
    smtp.callback(smtpCallback);

    config.server.host_name = SMTP_HOST;
    config.server.port = SMTP_PORT;
    config.login.email = EMAIL_SENDER;
    config.login.password = EMAIL_PASSWORD;
    config.login.user_domain = "";

    config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
    config.time.gmt_offset = -3;
    config.time.day_light_offset = 0;
}

void EmailSender::send(const String &mensagem)
{
    if (!smtp.connect(&config))
    {
        Serial.printf("[EmailSender] Falha na conexão SMTP: %s\n", smtp.errorReason().c_str());
        return;
    }

    SMTP_Message message;
    message.sender.name = F("ESP32");
    message.sender.email = EMAIL_SENDER;
    message.subject = F("Mensagem do ESP32");
    // message.addRecipient(RECIPIENT_NAME, EMAIL_RECIPIENT);
    for (int i = 0; i < NUM_DESTINATARIOS; i++)
    {
        message.addRecipient(DESTINATARIOS[i][0], DESTINATARIOS[i][1]);
    }

    message.text.content = mensagem.c_str();
    message.text.charSet = "us-ascii";
    message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

    message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
    message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

    bool success = MailClient.sendMail(&smtp, &message); // Envia o email ao remetente

    if (!success)
    {
        Serial.printf("[EmailSender] Falha ao enviar: %s\n", smtp.errorReason().c_str());
    }

    smtp.sendingResult.clear();
}

void EmailSender::smtpCallback(SMTP_Status status)
{
    Serial.println("[EmailSender] Callback SMTP:");
    Serial.println(status.info());

    if (status.success())
        Serial.println("E-mail enviado com sucesso.");
    else
        Serial.println("Erro no envio do e-mail.");
}
