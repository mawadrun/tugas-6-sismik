//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#define LED_1 4
#define LED_2 16

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

String message = "";
char incoming_char;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}

void loop() {
  if (SerialBT.available())
  {
    incoming_char = SerialBT.read();

    if (incoming_char != '\n')
    {
      message += incoming_char;
    }
    else
    {
      message = "";
    }
  }

  if (message == "toggle_1")
  {
    Serial.println("toggling 1");
    if (digitalRead(LED_1))
    {
      digitalWrite(LED_1, LOW);
    }
    else
    {
      digitalWrite(LED_1, HIGH);
    }
  }

  if (message == "toggle_2")
  {
    Serial.println("toggling 2");
    if (digitalRead(LED_2))
    {
      digitalWrite(LED_2, LOW);
    }
    else
    {
      digitalWrite(LED_2, HIGH);
    }
  }


  delay(20);
}