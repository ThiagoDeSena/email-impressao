# 📦 ESP32 - Monitoramento de Filamento de Impressora 3D

Este projeto foi desenvolvido para monitorar o estado do filamento de uma impressora 3D utilizando um **sensor infravermelho** e um **ESP32**, enviando **alertas por e-mail** caso o filamento pare de girar. Além disso, o sistema pode **desligar automaticamente a impressora via relé**, caso o problema persista.

<img src="https://github.com/user-attachments/assets/f4e50b68-c751-4bf1-b3ca-317d58d6a376" alt="WhatsApp Image 2025-07-15 at 11 18 36 (1)" width="400">


---
## 🎬 Vídeo Demonstrativo

📺 [Link para o vídeo do projeto](https://www.linkedin.com/feed/update/urn:li:activity:7321174972842844162/?originTrackingId=2boJZRI3RKKaUqj4tf%2BQDQ%3D%3D)

📺 [Melhoria do projeto](https://www.linkedin.com/feed/update/urn:li:activity:7350896457383575553/?originTrackingId=HnClR46fQTq2%2FTOE7opi4g%3D%3D) 

Assista ao vídeo para ver o sistema em ação!

## 🧠 Objetivo

Detectar possíveis falhas de impressão, como:

- Filamento quebrado;
- Falta de filamento;
- Impressora travada sem movimentação do filamento.

---

## ⚙️ Como funciona

1. Um **sensor infravermelho** monitora o movimento do filamento.
2. Sempre que há variação de cor (filamento girando), o sistema **reseta o temporizador**.
3. Caso **não haja variação** por **5 minutos**, o sistema:
   - Envia um **e-mail** informando que o filamento pode ter parado.
   - Reduz o tempo limite para **4 minutos**.
4. Se ainda **não houver variação após 4 minutos**, o sistema:
   - Envia **outro e-mail de alerta**.
5. Se novamente **nada for detectado**, o sistema:
   - Envia um e-mail de **aviso de desligamento**.
   - **Ativa o relé** para **desligar a impressora automaticamente**.
   - **Interrompe o envio de novos alertas** até o ESP32 ser reiniciado.

---

## 🔁 Fluxo resumido

<img width="1328" height="1379" alt="Fluxograma quebra de filamento" src="https://github.com/user-attachments/assets/db77a727-7af3-496c-a2d0-2ad9d4236288" />


---

## 📡 Comunicação

- Conexão Wi-Fi configurada via código.
- Envio de e-mails via **SMTP (Gmail)** usando a biblioteca [`ESP Mail Client`](https://github.com/mobizt/ESP-Mail-Client).

---

## 🔌 Componentes utilizados

- ESP32 DevKit
- Sensor Infravermelho (IR)
- Módulo Relé 5V
- Conexão Wi-Fi
- Conta de e-mail (SMTP)

---

## 🗂 Estrutura do Projeto

O projeto é modular, seguindo boas práticas e princípios SOLID:

<img width="324" height="557" alt="image" src="https://github.com/user-attachments/assets/53f6d10b-b14c-48b9-9c96-59fa7311e00d" />


---

## 📬 Alertas por E-mail

Os e-mails são enviados automaticamente para os destinatários configurados no arquivo `config.h`:

```cpp
#define EMAIL_RECIPIENT "usuario@exemplo.com"
#define RECIPIENT_NAME "Seu Nome"
```

---

## 👨‍💻 Desenvolvedor

<table> <tr> <td align="center"> <img src="https://github.com/user-attachments/assets/65acf7c7-8a0d-4dbb-9472-d22afee52b31" width="120px;" alt="Foto de Thiago de Sena"/><br> <sub><b>Thiago de Sena</b></sub><br> <a href="https://www.linkedin.com/in/thiago-de-sena-developer/" target="_blank">🔗 LinkedIn</a> </td> </tr> </table>


