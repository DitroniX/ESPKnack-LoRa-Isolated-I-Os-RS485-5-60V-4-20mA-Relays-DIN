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
#include "WiFi.h"
#include "Wire.h"
#include "I2C_eeprom.h"
#include <TCA6408A.h>  // Library or see https://github.com/RobTillaart/TCA6408A_RT
#include <Adafruit_NeoPixel.h>

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// **************** OUTPUTS ****************
#define LED_Red 22  // Red LED
#define PWM_Out 15  // PWM Out

// Hardware Serial 0 pins
#define RXD0 17
#define TXD0 16

// Hardware Serial 1 pins - RS485
#define RXLP 4
#define TXLP 5
#define RS485_EN 23  // RS485 UART Enable

// I2C
#define I2C_SDA 6
#define I2C_SCL 7

// RGB
#define PIN_WS2812B 8  // The ESP32-C6 pin GPIO8 connected to WS2812B
Adafruit_NeoPixel ws2812b(2, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

uint32_t start, duration, totals = 0;

uint64_t chipid = ESP.getEfuseMac();  // Get ChipID (essentially the MAC address)
I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC64);
TCA6408A tca(0x21);

struct
{
  float temperature;
  float humidity;
  float pressure;
} measurement;

// **************** FUNCTIONS AND ROUTINES ****************

// I2C Bus Scanner
void ScanI2CBus() {

  // Useful Reference https://i2cdevices.org/addresses

  byte error, address;
  int nDevices;

  Serial.println("Scanning I2C Bus for Devices for Auto Configuration ...\n");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    nDevices++;
    if (nDevices == 1)
      Serial.println(" I2C Possible Device(s) found at Address:");
    if (error == 0) {
      Serial.print(" * Hex 0x");
      Serial.print(address, HEX);

      Serial.print(" (");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(")\t");

      switch (address) {
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
    } else if (error == 4) {
      Serial.print(" * Unknown error at address Decimal ");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(" = Hex 0x");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println(" * No I2C devices found. Possible Hardware Issue?");
  } else {
    Serial.println(" I2C Bus Scan Complete\n");
  }
}  // ScanI2CBus

void RGB_Test() {
  // RED
  ws2812b.setPixelColor(0, ws2812b.Color(150, 0, 0));
  ws2812b.show();
  delay(250);

  // Turn off RGB
  ws2812b.clear();
  ws2812b.show();  // update to the WS2812B Led Strip
  delay(250);

  // GREEN
  ws2812b.setPixelColor(0, ws2812b.Color(0, 150, 0));
  ws2812b.show();
  delay(250);

  // Turn off RGB
  ws2812b.clear();
  ws2812b.show();
  delay(250);

  // BLUE
  ws2812b.setPixelColor(0, ws2812b.Color(0, 0, 150));
  ws2812b.show();
  delay(250);

  // Turn off RGB
  ws2812b.clear();
  ws2812b.show();  // update to the WS2812B Led Strip
  delay(250);

  // White
  ws2812b.setPixelColor(0, ws2812b.Color(150, 150, 150));
  ws2812b.show();
  delay(250);

  // Turn off RGB
  ws2812b.clear();
  ws2812b.show();  // update to the WS2812B Led Strip
  delay(250);
}

// **************** SETUP ****************
void setup() {

  // Stabalise
  delay(250);

  // Initialise UART 0 - USB COM Port
  Serial.begin(115200, SERIAL_8N1, RXD0, TXD0);  // U0
  while (!Serial)
    ;
  Serial.println("UART 0 Opened (USB COM Port)");

  Serial.println("ESPKnack Bring Up and Test Example Code");

  // RGB
  ws2812b.begin();  // Initialize WS2812B
  ws2812b.clear();  // Turn off RGB for two seconds

  // Turn off RGB
  ws2812b.clear();
  ws2812b.show();
  delay(250);

  RGB_Test();

  // Initialise UART 1 - RS485 Port
  Serial1.begin(9600, SERIAL_8N1, RXLP, TXLP);  //LP
  while (!Serial)
    ;
  Serial.println("UART 1 Opened (RS485 Port)");

  // Initialise RS485 UART Enable on GP23
  pinMode(RS485_EN, OUTPUT);

  // Cycle RS485 EN LED
  digitalWrite(RS485_EN, LOW);
  delay(500);
  digitalWrite(RS485_EN, HIGH);
  delay(500);

  //  Configures the specified LED GPIO as outputs
  pinMode(LED_Red, OUTPUT);

  // LEDs Default Off State
  digitalWrite(LED_Red, LOW);

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.setClock(100000);  // Set to 100 (default) or 400 kHz

  ScanI2CBus();

  // Init GPIO Matrix
  if (tca.begin() == false) {
    Serial.println("No TCA found.");
    while (1)
      ;
  }

  // Initialize EEPROM
  ee.begin();
  if (!ee.isConnected()) {
    Serial.println("ERROR: Can't find eeprom (stopped)...");
  }

  Serial.print("Size of Measurement: \t");
  Serial.println(sizeof(measurement));

  Serial.print("\n");

  // Clear Measurements Struct
  measurement.temperature = 0;
  measurement.humidity = 0;
  measurement.pressure = 0;

  // Read Measurements from EEPROM
  start = micros();
  ee.readBlock(0, (uint8_t *)&measurement, sizeof(measurement));
  duration = micros() - start;
  Serial.print("EEPROM Read: \t");
  Serial.println(duration);
  delay(10);

  Serial.println("\nMock Example Measurements\n");

  Serial.print("Temperature:\t");
  Serial.println(measurement.temperature);
  Serial.print("Humidity:\t");
  Serial.println(measurement.humidity);
  Serial.print("Pressure:\t");
  Serial.println(measurement.pressure);

  Serial.print("\n");

  // Write Test
  totals = 0;
  Serial.print("Test timing writeByte\t");
  start = micros();
  ee.writeByte(10, 1);
  duration = micros() - start;
  Serial.print("TIME: ");
  Serial.println(duration);
  totals += duration;

  // Read Test
  Serial.print("Test timing readByte\t");
  start = micros();
  ee.readByte(10);
  duration = micros() - start;
  Serial.print("TIME: ");
  Serial.println(duration);
  totals += duration;

  Serial.print("Test Timing Total\tTIME: ");
  Serial.println(totals);


  // GPIO Matrix
  //  Set 4-7 pins as outputs
  tca.setPinMode8(0x0F);

  //  Set all pins to OFF
  tca.digitalWrite8(0x00);

  // WiFI
  WiFi.mode(WIFI_MODE_STA);

  Serial.print("ESPKnack MAC Address:\t");
  Serial.println(WiFi.macAddress());

  Serial.printf("ESPKnack Serial ID:\t%04X", (uint16_t)(chipid >> 32));
  Serial.printf("%08X", (uint32_t)chipid);
  Serial.println("");
}

// **************** LOOP ****************
void loop() {

  // Force RS485 UART Driver Enable and Receiver is Disabled
  digitalWrite(RS485_EN, HIGH);
  Serial1.write("Hello World - Test\n");


  // PWM
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(PWM_Out, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(5);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(PWM_Out, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(5);
  }

  // GPIO Matrix Test
  for (int pin = 4; pin <= 7; pin++) {
    tca.digitalWrite1(pin, 1);
    Serial.println(pin);
    delay(1000);

    //  Set all pins to OFF
    tca.digitalWrite8(0x00);
  }

  RGB_Test();

  // Red
  digitalWrite(LED_Red, HIGH);
  delay(250);
  digitalWrite(LED_Red, LOW);
}
//