#include <WiFi.h>
#include <IRremote.hpp>
#include <esp_now.h>

static const uint8_t peerAddress[] = {0x94, 0xA9, 0x90, 0x96, 0xCE, 0x94};
const bool DEBUG = true;
int transmitterPin = 4;

static const uint16_t PowerOnrawData[67] = {
  8930,4420, 580,570, 530,570, 580,570, 530,570,
  580,570, 530,570, 580,570, 530,620, 530,1670,
  580,1670, 580,1670, 530,1720, 530,1670, 580,1670,
  580,570, 530,1720, 530,570, 530,1720, 580,1670,
  530,570, 530,1720, 530,620, 530,570, 530,620,
  530,1720, 530,570, 530,620, 530,1720, 530,570,
  530,1720, 530,1720, 530,1720, 530
};

static const uint16_t PowerOffrawData[67] = {
  8930,4420, 580,570, 530,570, 580,570, 530,570,
  580,570, 530,570, 580,570, 530,620, 530,1670,
  580,1670, 580,1670, 530,1720, 530,1670, 580,1670,
  580,570, 530,1720, 530,570, 530,1720, 580,1670,
  530,570, 530,1720, 530,620, 530,570, 530,620,
  530,1720, 530,570, 530,620, 530,1720, 530,570,
  530,1720, 530,1720, 530,1720, 530
};


int queueValue = 0;


bool reponseInterpreter(int val){

    if (DEBUG){
        Serial.println("Interpreter Solv -> ");

    }

    if (val == 111){
        IrSender.sendRaw(PowerOnrawData, 67, 38); 
        return true;
    }
    else if (val == 999)
    {
        IrSender.sendRaw(PowerOffrawData, 67, 38); 
        return true;
    }

    return false;

}

void onReceive(const esp_now_recv_info *info, const uint8_t *data, int len)
{
  int rcvdVal;
  memcpy(&rcvdVal, data, sizeof(rcvdVal));

  if (DEBUG)
  {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             info->src_addr[0], info->src_addr[1], info->src_addr[2],
             info->src_addr[3], info->src_addr[4], info->src_addr[5]);

    Serial.printf("(onReceive) New msg from: %s → %d\n", macStr, rcvdVal);
  }
  reponseInterpreter(rcvdVal);
}

void onSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  if (DEBUG)
  {
    Serial.print("(onsent) Msg to -> ");
    for (int i = 0; i < 6; i++)
    {
      Serial.printf("%02X", mac_addr[i]);
      if (i < 5)
        Serial.print(":");
    }
    Serial.print(" | Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sucess" : "Fail");
  }
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  IrSender.begin(transmitterPin); 

  if (DEBUG)
  {
    Serial.println("****** Welcome To Klinus ********");
    Serial.println("---- You are in Debug Mode. ----");
    Serial.println("+++ AS: HEAD FIRMWARE +++");
    Serial.print("This device MAC Addr is: ");
        Serial.println(WiFi.macAddress());
    Serial.print("** Lets begin =) **");
  }

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("CRITICAL ERROR: Start ESP32.");
    return;
  }

  esp_now_register_recv_cb(onReceive);
  esp_now_register_send_cb(onSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("CRITICAL ERROR: Add Peer.");
    return;
  }

  Serial.println("Network Ready. (Receiv and Send)");
}

void loop()
{

  if (queueValue != 0)
  {
    esp_err_t result = esp_now_send(peerAddress, (uint8_t *)&queueValue, sizeof(queueValue));

    if (result == ESP_OK)
    {
      queueValue = 0;
      if (DEBUG)
      {
        Serial.printf("New MSG Sended (loop stage) : %d\n", queueValue);
      }
    }
    else if (DEBUG)
    {
      Serial.println("CRITICAL ERROR: Send Msg to peer (loop stage)");
    }
  }
}
