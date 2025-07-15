#ifndef EMAIL_SENDER_H
#define EMAIL_SENDER_H

#include <ESP_Mail_Client.h>
#include "config.h" // <-- Importa as credenciais daqui

class EmailSender
{
private:
    SMTPSession smtp;
    Session_Config config;

    static void smtpCallback(SMTP_Status status);

public:
    EmailSender();
    void send(const String &mensagem);
};

#endif
