/*
  Dave Williams, DitroniX 2019-2026 (ditronix.net)
  ESPKnack - IoT ESP32-C6 Based Home and Industrial Controller SDK
  Features include ESP32-C6, LoRa, Isolated I/Os, RS485, 5-60V, 4-20mA, Relays, DIN SDK

  PCA 1.2604 - Basic Bring Up Test Code - May 2026
 
  Remember!
  - Set the BOARD to Use ESP32C6 Dev Module (or similar).
  - You can also set the BAUD rate up to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash.  It will take Power from the USB 5V.
  - The Serial Monitor is configured for BAUD 115200
  
  The purpose of this test code is to cycle through the various main functions of the board as part of bring up testing.
  .
  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website or github.com/DitroniX

  * github.com/DitroniX
  * github.com/DitroniX/ESPKnack-LoRa-Isolated-I-Os-RS485-5-60V-4-20mA-Relays-DIN
  * github.com/DitroniX/ESPKnack-LoRa-Isolated-I-Os-RS485-5-60V-4-20mA-Relays-DIN/wiki
  * hackster.io/DitroniX/espknack-lora-isolated-i-os-rs485-5-60v-4-20ma-relays-sdk-b70677
*/

// https://randomnerdtutorials.com/esp32-spi-communication-arduino/

// ESP32-C6 Serial Port Initialized
// These GPIO values are defauilt C6 and not what ESPKnack board uses
// MOSI: 22
// MISO: 23
// SCL / SCLK: 21
// CS / SS: 0
// SDA: 19
// SCL: 18


// Libraries
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;  // Wait for serial port to connect
  Serial.println("\n\nESP32-C6 Serial Port Initialized");
  Serial.println("These GPIO values are defauilt C6 and not what ESPKnack board uses");

  Serial.print("MOSI: ");
  Serial.println(MOSI);

  Serial.print("MISO: ");
  Serial.println(MISO);

  Serial.print("SCL / SCLK: ");
  Serial.println(SCK);

  Serial.print("CS / SS: ");
  Serial.println(SS);

  Serial.print("SDA: ");
  Serial.println(SDA);

  Serial.print("SCL: ");
  Serial.println(SCL);
}

void loop() {}