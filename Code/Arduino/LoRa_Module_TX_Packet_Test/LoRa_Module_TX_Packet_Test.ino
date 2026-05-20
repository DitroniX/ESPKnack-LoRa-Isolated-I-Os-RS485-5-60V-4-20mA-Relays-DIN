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

// Libraries
#include <RadioLib.h>
#include <SPI.h>

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// Pin definitions
#define SPI_MOSI 18
#define SPI_MISO 20
#define SPI_SCK 19
#define SPI_CS 14

#define E22_IRQ 1
#define E22_NRST 21
#define E22_BUSY 3

SX1262 radio = new Module(SPI_CS, E22_IRQ, E22_NRST, E22_BUSY);

// **************** SETUP ****************
void setup()
{
  Serial.begin(115200);

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);

  Serial.print(F("\n[SX1262] Initializing ... "));

  int state = radio.begin(868.0);
  if (state == RADIOLIB_ERR_NONE)
  {
    Serial.println(F("success!"));
  }
  else
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true)
    {
      delay(10);
    }
  }

  Serial.print("\nSending Packet\n");

  radio.setOutputPower(10);

  Serial.println("ESPKnack Bring Up and Test Example Code");
}

// **************** LOOP ****************
void loop()
{
  Serial.print("\nSending Packet\n");
  Serial.print(F("startTransmit code "));
  int transmissionState = radio.startTransmit("Hello World!");
  Serial.println(transmissionState);
  Serial.println("Test End\n");

  delay(2000);
}