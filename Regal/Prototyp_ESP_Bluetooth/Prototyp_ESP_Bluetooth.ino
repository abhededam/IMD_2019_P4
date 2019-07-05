
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

//iBeacon Adresse: 54:4a:16:38:8c:2d

String korbAddress = "54:4a:16:38:8c:2d";



int scanTime = 5; //In seconds
static BLEAddress *ScannedServerAddress;
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      ScannedServerAddress = new BLEAddress(advertisedDevice.getAddress());
      bool known = false;
        if (strcmp(ScannedServerAddress->toString().c_str(), korbAddress.c_str()) == 0){
          known = true;
        }
      if(known){
        Serial.println(advertisedDevice.getRSSI());
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
 /* Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("Scan done!");*/
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(500);
}
