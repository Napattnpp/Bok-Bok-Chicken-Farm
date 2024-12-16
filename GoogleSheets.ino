String httpFormat(float arrayTemperature[], float arrayHumidity[], float arrayAmmonia[], int egg) {
  String temperatureParameter = "?maxTemp=" + String(arrayTemperature[0]) + "&minTemp=" + String(arrayTemperature[1]);
  String humidityParameter = "&maxHumidity=" + String(arrayHumidity[0]) + "&minHumidity=" + String(arrayHumidity[1]);
  String ammoniaParameter = "&maxAmmonia=" + String(arrayAmmonia[0]) + "&minAmmonia=" + String(arrayAmmonia[1]);
  String eggParameter = "&egg=" + String(egg);

  return temperatureParameter + humidityParameter + ammoniaParameter + eggParameter;
}

void sendDataToGoogleSheets() {
  HTTPClient httpClient;
  String url = URL + httpFormat(dhtx.temperatureRange, dhtx.humidityRange, mqx.valueRange, 0);

  httpClient.begin(url.c_str());
  httpClient.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  httpClient.GET();

  httpClient.end();
  previousTime = currentTime;

  Serial.printf("Send data to Google Sheet successfully\n");
  Serial.printf("---------------------------------------------\n");
}