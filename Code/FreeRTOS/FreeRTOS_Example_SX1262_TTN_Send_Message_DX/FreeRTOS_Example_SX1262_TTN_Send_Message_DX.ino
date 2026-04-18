/*
  Dave Williams, DitroniX 2019-2026 (ditronix.net)
  ESPKnack - IoT ESP32-C6 Based Home and Industrial Controller SDK
  Features include ESP32-C6, LoRa, Isolated I/Os, RS485, 5-60V, 4-20mA, Relays, DIN SDK

  Basic Bring Up Test Code - April 2026
 
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

// See Wiki https://github.com/DitroniX/ESPKnack-LoRa-Isolated-I-Os-RS485-5-60V-4-20mA-Relays-DIN/wiki/FreeRTOS-Example


// ==================== Purpose ====================

// Code Purpose
// This code is based on a GROK generation but then manually updated
// Setup LoRa as a device.  Remember to add your device TTN info!!
// Fixed GPS Location
// Button Press - Send LoRa Message
// Heartbeat, 10 Mins, Send LoRa Message
// RS485 Receive Byte and Send Message

// ==================== Config ====================

/*
 * ESP32-C6 Threaded LoRaWAN (TTN) Example with SX1262 + Button + RS485
 * 
 * Hardware:
 *   SX1262 LoRa:
 *     MOSI -> GPIO 18
 *     MISO -> GPIO 20
 *     SCLK -> GPIO 19
 *     CS   -> GPIO 14
 *     BUSY -> GPIO 3
 *     INT  -> GPIO 1   (DIO1 / IRQ)
 *     nRST -> GPIO 21
 * 
 *   Button (active-low with internal pull-up) -> GPIO 9
 *   LED -> GPIO 22
 * 
 *   RS485 UART (9600 baud, receive-only):
 *     RXD -> GPIO 4
 *     TXD -> GPIO 5
 *     EN/DE/RE -> GPIO 23  (set LOW for RX mode)
 * 
 * Behavior:
 *   - Button press OR any data received on RS485 → flash LED + send uplink to TTN
 *   - Uses FreeRTOS tasks (threaded) for button, RS485, and LoRaWAN handling
 *   - RadioLib for SX1262 + LoRaWAN (OTAA)
 * 
 * Requirements:
 *   - Arduino-ESP32 core with ESP32-C6 board selected
 *   - RadioLib library (install via Library Manager: "RadioLib" by jgromes)
 *   - Register device on TTN (The Things Network) and fill DevEUI / keys below
 *   - Change EU868 to your region if needed (US915, AU915, etc.)
 * 
 * Compile & upload with default Arduino IDE settings for ESP32-C6.
 */

#include <Arduino.h>
#include <RadioLib.h> // You will need to add this within the Library, if not already installed
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

// ==================== PIN DEFINITIONS ====================
const uint8_t LORA_CS   = 14;
const uint8_t LORA_INT  = 1;   // DIO1
const uint8_t LORA_RST  = 21;
const uint8_t LORA_BUSY = 3;

const uint8_t SPI_MOSI = 18;
const uint8_t SPI_MISO = 20;
const uint8_t SPI_SCLK = 19;

const uint8_t BUTTON_PIN = 9;
const uint8_t LED_PIN    = 22;

const uint8_t RS485_RX   = 4;
const uint8_t RS485_TX   = 5;
const uint8_t RS485_EN   = 23;
const uint32_t RS485_BAUD = 9600;

// ==================== FIXED GPS LOCATION ====================
// ←←← CHANGE THESE TO YOUR DESIRED FIXED COORDINATES ←←←
const float FIXED_LAT = 51.29848;   // Example: 52.370216 Amsterdam
const float FIXED_LON = 0.58556;   // Example: 4.895168 Amsterdam
const float FIXED_ALT = 200.0;        // meters (optional)

// ==================== TTN ====================

// TTN Device Example Setup
// Frequency plan Europe 863-870 MHz (SF9 for RX2 - recommended)
// LoRaWAN version LoRaWAN Specification 1.1.0
// Regional Parameters version RP002 Regional Parameters 1.0.4

// ==================== TTN CONFIG - CHANGE THESE ====================
uint64_t joinEUI = 0x0000000000000000ULL;     // e.g. 0x0000000000000000ULL - Usually all zeros for TTN

// ←←← REPLACE WITH YOUR REAL DevEUI (exactly 16 hex digits + ULL) ←←←
uint64_t devEUI  = 0x70B3D57ED0076FF1ULL;     // e.g. 0x0000000000000000ULL;

// uint8_t appKey[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; // ← CHANGE (AppKey)

uint8_t appKey[16] = {0xA6, 0x77, 0x97, 0x0D, 0xB5, 0xA6, 0xFF, 0x27, 0xCC, 0x8B, 0x6E, 0x55, 0x3E, 0x2A, 0xA3, 0x16};

// uint8_t nwkKey[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; // ← CHANGE (NwkKey)

uint8_t nwkKey[16] = {0xAC, 0x39, 0x7C, 0x5F, 0x7A, 0xD4, 0xFD, 0x98, 0x99, 0xA9, 0x7C, 0x16, 0x41, 0x60, 0x5A, 0x66};

LoRaWANBand_t band = EU868;   // Change to US915, AU915, AS923_1 etc. if needed

// Radio & Node
SX1262 radio = new Module(LORA_CS, LORA_INT, LORA_RST, LORA_BUSY);
LoRaWANNode node(&radio, &band);

uint32_t uplinkCounter = 0;
SemaphoreHandle_t triggerSemaphore = NULL;
TimerHandle_t heartbeatTimer = NULL;

// ==================== ERROR HELPER ====================
const char* getRadioLibError(int16_t code) {
  switch (code) {
    case RADIOLIB_ERR_NONE:                    return "Success";
    case RADIOLIB_ERR_CHIP_NOT_FOUND:          return "Chip not found";
    case RADIOLIB_ERR_NO_JOIN_ACCEPT:          return "No Join Accept (-1116)";
    case RADIOLIB_ERR_NETWORK_NOT_JOINED:      return "Network not joined (-1102)";
    case RADIOLIB_LORAWAN_NEW_SESSION:         return "New OTAA session created";
    default:
      if (code >= RADIOLIB_ERR_NONE) return "Success";
      return "Unknown error";
  }
}

// ==================== HEARTBEAT (10 minutes) ====================
void heartbeatCallback(TimerHandle_t xTimer) {
  (void)xTimer;
  Serial.println(F("[Heartbeat] 10 min → sending fixed location"));
  xSemaphoreGive(triggerSemaphore);
}

// ==================== TASKS ====================

void buttonTask(void *pvParameters) {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  bool lastState = HIGH;

  while (true) {
    bool state = digitalRead(BUTTON_PIN);
    if (state == LOW && lastState == HIGH) {
      vTaskDelay(pdMS_TO_TICKS(50));
      if (digitalRead(BUTTON_PIN) == LOW) {
        digitalWrite(LED_PIN, HIGH); vTaskDelay(pdMS_TO_TICKS(120));
        digitalWrite(LED_PIN, LOW);  vTaskDelay(pdMS_TO_TICKS(80));
        digitalWrite(LED_PIN, HIGH); vTaskDelay(pdMS_TO_TICKS(120));
        digitalWrite(LED_PIN, LOW);

        Serial.println(F("[Button] Pressed → trigger fixed GPS uplink"));
        xSemaphoreGive(triggerSemaphore);
      }
    }
    lastState = state;
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void rs485Task(void *pvParameters) {
  pinMode(RS485_EN, OUTPUT);
  digitalWrite(RS485_EN, LOW);

  HardwareSerial rs485(1);
  rs485.begin(RS485_BAUD, SERIAL_8N1, RS485_RX, RS485_TX);

  while (true) {
    if (rs485.available()) {
      while (rs485.available()) rs485.read();

      digitalWrite(LED_PIN, HIGH); vTaskDelay(pdMS_TO_TICKS(150));
      digitalWrite(LED_PIN, LOW);  vTaskDelay(pdMS_TO_TICKS(100));
      digitalWrite(LED_PIN, HIGH); vTaskDelay(pdMS_TO_TICKS(150));
      digitalWrite(LED_PIN, LOW);

      Serial.println(F("[RS485] Data received → trigger fixed GPS uplink"));
      xSemaphoreGive(triggerSemaphore);
      vTaskDelay(pdMS_TO_TICKS(300));
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void loraTask(void *pvParameters) {
  while (true) {
    if (xSemaphoreTake(triggerSemaphore, portMAX_DELAY) == pdTRUE) {
      Serial.println(F("\n[LoRaWAN] Trigger received - sending fixed location"));

      if (!node.isActivated()) {
        Serial.println(F("[LoRaWAN] Joining TTN..."));
        int16_t joinState = node.activateOTAA();
        Serial.printf("[Join] %s (code %d)\n", getRadioLibError(joinState), joinState);
        if (joinState != RADIOLIB_LORAWAN_NEW_SESSION) continue;
      }

      // Build payload with fixed GPS location
      char payload[128];
      snprintf(payload, sizeof(payload),
               "Hello, Lat: %.6f, Lon: %.6f, Alt: %.1fm",
               FIXED_LAT, FIXED_LON, FIXED_ALT);

      size_t len = strlen(payload);
      int16_t state = node.sendReceive((const uint8_t*)payload, len, 1, false);  // port 1, unconfirmed

      if (state >= RADIOLIB_ERR_NONE) {
        Serial.printf("[LoRaWAN] Fixed location uplink sent: %s\n", payload);
      } else {
        Serial.printf("[LoRaWAN] Uplink FAILED: %s (code %d)\n", getRadioLibError(state), state);
      }
    }
  }
}

// ==================== SETUP ====================
void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println(F("\n=== ESP32-C6 SX1262 TTN - SF9 + FIXED GPS Location + Heartbeat ==="));
  Serial.printf("Fixed Location: Lat %.6f, Lon %.6f, Alt %.1fm\n", FIXED_LAT, FIXED_LON, FIXED_ALT);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  SPI.begin(SPI_SCLK, SPI_MISO, SPI_MOSI);

  Serial.print(F("[SX1262] Initializing... "));
  int16_t state = radio.begin();
  Serial.printf("%s (code %d)\n", getRadioLibError(state), state);

  if (state != RADIOLIB_ERR_NONE) {
    while (true) { digitalWrite(LED_PIN, !digitalRead(LED_PIN)); delay(200); }
  }

  // SF9 configuration
  radio.setSpreadingFactor(9);
  node.setADR(false);
  node.setDatarate(3);        // DR3 = SF9 / BW125

  Serial.print(F("[LoRaWAN] Initializing OTAA... "));
  state = node.beginOTAA(joinEUI, devEUI, nwkKey, appKey);
  Serial.printf("%s (code %d)\n", getRadioLibError(state), state);

  triggerSemaphore = xSemaphoreCreateBinary();

  // 10-minute heartbeat timer
  heartbeatTimer = xTimerCreate("Heartbeat", pdMS_TO_TICKS(10 * 60 * 1000), pdTRUE, NULL, heartbeatCallback);
  xTimerStart(heartbeatTimer, 0);
  Serial.println(F("[Heartbeat] 10-minute timer started"));

  // Start tasks
  xTaskCreate(buttonTask, "Button",  4096, NULL, 1, NULL);
  xTaskCreate(rs485Task,  "RS485",   4096, NULL, 1, NULL);
  xTaskCreate(loraTask,   "LoRaWAN", 8192, NULL, 2, NULL);

  Serial.println(F("All tasks started. Using fixed GPS location."));
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}