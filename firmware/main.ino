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

namespace pinSettings {
  const int emmiterPin = 4;

};

namespace deviceStats {

  unsigned long bootTimestamp;
  const bool SERVER_MODE = true;

};

namespace irCodes {
  
  uint16_t power[];
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
void loop(){
    if (SERVER_MODE){
        server_loop()
    }else{
        local_loop()
    }  
}