/*
 * Firmware - Klinus
 * https://github.com/diaslui/klinus/
 * Copyright 2025 Pedro Luis Dias & Victor Manuel Leal Ribeiro
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *  https://github.com/diaslui/klinus/blob/main/LICENSE
 */

#define MONITOR_SERIAL Serial
#define RADAR_SERIAL Serial1
#define RADAR_RX_PIN 4
#define RADAR_TX_PIN 5


const int DEVICE_ID = 10;


#define SERVICE_UUID        "06924101-0420-0666-1234-13124110" + DEVICE_ID + String("la")
#define CHARACTERISTIC_UUID "05318008-2010-9405-4321-08008135" + String("la")

#include <IRremote.hpp>
#include <WiFi.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEClient.h>
#include <ld2410.h>

ld2410 radar;


uint32_t lastReading = 0;
bool isPowerOn = false;

uint32_t lastMoviment = 0;
int movimentLimitCM = 5 * 100;
int stationaryLimitCM = 5  * 100;

uint32_t windowStart = 0;
uint32_t windowDuration = 10000; 
unsigned long detections = 0;
unsigned long totalReads = 0;



BLEAdvertisedDevice* myDevice;
BLERemoteCharacteristic* pRemoteCharacteristic;
bool bleConnected = false;


class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(BLEUUID(SERVICE_UUID))) {
      Serial.println("ble pair found!");
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      BLEDevice::getScan()->stop();
    }
  }
};


static void notifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic,
                           uint8_t* pData, size_t length, bool isNotify) {
  int msg = (pData[0] << 8) | pData[1];

  Serial.print("new msg: ");
  Serial.println(msg);
}



void connectToServer() {
  Serial.println("try to connect...");
  BLEClient* pClient = BLEDevice::createClient();
  if (!pClient->connect(myDevice)) {
    Serial.println("fail to connect!");
    return;
  }
  Serial.println("connected with Peripheral!");

  BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
  if (pRemoteService == nullptr) {
    Serial.println("Service not founded!");
    return;
  }
  Serial.println("Service founded!");

  pRemoteCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.println("Characteristic not founded!");
    return;
  }
  Serial.println("Characteristic founded!");

  if(pRemoteCharacteristic->canNotify()) {
    pRemoteCharacteristic->registerForNotify(notifyCallback);
    Serial.println("Notifications enabled!");
  }

  bleConnected = true;
}



const char* ssid = "yourNetworkName";
const char* password = "yourNetworkPassword";

namespace pinSettings {
  const int emmiterPin = 4;

};

namespace deviceStats {

  unsigned long bootTimestamp;
  const bool SERVER_MODE = true;

};

namespace irCodes {
  
  uint16_t power[][16];
  uint16_t upTemperature[][32];
  uint16_t downTemperature[][32];

};



bool emitIRaw(uint16_t rawData[], size_t length) {
  IrSender.sendRaw(rawData, length, 38);
  return true;
}



void setup(){
  Serial.begin(115200);
  deviceStats::bootTimestamp = millis();
  IrSender.begin(pinSettings::emmiterPin); 
  BLEDevice::init("");

  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);



  if (SERVER_MODE){

    WiFi.mode(WIFI_STA);
    connectToWifi(ssid, password);
  }else{

    Serial.println("Starting in Local Mode (DEV)");

  }
}


bool allowedInterval(){




}



void local_loop(){


  bool has_present = true;

  if (has_present){

    if (allowedInterval()){

      // ligar o ar 
      // liga o ar
      // 
      


    }else{



    }

  }else{



  }

 /// verificação de presença


 // se presente 





}


void server_loop(){}


bool sendBleMessage(int msgCode) {
  if (bleConnected && pRemoteCharacteristic != nullptr) {
    pRemoteCharacteristic->writeValue(msgCode);
    return true;
  }
  return false;
}


void loop(){
   if (myDevice && !bleConnected) {
    connectToServer();
  }
    if (SERVER_MODE){
        server_loop()
    }else{
        local_loop()
    }  
}