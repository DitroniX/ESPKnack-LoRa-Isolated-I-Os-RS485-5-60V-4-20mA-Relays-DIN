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
#include <Arduino.h>
#include <TCA6408A.h>  // Library or see https://github.com/RobTillaart/TCA6408A_RT

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

#define I2C_SDA 6
#define I2C_SCL 7
#define I2C_CLOCK 4000000UL

TCA6408A tca(0x21);

// **************** OUTPUTS ****************
#define LED_Red 22  // Red LED

// **************** FUNCTIONS AND ROUTINES ****************

// **************** SETUP ****************
void setup() {
  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1);  // 115200
  while (!Serial)
    ;
  Serial.println("");

  // Initialise I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(I2C_CLOCK);  // 400kHz | Standard-mode (Sm) and Fast-mode (Fm) which can go up to 100kHz and 400kHz respectively

  // Configures the specified LED GPIO as outputs
  pinMode(LED_Red, OUTPUT);

  // LEDs Default Off State
  digitalWrite(LED_Red, LOW);

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(100000);  // Set to 100 (default) or 400 kHz

  if (tca.begin() == false) {
    Serial.println("No TCA found.");
    while (1)
      ;
  }

  //  Set 4-7 pins as outputs
  tca.setPinMode8(0x0F);

  //  Set all pins to OFF
  tca.digitalWrite8(0x00);

  Serial.println("ESPKnack Bring Up and Test Example Code");
}

// **************** LOOP ****************
void loop() {

  // TCA6408 Outputs
  // P4 = OPTO
  // P5 = P5
  // P6 = Relay 2
  // P7 = Relay 1

  tca.digitalWrite1(7, 1);

  delay(1000);
  tca.digitalWrite1(7, 0);

  // Red
  digitalWrite(LED_Red, HIGH);
  delay(50);
  digitalWrite(LED_Red, LOW);
  delay(250);
}
//