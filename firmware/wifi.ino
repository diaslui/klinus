

bool connectToWifi(char *ssid, char *password){

  WiFi.begin(ssid, password);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 3000) {
      delay(100);
  }
  return WiFi.status() == WL_CONNECTED;

};
