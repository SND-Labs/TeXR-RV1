/*
 * COPYRIGHT NOTICE:
 * 
 * Copyright 2022 SND Labs
 * 
 * This is source code is for the TeXR Remote Controller's Receiver licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this Code and associated documentation files
 * to deal in the Code without restriction, including without limitation the rights to:
 * use, copy, modify, merge, publish, distribute and/or sublicense copies of the Software.
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * IMPORTANT NOTE:
 * You can use the TeXR Remote Controller with any type Dev board or Microcontroller
 * As Long As It Supports the ESP-NOW communication protocl developed by ESPRESSIF.
 * This code is written specifically in ARDUINO to make it easier to use for beginners
 * but you can use the same concept with in any other programming language.
 * 
 * For more help and info about the product make sure you visit our dedicated GitHub Documentaion page:
 * https://github.com/SND-Labs/TeXR  
 */

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

/* Structure to hold the received data (TeXR's 10 inputs)
 * This Structure Must match the sender structure DO NOT CHANGE THIS 
 * or the code becomes unstable and can lead to a Watchdog "boot looping" 
 * depending on the ESP board you are using.
 */
struct data_in {

short LJX;
short LJY;
short RJX;
short RJY;

short P1;
short P2;

byte AUX1;
byte AUX2;
byte AUX3;
byte AUX4;

byte V_SW;

};
data_in receivedData;

/* 
 * Receiver's MAC Address:
 * This MAC Address needs to be Replaced with the one that the Remote Controller shows in the "Pair Device" section
 * at the "Settings" Menu page
 * example: 
 *    if the Remote Controller shows:       08:3A:F2:50:C8:20
 *    
 *    Then this line of code: 
 *        uint8_t newMACAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
 *        
 *    Becomes:
 *        uint8_t newMACAddress[] = {0x08, 0x3A, 0xF2, 0x50, 0xC8, 0x20};
 *        
 */
uint8_t newMACAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Callback function that will be executed when data is received:

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  //Serial.print("Bytes received: "); //print received data size
  //Serial.println(len); //print received data size
  delay(10);
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a WiFi Station
  WiFi.mode(WIFI_STA);
  esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}

void loop(){
  Serial.print(" L: X: ");
  Serial.print(receivedData.LJX);
  Serial.print(" Y: ");
  Serial.print(receivedData.LJY);
  Serial.print(" R: X: ");
  Serial.print(receivedData.RJX);
  Serial.print(" Y: ");
  Serial.print(receivedData.RJY);

  Serial.print(" P1: ");
  Serial.print(receivedData.P1);
  Serial.print(" P2: ");
  Serial.print(receivedData.P2);

  Serial.print(" AUX1: ");
  Serial.print(receivedData.AUX1);
  Serial.print(" AUX2: ");
  Serial.print(receivedData.AUX2);
  Serial.print(" AUX3: ");
  Serial.print(receivedData.AUX3);
  Serial.print(" AUX4: ");
  Serial.print(receivedData.AUX4); 
  Serial.print(" Virtual Switch N°: ");
  Serial.print(receivedData.V_SW); 
  Serial.println(" is ON ");
  delay(10);
}
