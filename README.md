# TeXR RV1 Remote Controller Documentation

## Introduction:

Featuring RV1, the advanced wireless remote controller designed by TeXR team for all your robotics projects.
With its powerful Espressif esp32 microcontroller over WiFi using a modified Esp-now protocol, RV1 provides reliable and secure wireless control for a wide range of robotics or industrial projects.

Using the 2.4GHz ISM band, RV1 can wirelessly control projects such as RC cars, RC planes, Robotic hands, drones, and other various projects, with an impressively extended range (+100m for Urban zones).
RV1 features a built-in 1.3-inch display that allows users to interact with the Remote Controller itself and view sent data values in Real-Time, providing a seamless and intuitive user experience and making it easy to monitor and control your projects.

**To use RV1, you'll need an ESP based receiver (any board that has any microcontroller made by Esspressif)**, which means that it can be easily integrated into any of your existing robotics projects, making it extremly easy for users to implement in either a diy project or a commercial product.

With RV1, users can take complete control of their projects and unleash their creativity like never before, whether you're an professional embedded systems developer, an experienced robotics enthusiast or just starting out, RV1's user-friendly design ensures that it's easy to use for users of all levels. 

Take your robotics projects to the next level with the advanced wireless remote controller, RV1 made by TeXR team.


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


## Input:

1. Two Thumnsticks
2. Two potentiometers.
3. Four xiliary Switch buttons.
4. Four Virtual Switches.

## Features and Modes:

1.  To navigate through the **Menu** You can use the **Thumbsticks** or the buttons:
      * **AUX1|AUX2|AUX3|AUX4** as **Up|Down|Left|Right**
      * The Return button
      * The OK button
![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/nav.png)

2.  to *Choose* and *Activate* a **Virtual Switch**:
      * Open Menu (Menu button).
      * You will be already in the Virtual Switches page (Page 1).
      * Confirm by pressing the *OK* button.
![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/vs.png)

3.  To get the **Pair a device** instructions:
      * Open Menu (Menu button).
      * Go to the Settings page (Page 2).
      * select the *Pair Device* option.
      * Confirm by pressing the *OK* button.
![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/settings.png)

4.  To *change* the display mode, **Dark Mode** or **Light Mode**:
      * Open Menu (Menu button).
      * Go to the Display Mode page (Page 3).
      * Confirm by pressing the *OK* button.
![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/dm.png) ![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/dark.png) ![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/light.png)

5.  You can *change* the **Transmission Mode**, **Performance Mode**(4ms Latency) or **Smooth Mode**(15ms Latency):
      * Open Menu (Menu button).
      * Go to the Transmission Mode page (Page 4).
      * Confirm by pressing the *OK* button.
![Dark Mode](https://github.com/SND-Labs/TeXR-RV1/blob/main/Documentation/tm.png)

2. Power on the Remote Controller and your project.
3. Use the display and buttons on the Remote Controller to control your project wirelessly.

## Getting Started:

**1. Pairing the Remote Controller with a receiver (any ESP microcontroller or dev board will work completely fine):** 
  - For the simplicity we're going to use arduino for our examples but it doesnt matter what programming language you use, ***as long as you change the Mac Address to     the one showing up on the screen.***
  - So 1st in your project's code we need to include the needed libraries (you don't need to download them):
   ``#include <esp_now.h>``
   ``#include <WiFi.h>``
   ``#include <esp_wifi.h>``
      
2. Power on the Remote Controller and your project.
3. Use the display and buttons on the Remote Controller to control your project wirelessly.
