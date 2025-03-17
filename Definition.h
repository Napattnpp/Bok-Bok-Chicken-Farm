/*----------------------------------------------------- DHT22 (Temperature and Humidity sensor) -----------------------------------------------------*/
#define DHT_PIN                       4
#define DHT_TYPE                      DHT22
// Refference value
#define REF_TEMP                      36
#define REF_HUMI                      40

/*------------------------------------------------------------- MQ-137 (Ammonia sensor) -------------------------------------------------------------*/
#define MQ_PIN                        35
// Equation variables
#define RL                            47.0      // The value of resitor (47k)
#define SLOPE                        -0.263     // Slope     = [log(y2) - log(y1)] / [log(x2) - log(x1)]
#define INTERCEPT                     0.42      // Intercept = log(y) - m*log(x)
#define RO                            30.0      // Resistance in fresh air  (20 to 30)
#define V                             5.0       // Supply voltage
#define MAX_ANALOG                    4095.0    // ESP32 using ADC 12bits (Maximum analog value that esp32 can read is 4095)
// Refference value
#define REF_AMMONIA                   80        // Minimum = 0, Maximum = 100

/*-------------------------------------------------------------- Relay 4 channel (x2) --------------------------------------------------------------*/
#define NUM_OF_RELAY                  5
// Relay-1
#define RELAY_LAMP                    32
#define RELAY_FAN                     33
#define RELAY_EVAP                    25
#define RELAY_CLEAN                   26        // Chicken poop
// Relay-2
#define RELAY_FOOD                    27        // Chicken food
// Relay state
#define RELAY_ON                      0
#define RELAY_OFF                     1

/*---------------------------------------------------------------------- Blynk ----------------------------------------------------------------------*/
#define BLYNK_TEMPLATE_ID             ""
#define BLYNK_TEMPLATE_NAME           ""
#define BLYNK_AUTH_TOKEN              ""
#define BLYNK_PRINT                   Serial
// WiFi
#define WIFI_SSID                     ""
#define WIFI_PASSWORD                 ""
// Mode
#define AUTO                          1
#define MANUAL                        0

/*---------------------------------------------------------------- Google Apps Script ----------------------------------------------------------------*/
#define URL                           ""
