/*
 * Firmware - Klinus
 * https://github.com/diaslui/klinus/
 * Copyright 2025 Pedro Luis Dias
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


//#include <config.hpp>
#include <IRremote.hpp>
#include <WiFi.h>


const char* ssid = "yourNetworkName";
const char* password = "yourNetworkPassword";

const int sPin = 4;

bool connectToWifi(char *ssid, char *password){

  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 3000) {
      delay(100);
  }
  return WiFi.status() == WL_CONNECTED;

};

bool emitIRaw(uint16_t rawData[], size_t length) {
  IrSender.sendRaw(rawData, length, 38);
  return true;
}

int SERVER_MODE = true;


void setup(){
  Serial.begin(115200);
  IrSender.begin(sPin); 

  if (SERVER_MODE){

    WiFi.mode(WIFI_STA);
    connectToWifi(ssid, password);

    return;
  }
    Serial.println("Starting in Local Mode (DEV)");


}

void loop(){

    if (SERVER_MODE){
        Serial.println("Server Mode");
    }else{
        Serial.println("Local Mode");

    }


    
}