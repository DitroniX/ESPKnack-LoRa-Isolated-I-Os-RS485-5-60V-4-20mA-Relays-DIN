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

// This code is for the ESPKnack with Panel

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// **************** MIXED MODE INPUT/OUTPUT ****************
#define User_GP02 2

// **************** SETUP ****************
void setup() {

  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1);  // 115200
  while (!Serial)
    ;
  Serial.println("");

  // Configure GPIO Inputs (Default)
  pinMode(User_GP02, INPUT_PULLUP);

  Serial.println("ESPKnack Bring Up and Test Example Code");
  Serial.println("Ready for Input");
}

// **************** LOOP ****************
void loop() {

  // Check for Button Press
  if (digitalRead(User_GP02) == LOW) {

    Serial.println("User User_GP02");

    pinMode(User_GP02, OUTPUT);

    // Red Panel LED
    digitalWrite(User_GP02, LOW);
    delay(500);
    digitalWrite(User_GP02, HIGH);
    delay(500);
    digitalWrite(User_GP02, LOW);
    delay(500);
    digitalWrite(User_GP02, HIGH);
    delay(500);
    digitalWrite(User_GP02, LOW);
    delay(500);
    digitalWrite(User_GP02, HIGH);

    pinMode(User_GP02, INPUT_PULLUP);
  }
}
