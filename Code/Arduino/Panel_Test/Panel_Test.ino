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
#include <GyverOLED.h>
#include <Adafruit_NeoPixel.h>

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// Define I2C (Expansion Port)
#define I2C_SDA 6
#define I2C_SCL 7

// Hardware Serial 0 GPIO Pins
#define RXD0 17
#define TXD0 16

// RGB
#define PIN_WS2812B 8  // The ESP32-C6 pin GPIO8 connected to WS2812B
Adafruit_NeoPixel ws2812b(1, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

// **************** MIXED MODE INPUT/OUTPUT ****************
#define User_GP02 2


// **************** OUTPUTS ****************
#define LED_Red 22  // Red LED

// OLED Instance. You will need to select your OLED Display. 
// Uncomment/Comment as needed.
GyverOLED<SSD1306_128x32, OLED_BUFFER> oled;  //0.6"
//GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
// GyverOLED<SSH1106_128x64> oled; //1.1"

// Draw Battery
void drawBattery(byte percent) {
  oled.drawByte(0b00111100);
  oled.drawByte(0b00111100);
  oled.drawByte(0b11111111);
  for (byte i = 0; i < 100 / 8; i++) {
    if (i < (100 - percent) / 8) oled.drawByte(0b10000001);
    else oled.drawByte(0b11111111);
  }
  oled.drawByte(0b11111111);
}

// **************** SETUP ****************
void setup() {
  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1, RXD0, TXD0);  // U0
  while (!Serial)
    ;
  Serial.println("");

  // Initialise RED LED on GP22
  pinMode(LED_Red, OUTPUT);

  // Configure GPIO Inputs (Default)
  pinMode(User_GP02, INPUT_PULLUP);

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  ws2812b.begin();  // Initialize WS2812B
  ws2812b.clear();  // Turn off RGB

  Serial.println("ESPKnack Bring Up and Test Example Code");
}

void loop() {

  // Turn off RGB
  ws2812b.clear();
  ws2812b.show();

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(15, 0);
  oled.setScale(2);
  oled.print("ESPKnack");
  oled.update();
  delay(500);

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

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(15, 1);
  oled.setScale(2);
  oled.print("ESPKnack");
  oled.update();
  delay(500);

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(15, 2);
  oled.setScale(2);
  oled.print("ESPKnack");
  oled.update();
  delay(500);

  // RED
  ws2812b.setPixelColor(0, ws2812b.Color(50, 0, 0));
  ws2812b.show();
  delay(500);

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(30, 1);
  oled.setScale(3);
  oled.print("LoRa");
  oled.update();

  // Turn off RGB
  ws2812b.clear();
  ws2812b.show();  // update to the WS2812B Led Strip

  // BLUE
  ws2812b.setPixelColor(0, ws2812b.Color(0, 0, 50));
  ws2812b.show();
  delay(500);

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(15, 1);
  oled.setScale(2);
  oled.print("ESPKnack");
  oled.update();
  delay(500);

  // Turn off RGB
  ws2812b.clear();
  ws2812b.show();

  // GREEN
  ws2812b.setPixelColor(0, ws2812b.Color(0, 50, 0));
  ws2812b.show();
  delay(500);

  // Turn off RGB
  ws2812b.clear();
  ws2812b.show();

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(30, 1);
  oled.setScale(3);
  oled.print("LoRa");
  oled.update();

  delay(500);

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(20, 1);
  oled.setScale(3);
  oled.print("RS485");
  oled.update();

  delay(500);

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(19, 1);
  oled.setScale(3);
  oled.print("5-60V");
  oled.update();

  delay(500);

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(15, 0);
  oled.setScale(2);
  oled.print("ESPKnack");
  oled.update();
  delay(500);

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(15, 1);
  oled.setScale(2);
  oled.print("ISO GPIO");
  oled.update();
  delay(500);

  // GP LED - Mixed Mode GPIO
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

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(15, 2);
  oled.setScale(2);
  oled.print("ISO GPIO");
  oled.update();
  delay(500);

  delay(500);

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(13, 1);
  oled.setScale(2);
  oled.print("ISO GPIO");
  oled.update();

  delay(500);

  // Heatbeat LED
  digitalWrite(LED_Red, HIGH);
  delay(100);
  digitalWrite(LED_Red, LOW);
}
