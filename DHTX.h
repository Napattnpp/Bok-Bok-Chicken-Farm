class DHTX {
  private:
    DHT dht;
  public:
    float temperature = 0;
    float humidity = 0;

    /* Temperature-range & Humidity-range
      [0]: Max
      [1]: Min
    */
    float temperatureRange[2];
    float humidityRange[2];

    DHTX(int _dhtPin, int _dhtType) : dht(_dhtPin, _dhType) {}

    void init();
    void get();
    void log();

    void calculateDataRange();
};

void DHTX::init() {
  dht.begin();
  delay(100);

  // Set default value to temperatureRange[2] and humidityRange[2]
  get();
  temperatureRange[0] = temperature;
  temperatureRange[1] = temperature;
  humidityRange[0] = humidity;
  humidityRange[1] = humidity;
}

void DHTX::get() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}

void DHTX::log() {
  Serial.printf("\tTemperature (C)\t|\tHumidity (%%)\n");
  Serial.printf("\t%f\t|\t%f\n", temperature, humidity);
  Serial.printf("---------------------------------------------\n");
}

void DHTX::calculateDataRange() {
  // Check if current temperature more than previous max-temperature or less than previous min-temperature
  if (temperature > temperatureRange[0]) {
    temperatureRange[0] = temperature;
  } else if (temperature < temperatureRange[1]) {
    temperatureRange[1] = temperature;
  }

  // Check if current humidity more than previous max-humidity or less than previous min-humidity
  if (humidity > humidityRange[0]) {
    humidityRange[0] = humidity;
  } else if (humidity < humidityRange[1]) {
    humidityRange[1] = humidity;
  }
}
