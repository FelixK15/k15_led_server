# k15_led_server

## What is this project trying to do? (ELI5)
This project is a simple HTML server destined to be running on an ATMEGA2560.
The HTML server interfaces with the Counter Strike Global Offensive Game State Intergration API (https://developer.valvesoftware.com/wiki/Counter-Strike:_Global_Offensive_Game_State_Integration)
to control an LED strip.

The idea behind the project is to have an ambient lighting response if certain events happen in a Counter Strike Global Offensive match.

## Code Overview
**main:** main part of the server

**sd:**   files located on the sim cart on the microcontroller, mainly used to store settings and the HTML pages

**sim:**  (WIP) arduino sim for win32 to be able to test the code on a win32 environment without an actual ATMEGA2560 microcontroller

