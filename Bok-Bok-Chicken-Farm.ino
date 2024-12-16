#include "SystemFile.h"

DHTX dhtx;
MQX mqx;
Relay relay;
BlynkTimer timer;

int mode = MANUAL;

unsigned long currentTime = 0;
unsigned long previousTime = 0;

void setup() {
  // Initialize Serial monitor
  Serial.begin(115200);

  pinMode(2, OUTPUT);

  dhtx.init();
  mqx.init();
  relay.init();

  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
  // // Send data to Blynk every 3000 ms
  timer.setInterval(3000L, sendDataToBlynk);
}

void loop() {
  currentTime = millis();

  Blynk.run();
  timer.run();

  // Send data to Google Sheet ever 3,600,000 ms (1 hour) (m * s * ms)
  if ((currentTime - previousTime) >= (60*60*1000)) {
    sendDataToGoogleSheets();
  }
}
