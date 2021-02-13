/* 8266 wifi client basic 8266WiFiBME280
 *  This has deep sleep, this reports to the web server with query parms
 *  This is Version 1.0
 *  
 *  The BME280 I2C is built on this code
    This sketch sends a string to a web server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
	
	HTTPlib development
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Wire.h>
#include <SparkFunBME280.h>
#include "HTTPlib.h"
#ifndef STASSID
#define STASSID "cirrus"
#define STAPSK  "7138982048"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

//const char* host = "40n.us";
const char* host = "10.0.0.151";
const uint16_t port = 80;

ESP8266WiFiMulti WiFiMulti;
 BME280 mySensor;

 /////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  
    Serial.begin(115200);
  delay(5000);
  Serial.println("\r\n");
  for (uint16_t i=0;i<10;i++)
  {Serial.print("Start ----> ESP8266 WiFi client plus BME280 sensor --> ");
  Serial.println(String(i));}
  // We start by connecting to a WiFi network
  Serial.println(" We start by connecting to a WiFi network");
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // initialize I2C 

 
  int sda = 5;
  int scl = 4;
  Wire.begin(sda, scl);

   while (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    delay (2000);
   // Serial.println("jump to elfin");
   // goto elfin2;
  }
  elfin2:
  Serial.println("Sensor responded");
  delay(500);
}
 void js(WiFiClient &x){}
//////  LOOP starts here ////////////////////////////////////////////////////////////

void loop() {
  Serial.println("Start of main loop");
  delay(300);
  // 
  String humidity, baro, alt, temp, device;
  // device is just a string, Version is added for me to keep track of it
  device="0001-V1.0";
  // Since we just reset due to sleeping, sample the BME280 multiple times
  // before sending to the web server
Serial.println(" test \" quote");
for (uint16_t i=0;i<25;i++){
  // get readings

  Serial.print("Humidity: ");
  humidity = mySensor.readFloatHumidity();
  Serial.print(mySensor.readFloatHumidity(), 0);
  baro = mySensor.readFloatPressure();
  Serial.print(" Pressure: ");
  Serial.print(mySensor.readFloatPressure(), 0);
  alt = mySensor.readFloatAltitudeMeters();
  Serial.print(" Alt: ");
  //Serial.print(mySensor.readFloatAltitudeMeters(), 1);
  Serial.print(mySensor.readFloatAltitudeFeet(), 1);
  temp = mySensor.readTempF();
  Serial.print(" Temp: ");
  //Serial.print(mySensor.readTempC(), 2);
  Serial.print(mySensor.readTempF(), 2);
  Serial.println();
}
  //delay(50);
  ////////
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }
  HTTPhelper http(client);
  // This will send the request to the server
  //client.println("hello from ESP8266");
  // Send initial http request 
  http.kvstart();
  http.kvparm("humidity",humidity,1);
  http.kvparm("alt",alt,1);
  http.kvparm("baro", baro, 1);
  http.kvparm("temp", temp, 1);
  http.kvparm("device", device, 0);
  http.kvend();
  //read back one line from server
  Serial.println("receiving from remote server");
  String line = client.readStringUntil('\r');
  Serial.println(line);

  Serial.println("closing connection");
  client.stop();
  goto normal;
  elfin: 
  Serial.println("Sensor did not respond");
  normal: Serial.println("wait 5 sec...");
  // delay(5000);
  Serial.println("Going into deep sleep for 50");
  ESP.deepSleep(50e6);
  // There ain't no coming back from the deep sleep....
  // We just start over again!!!!!!
 
}
