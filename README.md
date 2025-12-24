## ESPKnack, LoRa, Isolated I/Os, RS485, 5-60V, 4-24mA, Relays, DIN SDK

**Supporting STEM Electronic Internet of Things & Home Automation Technology for Smart Energy Monitoring**

![ESPKnack Features](https://github.com/DitroniX/ESPKnack-LoRa-Isolated-I-Os-RS485-5-60V-4-24mA-Relays-DIN/blob/main/Datasheets%20and%20Information/ESPKnack%20-%20Features.png)

[**For Latest Project Updates - Click Here**](https://github.com/DitroniX/ESPRanger-LoRa-GNSS-GPS-IMU-RS485-60V?tab=readme-ov-file#updates)

## Updates
-   25-12-24  - Alpha Design, Schematics and Layout Topology

## Availability

**ESPKnack** Launching on KickStarter in January

## Feature Overview

### **What is ESPKnack?**

 - **Espressif ESP32-C6 U.FL**
	 - WiFi, Bluetooth, Zigbee and Thread
 - **EByte E22-900MM22S**
	 - LoRa SX1262 module for 868MHz through to 915MHz
 - **Chipanalog CA-IS2092**
	 - Industry Standard Galvanic Isolated RS-485 interface
 - **RTC DS3231SN**
	 - 5V to 3V3 DC SMPS	 	 
 - **4-20mA Current Loop**	 
	 - HCNR200-500E - Galvanic Isolation
 - **ADC ADS1115**
	 - 16bit 4 Channels
 - **TI TMP102**
	 - Digital Temperature
 - **FET 2N7002DW**
	 - PWM/GPIO Output Galvanic Isolation
 - **Relays SRD-05VDC-SL-CC**
	 - 15A 250VAC SPDT - CO - Galvanic Isolation
 - **Siproin SSP9481**
	 - 5 to 60V DC SMPS for wide ranging power input, providing a stable 5V
 - **OnSemi NCP167BMX330**
	 - 5V to 3V3 DC SMPS	 
 - **EEPROM P24C64C**
	 - 64Kbit storage
	 - Two EEPROMs are included, one for ATGM336H and one for the ESP32-C6.

   
### **Where can ESPKnack be used?**

The **ESPKnack** board can be used in a wide range of projects and installations such as:

-   Agriculture
-   Animal Monitoring
-   Automation
-   Commercial
-   Drones
-   Emergency Response
-   Factories
-   Farms
-   FPV Radio Controlled Vehicles
-   Greenhouses
-   Homes
-   Industry
-   Livestock Monitoring
-   LoRa GPS Tracker
-   Makers
-   Mapping
-   Modelling
-   Off Grid Systems
-   Robotics
-   Scientific Research
-   Security
-   Shipping
-   Smart systems
-   Solar Farms
-   STEM Education
-   Surveillance
-   Surveying
-   Tracking
-   Wind Farms

## Features (Preliminary)

### **Radio and U.FL**

**ESPKnack** main MCU is the ESP32-C6 which includes a powerful radio module, opening up a range of IoT applications that include:

#### Wi-Fi 6

-   2.4 GHz (2400 ~ 2483.5 MHz)
-   802.11ax (20 MHz bandwidth)
-   802.11b/g/n (20/40 MHz bandwidth)
-   CE Max EIRP 19.81 dBm

#### Bluetooth

-   2.4 GHz (2400 ~ 2483.5 MHz)
-   Bluetooth LE
-   Bluetooth 5.3
-   Bluetooth Mesh
-   CE Max EIRP 18.46 dBm

#### [Thread](https://www.threadgroup.org/) 1.4

-   2.4 GHz (2405 ~ 2480 MHz)
-   802.15.4
-   Thread Mesh
-   CE Max EIRP 10.29 dBm

#### [Zigbee](https://csa-iot.org/) 3.0

-   2.4 GHz (2405 ~ 2480 MHz)
-   802.15.4
-   Zigbee Mesh
-   CE Max EIRP 10.40 dBm

Zigbee and mesh are expanding in an range of home, farming and industrial applications, so will be interested to see how this develops over time.

### **LoRa and LoRaWAN**

The main focus of the **ESPKnack** board was sensor flexibility and the ability to send this data to the outside world.  LoRa provides a Long Range wireless communication technology.

The **ESPKnack** includes an EByte E22-900MM22S LoRa module, with Semtech SX1262.  This module covers 850 to 930MHz, so allowing the ESPRanger to work in many countries around the World.  

Example [bands](https://www.thethingsnetwork.org/docs/lorawan/frequencies-by-country/):

-   AS923 (AS1) band (920-923 MHz) in Japan, Malaysia, Singapore
-   AS923 (AS2) band (915–928 MHz) in Asia
-   AU915 band (915–928 MHz) in South America
-   CN779 band (779-787 MHz) in China
-   EU868 band (863–870 MHz) in Europe 
-   IN865 band (865-867 MHz) in India
-   KR920 band (920-923 MHz) in Korea
-   RU864 band (864-870 MHz) in Russia
-   US915 band (902–928 MHz) in North America

LoRa networks supported include [TTN](https://www.thethingsnetwork.org/), [Helium](https://www.helium.com/iot), [SkyNet](https://www.skynetiot.io/), [Meshtastic](https://meshtastic.org/), [MeshCore](https://meshcore.co.uk/) and [ChirpStack](https://www.chirpstack.io/).

**LoRa Local Networks**

A LoRa network can be local and self contained.  This includes 'private' networks for company or farm usage.  Examples are:

-   ChirpStack (Open-source LoRaWAN)
-   Meshtastic (Open source, Off-grid, Decentralized, Mesh network)
-   MeshCore (Open source, Multi Platform System)

ChirpStack is an open-source LoRaWAN Network Server, providing a private network. or an integrated network with the wider LoRaWAN such as TTN.

Meshtastic provides a way to connect nodes and propagate messages across an off-gride network.

#### Coverage Examples:

-   [TTN](https://ttnmapper.org/heatmap/)
-   [Helium](https://helium.coveragemap.net/heatmap/)
-   [SkyNet](https://www.skynetiot.io/en/coverage)
-   [ThingsIX](https://thingsix.coveragemap.net/heatmap/)
-   [Meshtastic](https://meshmap.net/) 
-   [Chirpstack](https://www.coveragemap.net/2024/02/28/mapping-with-chirpstack/)

An U.FL antenna connector is provided to allow internal or external antennas to be fitted.

### **RS-485**

To interfacing to other devices shich Smart Meters, Devices and Smart Batteries which have an RS-485 MODBUS interface, the **ESPKnack** includes a standard industry interface which allows you to collect, or control, other devices on the RS-485 bus, using the Galvanic Isolation from the CA-IS2092.

This RS-485 interface could also be used to control local CCTV on remote installations, or even send data from the **ESPKnack** board over a single twisted pair, up to around 1,200 meters (4,000 feet), in distance. Ideal for farms and remote installations.

In addition to RS485, it is possible to use this interface for Lighting Controller or Analyser/monitor control through DMX, or DMX512.

### **Outline Features and Specifications**

Full features to be updated.

### **Programming and Development**

Development is primarily supported through Visual Studio Code (VSCode and PlatformIO) and Arduino IDE. This also includes platforms like Home Assistant via ESPHome.

A range of libraries are already available which support the devices on the **ESPKnack** such as the:

-   ESP32-C6
-   E22-900MM22S (SX1262)
-   EEPROM J1424C64
-   ADS1115
-   TCA6408 
-   OLED Display
-   RS485
-   TMP102
-   WS2812

Code support is available in my existing [GitHub](https://github.com/DitroniX)  [code](https://github.com/DitroniX/ESPRanger-LoRa-GNSS-GPS-IMU-RS485-60V/tree/main/Code).

This is a worldwide community project and is able to be integrated in so many systems.



## **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Code** *(Code examples for Arduino  IDE, PlatformIO)*
 -  **Datasheets and Information** *(Component Datasheets, Schematics, Board Layouts, Photos, Technical Documentation)*
 - **Certification** *(Related Repository Project or Part, Certification Information)*

**Repository Tabs**

 - **Wiki** *(Related Repository Wiki pages and Technical User Information)*
 - **Discussions** *(Related Repository User Discussion Forum)*
 - **Issues** *(Related Repository Technical Issues and Fixes)*

***

We value our Customers, Users of our designs and STEM Communities, all over the World . Should you have any other questions, or feedback to share to others, please feel free to:

* Visit the related [Project](https://github.com/DitroniX?tab=repositories) *plus the related* **Discussions** and **Wiki** Pages.  See tab in each separate repository.
* **Project Community Information** can be found at https://www.hackster.io/DitroniX
* [DitroniX.net Website - Contact Us](https://ditronix.net/contact/)
* **Twitter**: [https://twitter.com/DitroniX](https://twitter.com/DitroniX)
* [Supporting the STEM Projects - BuyMeACoffee](https://www.buymeacoffee.com/DitroniX)
*  **LinkedIN**: [https://www.linkedin.com/in/g8puo/](https://www.linkedin.com/in/g8puo/)

***Dave Williams, Maidstone, UK.***

Electronics Engineer | Software Developer | R&D Support | RF Engineering | Product Certification and Testing | STEM Ambassador

## STEM

**Supporting [STEM Learning](https://www.stem.org.uk/)**

