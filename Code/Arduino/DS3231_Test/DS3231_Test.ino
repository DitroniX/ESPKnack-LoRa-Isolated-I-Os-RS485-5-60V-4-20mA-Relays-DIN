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
#include <DS3231.h>
#include <Wire.h>

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// Hardware Serial 0 GPIO Pins
#define RXD0 17
#define TXD0 16

// Define I2C (Expansion Port)
#define I2C_SDA 6
#define I2C_SCL 7

char myData[50];
DS3231 myRTC;
bool h12Flag;
bool pmFlag;

// **************** FUNCTIONS AND ROUTINES ****************

// **************** SETUP ****************
void setup() {
  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1, RXD0, TXD0);  // U0
  while (!Serial)
    ;
  Serial.println("");

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(100000);  // Set to 100 (default) or 400 kHz

  Serial.println("ESPKnack Bring Up and Test Example Code");
}

// **************** LOOP ****************
void loop() {

  Serial.println("Serial U0");

  // Finally the hour, minute, and second
  Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC);
  Serial.print(" ");
  Serial.print(myRTC.getMinute(), DEC);
  Serial.print(" ");
  Serial.print(myRTC.getSecond(), DEC);

  // Display the temperature
  Serial.print("\tT=");
  Serial.println(myRTC.getTemperature(), 2);

  delay(500);
}