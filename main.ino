#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Adafruit_VL53L0X.h>
// Set these to run example. 
#define FIREBASE_HOST "locu-15eca.firebaseio.com"
//"example.firebaseio.com" 
#define FIREBASE_AUTH "dA7KUz5NkLTctyKZEtC8TFkhA2C0tI9jpYchD5Lh" 
#define WIFI_SSID "G" 
#define WIFI_PASSWORD "password" 

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() { 
 Serial.begin(9600); 
 // connect to wifi. 
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
 Serial.print("connecting"); 
 while (WiFi.status() != WL_CONNECTED) { 
   Serial.print("."); 
   delay(500); 
 } 
 Serial.println(); 
 Serial.print("connected: "); 
 Serial.println(WiFi.localIP()); 
 Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
} 
int n = 0; 
void loop() { 
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
    
  delay(2000);
//  set value 
 Firebase.setFloat("location/1/sensor1", measure.RangeMilliMeter); 
 // handle error 
 if (Firebase.failed()) { 
     Serial.print("setting /number failed:"); 
     Serial.println(Firebase.error());   
     return; 
 } 
 delay(500); 
} 
