#include "Definition.h"

// Temperature and Humidity (DHT22 module)
// Use DHT sensor library by Adafruit
#include <DHT.h>
#include "DHTX.h"

// Ammonia sensor (MQ-137 module)
#include "MQX.h"

// Relay
#include "Relay.h"

// Blynk and WiFi
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <BlynkSimpleEsp32.h>
