/*
  Dave Williams, DitroniX 2019-2026 (ditronix.net)
  ESPKnack - IoT ESP32-C6 Based Home and Industrial Controller SDK
  Features include ESP32-C6, LoRa, Isolated I/Os, RS485, 5-60V, 4-20mA, Relays, DIN SDK

  PCA 1.2603 - Basic Bring Up Test Code - March 2026
 
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

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

#include <Wire.h>

// **************** OUTPUTS ****************
#define LED_Red 22  // Red LED

// Hardware Serial 0 pins
#define RXD0 17
#define TXD0 16

// Hardware Serial 1 pins - RS485
#define RXLP 4
#define TXLP 5
#define ENLP 23  // RS485 UART Enable

// **************** FUNCTIONS AND ROUTINES ****************

// **************** SETUP ****************
void setup() {

  // Stabalise
  delay(250);

  // Initialise UART 0 - USB COM Port
  Serial.begin(115200, SERIAL_8N1, RXD0, TXD0);  // U0
  while (!Serial)
    ;
  Serial.println("UART 0 Opened (USB COM Port)");

  // Initialise UART 1 - RS485 Port
  Serial1.begin(9600, SERIAL_8N1, RXLP, TXLP);  //LP
  while (!Serial)
    ;

  Serial.println("UART 1 Opened (RS485 Port)");

  // Initialise RED LED on GP22
  pinMode(LED_Red, OUTPUT);

  // Initialise RS485 UART RX Enable on GP23
  pinMode(ENLP, OUTPUT);

  Serial.println("ESPKnack Bring Up and Test Example Code");
  Serial.println("Running RS485 RX Test");
}

// **************** LOOP ****************
void loop() {

  // Force RS485 UART Driver Disabled and Receiver is Enabled
  digitalWrite(ENLP, LOW);

  if (Serial1.available() > 0) {

    // Read Incomming Byte from RS485 UART and Output to the Serial Monitor
    char incomingbyte = Serial1.read();
    Serial.print(incomingbyte);

    // Heartbeat RED LED
    digitalWrite(LED_Red, HIGH);
    delay(150);
    digitalWrite(LED_Red, LOW);
  }
}
