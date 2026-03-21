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
#include <Arduino.h>
#include <Wire.h>

// ****************  VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// ******************************** DATA ********************************

// Define I2C (Expansion Port)
#define I2C_SDA 6
#define I2C_SCL 7
#define I2C_CLOCK 4000000UL

// TCA6408A
#define TCA6408A_ADDR 0x21
#define REG_INPUT 0x00
#define REG_OUTPUT 0x01
#define REG_POLARITY 0x02
#define REG_CONFIG 0x03

// **************** INSTANCES ****************


// **************** FUNCTIONS AND ROUTINES ****************

void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(TCA6408A_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(TCA6408A_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)TCA6408A_ADDR, (uint8_t)1);
  return Wire.available() ? Wire.read() : 0xFF;
}

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

  // Set P0–P3 as inputs, P4–P7 as outputs
  writeRegister(REG_CONFIG, 0x0F);  // 0x0F 00001111

  // Invert input polarity (so pressing button = 1)
  writeRegister(REG_POLARITY, 0x0F);  // 00001111

  // Initialize outputs to off (all LEDs off)
  writeRegister(REG_OUTPUT, 0x0F);

  Serial.println("ESPKnack Bring Up and Test Example Code");
}

// **************** LOOP ****************
void loop(void) {

  // Read inputs
  uint8_t input = readRegister(REG_INPUT) & 0x0F;

  // Shift input bits to upper nibble to drive P4–P7
  uint8_t output = input << 4;

  output = 0xff;
  writeRegister(REG_OUTPUT, output);
  delay(500);

  output = 0x00;
  writeRegister(REG_OUTPUT, output);
  delay(100);

  // Write to output register
  writeRegister(REG_OUTPUT, output);

  // Print input/output states
  Serial.print("Inputs (P0–P3): ");
  Serial.print(input, BIN);

  Serial.print(" | Outputs (P4–P7): ");
  Serial.println(output >> 4, BIN);
  // Serial.println(0xFF >> 4, BIN);

  delay(500);
}
