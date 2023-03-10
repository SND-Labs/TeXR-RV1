# TeXR RV1 Remote Controller Documentation

## Introduction:

+ Featuring RV1 made by TeXR team, the advanced wireless remote controller designed by TeXR team for all your robotics projects.
With its powerful Espressif esp32 microcontroller over WiFi using a modified Esp-now protocol, RV1 provides reliable and secure wireless control for a wide range of robotics or industrial projects you can take your robotics projects to the next level.

+ Using the 2.4GHz ISM band, RV1 can wirelessly control projects such as RC cars, RC planes, Robotic hands, drones, and other various projects, with an impressively extended range (+100m for Urban zones).
RV1 features a built-in 1.3-inch display that allows users to interact with the Remote Controller itself and view sent data values in Real-Time, providing a seamless and intuitive user experience and making it easy to monitor and control your projects.

+ **To use RV1, you'll need an ESP based receiver (any board that has any microcontroller made by Esspressif)**, which means that it can be easily integrated into any of your existing robotics projects, making it extremly easy for users to implement in either a diy project or a commercial product.

+ With RV1, users can take complete control of their projects and unleash their creativity like never before, whether you're an professional embedded systems developer, an experienced robotics enthusiast or just starting out, RV1's user-friendly design ensures that it's easy to use for users of all levels. 

+ Make sure to visit our *[Official Facebook Page: TeXRtunisia](https://facebook.com/TeXRtunisia)*.
+ For any inquiries or business-related matters, please do not hesitate to contact us via email at *texr.contact@gmail.com* . We are always available to answer any questions you may have and look forward to hearing from you.


## RV1 Documentation Shortcuts:

  1.  [Specification](https://github.com/SND-Labs/TeXR-RV1/blob/main/README.md#specification)
  2.  [Overview](https://github.com/SND-Labs/TeXR-RV1/blob/main/README.md#overview)
  3.  [Getting Started](https://github.com/SND-Labs/TeXR-RV1/blob/main/README.md#Getting-Started)
  4.  [Charging & Power Consumption](https://github.com/SND-Labs/TeXR-RV1/blob/main/README.md#Charging--Power-Consumption)
  5.  [Inputs](https://github.com/SND-Labs/TeXR-RV1/blob/main/README.md#unputs)
  6.  [Features & Modes](https://github.com/SND-Labs/TeXR-RV1/blob/main/README.md#Features--Modes)
  7.  [Description & GPIO connections (useful when Creating Custom Firmwares)](https://github.com/SND-Labs/TeXR-RV1/blob/main/README.md#Description--GPIO-connections-useful-for-Creating-Custom-Firmwares)
  8.  [Real life Dimensions](https://github.com/SND-Labs/TeXR-RV1/blob/main/README.md#Real-life-Dimensions)
  9.  [Feedback & Contact](https://github.com/SND-Labs/TeXR-RV1/blob/main/README.md#Feedback--Contact)

## Specifications:

Here are the technical specifications for the RV1 Remote Controller:

| Spec | Value |
| --- | --- |
| Latest Version | 1.0 |
| Protocol | Modified ESP-NOW |
| Frequency Band | 2.4GHz (ISM Band) |
| Range (Urban) | 100+ meters |
| Display Size | SH1106 - 1.3 inches OLED Display (128px by 64px) |
| Microcontroller | Espressif ESP32 |
| Power Source | 3.7v, 3000mAh lithium battery |
| Charging Requirements | 5v, 1A |
| Dimensions | 20.1cm x 11.0cm |


## Overview:

![OV](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/Overview.jpg) ![legend](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/legend.png)


## Getting Started:

1.  To navigate through the **Menu** You can use the **Thumbsticks** or the buttons:
      * **AUX1|AUX2|AUX3|AUX4** as **Up|Down|Left|Right**
      * The Return button.
      * The OK button.
      * The Return button.

2. Pairing the Remote Controller with a receiver (any ESP microcontroller or dev board will work completely fine): 
      - For the sake of simplicity we're going to use arduino programming in our examples but it doesnt matter what programming language you use, ***As LONG as you CHANGE the receiver's Mac Address to the one showing up on the screen in the "Pair Device" section at the "Settings" Menu page.***

      - Step 1: We need to include the needed libraries (you don't need to download them):
      
      ```
      #include <esp_now.h>
      #include <WiFi.h>
      #include <esp_wifi.h>
      ```
      
      - Step 2: We need to add a structure to hold the incomming data **| The number of Variables in the Structure NEEDS to be EXACTLY 11 |**:

          ```
          struct data_in { // this Structure will hold the received input values of the Remote Controller.

          short LJX;     // left Y axis of the Thumbstick.
          short LJY;     // left X axis of the Thumbstick.
          short RJX;     // right Y axis of the Thumbstick.
          short RJY;     // right Y axis of the Thumbstick.

          short P1;      // Potentiometer 1.
          short P2;      // Potentiometer 2.

          byte AUX1;     // Auxiliary Switch 1.
          byte AUX2;     // Auxiliary Switch 2.
          byte AUX3;     // Auxiliary Switch 3.
          byte AUX4;     // Auxiliary Switch 4.

          byte V_SW;     // Virtual Switches.

          };
          data_in receivedData;
          ```
      - Step 3: We need to define the Mac Address that is showing up on the RV1 screen, to do that:
                
           * Open Menu (Menu button).
           * Go to the Settings page (Page 2).
           * select the *Pair Device* option.
           * Confirm by pressing the *OK* button.

           ![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/pair.png)
          
           
           * Receiver's MAC Address:
           
           *    if the Remote Controller shows:       08:3A:F2:50:C8:20
               
           *    Then you need to define the Mac Address like this: 
               
           ```
           uint8_t newMACAddress[] = {0x08, 0x3A, 0xF2, 0x50, 0xC8, 0x20};
           ```
      - Step 4: Now the last thing is to do is to start receiving data with ESP-NOW protocol, simply add this code (Callback function + WiFi preferences):

          ```
          // Callback function that will be executed when data is received:

          void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
            memcpy(&receivedData, incomingData, sizeof(receivedData));
            //Serial.print("Bytes received: "); //print received data size
            //Serial.println(len); //print received data size
            delay(10);
          }
          ```
          ```
          void setup() {
          
            // Initialize Serial Monitor
            Serial.begin(115200);

            // Set device as a WiFi Station
            WiFi.mode(WIFI_STA);
            esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]);

            // Initialize ESP-NOW
            if (esp_now_init() != ESP_OK) {
              Serial.println("Error initializing ESP-NOW");
              return;
            }

            // Once ESPNow is successfully initialized, we will register for receiving Callback function to
            // receive the data and the packet info.
            
            esp_now_register_recv_cb(OnDataRecv);
          }
          ```
          
          * Now you are Ready to fully use the received data however you like!
          * As an example, we can print them on the Serial Monitor:

          ```
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
            Serial.print(" Virtual Switch N??: ");
            Serial.print(receivedData.V_SW); 
            Serial.println(" is ON ");
            delay(10);
          }
          ```
##  Charging & Power Consumption:

   + Rated Charging Voltage ???: 5V
   + Rated Charging Current ???: 1A
   + Active mode power consumption (Full Transmission power): 4.25v-3.6v at 240mAh (lasts 2 Hours on single charge)
   + Hibernation Mode (when you trun off the device using the power button): 125mAh (lasts 24 hours on single charge).
   + Charging status:
      * Menu button is ***Blue***: Charging in progress.      
      * Menu button is ***Green***: Charging is complete.

![charging](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/charging.png) ![charged](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/charged.png)



## Inputs:

+ x2 Thumnsticks
+ x2 potentiometers.
+ x4 Auxiliary Switch buttons.
+ x4 Virtual Switches.



## Features & Modes:

1.  Virtual Switches acts like a permanent Switch that stays *ON* even when the remote restarts.
    To *Choose* and *Activate* a **Virtual Switch**:
      * Open Menu (Menu button).
      * You will be already in the Virtual Switches page (Page 1).
      * Confirm by pressing the *OK* button.

![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/vs.png)

2.  To *change* the display mode, **Dark Mode** or **Light Mode**:
      * Open Menu (Menu button).
      * Go to the Display Mode page (Page 3).
      * Confirm by pressing the *OK* button.

![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/dm.png)

**Dark Mode vs Light Mode**

![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/dark.png) ![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/light.png)

3.  You can *change* the **Transmission Mode**, **Performance Mode**(14ms Latency) or **Smooth Mode**(25ms Latency):
      * Open Menu (Menu button).
      * Go to the Transmission Mode page (Page 4).
      * Confirm by pressing the *OK* button.

![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/tm.png)

4.  RV1 supports OTA updates, meaning you can upload your own firmware, to do so:

     ***CAUTION! UPLOADING A CUSTOM FIRMWARE CAN LEAD TO BRICKING YOUR RV1 REMOTE CONTROLLER SO AT LEAST MAKE SURE YOU HAVE AN ALREADY WORKING OTA UPDATE CODE AND TEST IT ON A ESP32 BASED PROJECT or DEV BOARD AND PROCEED CAREFULLY AND WITH DOUBLE VERIFICATION IN EVERY STEP***

      * Create a mobile Hotspot using your phone or pc | **Hotspot Name: OTA** | **Hotspot password: T3XR_RV1** |
      * Connect your PC on the recently created Hotspot.
      * On the RV1 Open Menu (Menu button).
      * Go to the Settings page (Page 2).
      * Select the *update* option
      * Confirm by pressing the *OK* button.
      Then the device should display *Connecting...* then Automatically connects to the Hotspot and displays an IP Address on the screen:
      
     ![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/update.png)

      * Now open your web browser and type *IP Address*/update:
      
     ![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/ip.png)
     
      * You should see this interface:
      
     ![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/ota.png)
     
      * Now Click on choose file, and browse to your BIN firmware file
      
     ![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/firmware.png)

      Then the uploading process should start automatically and once it's completed the Device will restart automatically.
      * ***Congrats now you are running your own firmware!***
      * **If you ended up bricking your device make sure to contact us at: *texr.contact@gmail.com* or on our Facebook page *[Official Facebook Page](https://facebook.com/TeXRtunisia)*
   


## Description & GPIO connections (useful for Creating Custom Firmwares):

1.  Description:
     > The Display is the SH1106 1.3 inches OLED display
     
     > The Display uses I2C communication protocol

     > i2c_Address: 0x3c

2.  GPIO connections:
     > Power button -- GPIO 26
     
     > Menu button -- GPIO 19
     
     > Buzzer -- GPIO 25
     
     > Potentiometer 1 -- GPIO 39
     
     > Potentiometer 2 -- GPIO 36
     
     > Right Y axis of the Thumbstick -- GPIO  32
     
     > Right X axis of the Thumbstick -- GPIO  33
     
     > Left Y axis of the Thumbstick -- GPIO  34
     
     > Left X axis of the Thumbstick -- GPIO  35
     
     > Auxiliary Switch 1 -- GPIO 4 (Pull_up)
     
     > Auxiliary Switch 2 -- GPIO 15 (Pull_up)
     
     > Auxiliary Switch 3 -- GPIO 3 (Pull_up)
     
     > Auxiliary Switch 4 -- GPIO 0 (Pull_up)
     
     > Trim Down Left Y axis -- GPIO 27 (Pull_up)
     
     > Trim UP Left Y axis -- GPIO 14 (Pull_up)
     
     > Trim Down Left X axis | Return -- GPIO 13 (Pull_up)
     
     > Trim UP Left X axis -- GPIO 12 (Pull_up)
     
     > Trim Down Right Y axis -- GPIO 5 (Pull_up)
     
     > Trim Up Right Y axis -- GPIO 18 (Pull_up)
     
     > Trim Down Right X axis | OK -- GPIO 16 (Pull_up)
     
     > Trim Up Right Y axis -- GPIO 17 (Pull_up)



## Real life Dimensions:

![dim1](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/dim1.jpg) ![dim2](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/dim2.png) ![dim3](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/dim3.png) ![dim4](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/dim4.jpg) ![dim4](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/dim5.png)



## Feedback & Contact:

  + Scanning the QR code on the back of the RV1 or in the ***Pair Device*** Section on the ***Settings*** menu will redirect you to this Github Documentation Page.

![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/back.png) ![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/qr.png)

  + Make sure to visit our *[Official Facebook Page: TeXRtunisia](https://facebook.com/TeXRtunisia)*
  + For any inquiries or business-related matters, please do not hesitate to contact us via email at *texr.contact@gmail.com* . We are always available to answer any questions you may have and look forward to hearing from you.
