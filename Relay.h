class Relay {
  public:
    int pinList[NUM_OF_RELAY];

    // Set constructor
    Relay() {
      pinList[0] = RELAY_LAMP;
      pinList[1] = RELAY_FAN;
      pinList[2] = RELAY_EVAP;
      pinList[3] = RELAY_CLEAN;
      pinList[4] = RELAY_FOOD;
    }

    void init();
    void test();
};

void Relay::init() {
  // Set pin mode
  for (int i = 0; i < NUM_OF_RELAY; i++) {
    pinMode(pinList[i], OUTPUT);
  }

  // Set default state (1 == turn off)
  for (int i = 0; i < NUM_OF_RELAY; i++) {
    digitalWrite(pinList[i], RELAY_OFF);
  }
}

void Relay::test() {
  for (int i = 0; i < NUM_OF_RELAY; i++) {
    digitalWrite(pinList[i], RELAY_ON);
    delay(2000);
    digitalWrite(pinList[i], RELAY_OFF);
    delay(2000);
  }
}
