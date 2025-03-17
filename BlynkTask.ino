/*--------------------------------------------------------------- Send data to blynk ---------------------------------------------------------------*/
void sendDataToBlynk() {
  Blynk.sendInternal("rtc", "sync");

  dhtx.get();
  dhtx.log();
  dhtx.calculateDataRange();

  mqx.get();
  mqx.log();
  mqx.calculateDataRange();

  // Set datastreams
  Blynk.virtualWrite(V9, dhtx.temperature);
  Blynk.virtualWrite(V10, dhtx.humidity);
  Blynk.virtualWrite(V11, map(mqx.value, 0, 4095, 0, 100));
}

/*------------------------------------------------------ Update Pin-value & Virtual-pin-value ------------------------------------------------------*/
void updatePinNVirtualPin(int pin, int pinValue, int virtualPin, int virtualPinValue) {
  digitalWrite(pin, pinValue);
  Blynk.virtualWrite(virtualPin, virtualPinValue);
}

/*-------------------------------------------- Turn on/off built-in LED when connect/disconnect to blynk --------------------------------------------*/
BLYNK_CONNECTED() {
  Blynk.sendInternal("rtc", "sync");

  digitalWrite(2, 1);
  Serial.println("--- Blynk connected ---");
}
BLYNK_DISCONNECTED() {
  digitalWrite(2, 0);
  Serial.println("--- Blynk disconnected ---");
}

BLYNK_WRITE(InternalPinRTC) {
  unsigned long blynkTime = param.asLong();
  // Serial.printf("Time: %lu\n", blynkTime);
}

/*------------------------------------------------------------ Get mode (Manual & Auto) ------------------------------------------------------------*/
BLYNK_WRITE(V0) {
  mode = param.asInt();
  Blynk.virtualWrite(V0, mode);
}

/*--------------------------------------------------------------- Get value for blynk ---------------------------------------------------------------*/
BLYNK_WRITE(V1) {
  // Lamp
  int value = param.asInt();
  blynkCheckMode(0, 1, value);
}
BLYNK_WRITE(V2) {
  // Fan
  int value = param.asInt();
  blynkCheckMode(1, 2, value);
}
//------------- Evap (Pump) is controlled by system -------------//
BLYNK_WRITE(V3) {
  // Evap
  /*
   * int value = param.asInt();
   * blynkCheckMode(2, 3, value);
  */
}
BLYNK_WRITE(V4) {
  // Clean (Chicken poop)
  int value = param.asInt();
  blynkCheckMode(3, 4, value);
}
BLYNK_WRITE(V5) {
  // Food (Chicken food)
  int value = param.asInt();
  blynkCheckMode(4, 5, value);
}

/*------------------------------------------------ Deny any manual activity when user in manual mode ------------------------------------------------*/
void denyManualMode(int virtualPin, int value) {
  Blynk.virtualWrite(virtualPin, !value);
}

/*-------------------------------------------------------- Check mode when virture pin changed --------------------------------------------------------*/
void blynkCheckMode(int relayPinIndex, int virtualPin, int value) {
  if (mode == MANUAL) {
    blynkManualMode(relayPinIndex, virtualPin, value);
  } else if (mode == AUTO) {
    denyManualMode(virtualPin, value);
  }
}

/*------------------------------------------------------------------- Manual-mode -------------------------------------------------------------------*/
void blynkManualMode(int relayPinIndex, int virtualPin, int value) {
  updatePinNVirtualPin(relay.pinList[relayPinIndex], !value, virtualPin, value);
}

/*-------------------------------------------------------------------- Auto-mode --------------------------------------------------------------------*/
void blynkIfAutoMode() {
  if (mode == AUTO) {
    //---------- Temperature ----------//
    if (dhtx.temperature >= REF_TEMP) {
      // Turn on the Fan & Evap
      updatePinNVirtualPin(RELAY_FAN, RELAY_ON, V2, 1);
      updatePinNVirtualPin(RELAY_EVAP, RELAY_ON, V3, 1);
    } else if (dhtx.temperature < REF_TEMP) {
      // Turn off the Fan & Evap
      updatePinNVirtualPin(RELAY_FAN, RELAY_OFF, V2, 0);
      updatePinNVirtualPin(RELAY_EVAP, RELAY_OFF, V3, 0);
    }

    //---------- Ammonia ----------//
    else if (mqx.value >= REF_AMMONIA) {
      // Turn on the Fan
      updatePinNVirtualPin(RELAY_FAN, RELAY_ON, V2, 1);
    } else if (mqx.value < REF_AMMONIA) {
      // Turn off the Fan
      updatePinNVirtualPin(RELAY_FAN, RELAY_ON, V2, 1);
    }

    //---------- Humidity ----------//
    if (dhtx.humidity >= REF_HUMI) {
      // Turn on the Ultrasonic atomization
    } else {
      // Turn off the Ultrasonic atomization
    }
  }
}
