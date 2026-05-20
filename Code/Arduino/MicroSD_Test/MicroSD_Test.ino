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

/*
  This is an extract test code for the Display User Panel MicroSD Test - 
  Complete MicroSD Rui Santos software project details at https://RandomNerdTutorials.com/esp32-microsd-card-arduino/
*/

// Libraries
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "FS.h"
#include "SD.h"

// **************** USER VARIABLES / DEFINES / STATIC / STRUCTURES / CONSTANTS ****************

// SPI Configuration
#define MOSI 18
#define MISO 20
#define SCLK 19
#define CS_EXT 13

// **************** FUNCTIONS AND ROUTINES ****************

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char *path) {
  Serial.printf("Creating Dir: %s\n", path);
  if (fs.mkdir(path)) {
    Serial.println("Directory Created");
  } else {
    Serial.println("mkdir failed");
  }
}

void removeDir(fs::FS &fs, const char *path) {
  Serial.printf("Removing Directory: %s\n", path);
  if (fs.rmdir(path)) {
    Serial.println("Directory Removed");
  } else {
    Serial.println("rmdir failed");
  }
}

void readFile(fs::FS &fs, const char *path) {
  Serial.printf("Reading File: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File Written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message Appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void renameFile(fs::FS &fs, const char *path1, const char *path2) {
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File Renamed");
  } else {
    Serial.println("Rename failed");
  }
}

void deleteFile(fs::FS &fs, const char *path) {
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path)) {
    Serial.println("File Deleted");
  } else {
    Serial.println("Delete failed");
  }
}

void testFileIO(fs::FS &fs, const char *path) {
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if (file) {
    len = file.size();
    size_t flen = len;
    start = millis();
    while (len) {
      size_t toRead = len;
      if (toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u bytes read for %u ms\n", flen, end);
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }


  file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  size_t i;
  start = millis();
  for (i = 0; i < 2048; i++) {
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
  file.close();
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

  delay(250);  // Allow time for SD card to settle

  Serial.println("ESPKnack Bring Up and Test Example Code");
  Serial.println("Basic MicroSD Test on SPI Expansion Port");

  SPI.begin(SCLK, MISO, MOSI);

  if (!SD.begin(CS_EXT)) {
    Serial.println("\nCard Mount Failed - Try Re-insert and Press Reset - Please Check Card Inserted and pre-Formatted");
    Serial.println("Large cards (SDXC) are harder for the ESP to mount on first boot compared to standard SDHC cards");
    Serial.println("Possible SC Card 'Cold Boot' Only - After Flashing ESP");
    // Options
    // delay(1000);
    // ESP.restart();
    return;
  }

  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD Card Attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  listDir(SD, "/", 0);
  createDir(SD, "/mydir");
  listDir(SD, "/", 0);

  removeDir(SD, "/mydir");
  listDir(SD, "/", 2);

  writeFile(SD, "/hello.txt", "Hello ");
  appendFile(SD, "/hello.txt", "World!\n");

  readFile(SD, "/hello.txt");

  deleteFile(SD, "/foo.txt");

  renameFile(SD, "/hello.txt", "/foo.txt");
  readFile(SD, "/foo.txt");
  testFileIO(SD, "/test.txt");

  Serial.printf("\nTotal space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("\nUsed space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

// **************** LOOP ****************
void loop() {
}