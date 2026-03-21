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

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// Define I2C (Expansion Port)
#define I2C_SDA 6
#define I2C_SCL 7

// **************** FUNCTIONS AND ROUTINES ****************

// I2C Bus Scanner
void ScanI2CBus()
{

  // Useful Reference https://i2cdevices.org/addresses

  byte error, address;
  int nDevices;

  Serial.println("Scanning I2C Bus for Devices for Auto Configuration ...\n");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    nDevices++;
    if (nDevices == 1)
      Serial.println(" I2C Possible Device(s) found at Address:");
    if (error == 0)
    {
      Serial.print(" * Hex 0x");
      Serial.print(address, HEX);

      Serial.print(" (");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(")\t");

      switch (address)
      {
      case 0x21:
        Serial.print(" TCA6408A GPIO Expander");
        break;
      case 0x48:
        Serial.print(" TLA2024 12-bit ADC");
        break;
      case 0x4A:
        Serial.print(" TMP102 Temperature Sensor");
        break;
      case 0x49:
        Serial.print(" ADS1115 16-bit ADC");
        break;
      case 0x3C ... 0x3D:
        Serial.print(" OLED");
        break;
      case 0x50:
        Serial.print(" EEPROM");
        break;
      case 0x55:
        Serial.print(" EEPROM IPEM PiHat");
        break;
      case 0x58:
        Serial.print(" EEPROM (Reserved Address)");
        break;
      case 0x60 ... 0x62:
        Serial.print(" MCP4728 12-bit DAC");
        break;
      case 0x68:
        Serial.print(" DS3231 RTC");
        break;     
      case 0x71 ... 0x77:
        Serial.print(" PCA9671 GPIO Expander");
        break;
      case 0x7C:
        Serial.print(" PCA9671 GPIO Expander (Reserved Address)");
        break;
      default:
        Serial.print(" ?");
        break;
      }
      Serial.println();
    }
    else if (error == 4)
    {
      Serial.print(" * Unknown error at address Decimal ");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(" = Hex 0x");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println(" * No I2C devices found. Possible Hardware Issue?");
  }
  else
  {
    Serial.println(" I2C Bus Scan Complete\n");
  }
} // ScanI2CBus

// **************** SETUP ****************
void setup()
{

  // Stabalise (Optional)
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1); // 115200
  while (!Serial)
    ;
  Serial.println("");

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  Serial.println("ESPKnack Bring Up and Test Example Code");

  ScanI2CBus();
}

// **************** LOOP ****************
void loop()
{
}
