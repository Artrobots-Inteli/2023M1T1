#include <Arduino.h>
#include <stdio.h>
#include <ESP8266WiFi.h>
#include <time.h>
#include "EasyNextionLibrary.h"
#include <string.h>
EasyNex Nextion(Serial); // Serial2 = RX2: 16, TX2: 17

String getCurrentDateTime()
{
  // Conectar ao servidor NTP para sincronizar o relógio interno do ESP32
  configTime(0, 0, "pool.ntp.org");


  // Obter o datetime atual a partir do relógio interno
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    return "Erro ao obter o datetime";
  }

  // Converter o datetime para uma string no formato desejado
  char datetimeStr[20];
  sprintf(datetimeStr, "%02d/%02d/%04d %02d:%02d:%02d",
          timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900,
          timeinfo.tm_hour-3, timeinfo.tm_min, timeinfo.tm_sec);

  // Retornar a string do datetime
  return String(datetimeStr);
}

void setMessage()
{
  String dateTime = getCurrentDateTime();
  Nextion.writeStr("date.txt", String(dateTime));
  Nextion.writeStr("name.txt", "Sala de Reunião - R06");
}

void setup()
{
  Nextion.begin(9600);
  Serial.begin(9600);
  const char *ssid = "Inteli-COLLEGE";
  const char *password = "QazWsx@123";
  // Conectar à rede WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop()
{
  // Obter o datetime atual e imprimi-lo no console serial
  setMessage();
}