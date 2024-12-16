class MQX {
  public:
    float value = 0.f;

    /* Value-range
      [0]: Max
      [1]: Min
    */
    float valueRange[2];

    void init();
    void get();
    void log();

    void calculateDataRange();
};

void MQX::init() {
  pinMode(MQ_PIN, INPUT);

  // Set default value to valueRange[2]
  get();
  valueRange[0] = value;
  valueRange[1] = value;

}

void MQX::get() {
  float analogValue = 0;
  float vrl = 0;

  float rs = 0;
  float ratio = 0;

  // Get the average of analog value
  for (int i = 0; i < 500; i++) {
    analogValue += analogRead(MQ_PIN);
  }
  analogValue /= 500;

  // Get the voltage drop across the sensor
  vrl = analogValue * (V/MAX_ANALOG);

  // Find ratio Rs/Ro (resistance at gas concentration / resistance in clean air)
  rs = ((5.0*RL) / vrl) - RL;
  ratio = rs/RO;

  value = pow(10, ((log10(ratio)-INTERCEPT) / SLOPE));
}

void MQX::log() {
  Serial.printf("Ammonia Concentration: %lf ppm\n", value);
  Serial.printf("---------------------------------------------\n");
}

void MQX::calculateDataRange() {
  // Check if current value more than previous max-value or less than previous min-value
  if (value > valueRange[0]) {
    valueRange[0] = value;
  } else if (value < valueRange[1]) {
    valueRange[1] = value;
  }
}
