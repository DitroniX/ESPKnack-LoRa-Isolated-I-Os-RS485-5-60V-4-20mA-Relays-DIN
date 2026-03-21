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
#include <WiFi.h>

// ****************  VARIABLES / DEFINES / STATIC ****************

// Constants
int WifiMaxAPScan = 8;  // Multiple WiFi Scan Maximum APs (Default 8)

WiFiClient client;  // Initialize the client library

char buffer[20];

// Return Some Meaningful Information From RSSI
String RSSI_Info(int RSSI_Value) {
  switch (-RSSI_Value)  // Inverted dBm Level ;)
  {
    {
      case 0 ... 30:
        return "Signal Very Strong";
        break;
      case 31 ... 50:
        return "Signal Excellent";
        break;
      case 51 ... 60:
        return "Signal Healthy";
        break;
      case 61 ... 70:
        return "Signal Very Good";
        break;
      case 71 ... 80:
        return "Signal Good";
        break;
      case 81 ... 90:
        return "Signal Poor - Try Moving Position";
        break;
      case 91 ... 100:
        return "Signal Very Low! - Move Position";
        break;
      default:
        return "No Signal :(";
        break;
    }
  }

}  // RSSI_Info

void setup() {

  // Stabalise
  delay(250);

  // Initialize UART:
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial)
    ;

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.println("ESPKnack Bring Up and Test Example Code");
}

void loop() {

  Serial.println("\nESPKnack WiFi MAC \t " + WiFi.macAddress());
  Serial.println("Scanning for Access Points, or Routers.  Please wait....");
  delay(100);

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.print("Scan Complete.  ");

  if (n == 0) {
    Serial.println("No Access Points, or Routers, Found.");
  } else {
    Serial.print(n);
    Serial.println(" Access Points, or Routers, Found.");
    Serial.println("");

    for (int i = 0; i < n; ++i) {

      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(":");
      sprintf(buffer, "% 18s", WiFi.SSID(i));
      Serial.print(buffer);
      Serial.print("\t(");
      Serial.print("WiFi RSSI " + String(WiFi.RSSI(i)) + " dBm (" + RSSI_Info(WiFi.RSSI(i)) + ")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");

      // Do Not Unnecessarily Dither - Scan first X Access Points Only
      if (i >= (WifiMaxAPScan - 1))
        break;
    }
  }

  delay(2000);
}
