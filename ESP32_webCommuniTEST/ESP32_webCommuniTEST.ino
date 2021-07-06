#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

#include "html.h"
#include "mpu.h"

#include "mpr121.h"

// Replace with your network credentials (STATION)
const char* ssid = "kit-bakery Lab";
const char* password = "sewoon203";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Create an Event Source on /events
AsyncEventSource events("/events");

// Timer variables
unsigned long lastTime = 0;
unsigned long gyroDelay = 30;

unsigned long lastTimeLight = 0;
unsigned long lightDelay = 30;

unsigned long lastTimeTouch = 0;
unsigned long touchDelay = 30;


const int lightPin = 39;
const int soundPin = 34;
int lightSensorValue = 0;        // value read from the pot
int soundSensorValue = 0;        // value read from the pot


void initWiFi() {
  WiFi.mode(WIFI_STA);

  IPAddress local_IP(192, 168, 1, 183);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

  Serial.println(WiFi.localIP());  
}

void getReadings(){
  mpu1.dmpGetQuaternion(&mpuVal1.q, mpuVal1.fifoBuffer);
  mpu1.dmpGetAccel(&mpuVal1.aa, mpuVal1.fifoBuffer);
  mpu1.dmpGetGravity(&mpuVal1.gravity, &mpuVal1.q);
  mpu1.dmpGetYawPitchRoll(mpuVal1.ypr, &mpuVal1.q, &mpuVal1.gravity);
  mpu1.dmpGetLinearAccel(&mpuVal1.aaReal, &mpuVal1.aa, &mpuVal1.gravity);

  mpu2.dmpGetQuaternion(&mpuVal2.q, mpuVal2.fifoBuffer);
  mpu2.dmpGetGravity(&mpuVal2.gravity, &mpuVal2.q);
  mpu2.dmpGetGravity(&mpuVal2.gravity, &mpuVal2.q);
  mpu2.dmpGetYawPitchRoll(mpuVal2.ypr, &mpuVal2.q, &mpuVal2.gravity);
  mpu2.dmpGetLinearAccel(&mpuVal2.aaReal, &mpuVal2.aa, &mpuVal2.gravity);
}

String processor(const String& var){
  getReadings();
  //Serial.println(var);
  if(var == "GZ1"){
    return String(mpuVal1.ypr[0]);
  }
  else if(var == "GX1"){
    return String(mpuVal1.ypr[1]);
  }
  else if(var == "GY1"){
    return String(mpuVal1.ypr[2]);
  }

  if(var == "GZ2"){
    return String(mpuVal2.ypr[0]);
  }
  else if(var == "GX2"){
    return String(mpuVal2.ypr[1]);
  }
  else if(var == "GY2"){
    return String(mpuVal2.ypr[2]);
  }
  
  return String();
}

void initWebSocket(){
  // Handle Web Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //Send large webpage from PROGMEM containing templates
    request->send_P(200, "text/html", index_html, processor);
  });

  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);

  // Start server
  server.begin();
}

void setup() {
  Serial.begin(115200);
  mpuInit();
  initWiFi();
  Serial.print("RRSI: "); Serial.println(WiFi.RSSI());

  initWebSocket();
  initTouch();
}

void loop() {
  if ((millis() - lastTime) > gyroDelay) {
//    
    
    if (mpu1.dmpGetCurrentFIFOPacket(mpuVal1.fifoBuffer) ) {
      getReadings();
      
      // Send Events to the Web Server with the Sensor Readings
      events.send(String(mpuVal1.ypr[0]* 180/M_PI).c_str(), "GZ1", millis());
      events.send(String(mpuVal1.ypr[1]* 180/M_PI).c_str(), "GX1", millis());
      events.send(String(mpuVal1.ypr[2]* 180/M_PI).c_str(), "GY1", millis());

      events.send(String(mpuVal1.aaReal.x).c_str(), "AZ1", millis());
      events.send(String(mpuVal1.aaReal.y).c_str(), "AX1", millis());
      events.send(String(mpuVal1.aaReal.z).c_str(), "AY1", millis());
      
      lastTime = millis();
      #ifdef DEBUG
      Serial.print("move1\t");
      Serial.print("ypr\t");
      Serial.print(mpuVal1.ypr[0] * 180/M_PI);
      Serial.print("\t");
      Serial.print(mpuVal1.ypr[1] * 180/M_PI);
      Serial.print("\t");
      Serial.println(mpuVal1.ypr[2] * 180/M_PI);
      #endif
      
    }
//    if (mpu2.dmpGetCurrentFIFOPacket(mpuVal2.fifoBuffer)) {
//      getReadings();
//      
//      // Send Events to the Web Server with the Sensor Readings
//      events.send(String(mpuVal2.ypr[0]* 180/M_PI).c_str(), "GZ2", millis());
//      events.send(String(mpuVal2.ypr[1]* 180/M_PI).c_str(), "GX2", millis());
//      events.send(String(mpuVal2.ypr[2]* 180/M_PI).c_str(), "GY2", millis());
//
//      events.send(String(mpuVal2.aaReal.x).c_str(), "AZ2", millis());
//      events.send(String(mpuVal2.aaReal.y).c_str(), "AX2", millis());
//      events.send(String(mpuVal2.aaReal.z).c_str(), "AY2", millis());
//      lastTime = millis();
//    #ifdef DEBUG
//      Serial.print("move2\t");
//      Serial.print("ypr\t");
//      Serial.print(mpuVal2.ypr[0] * 180/M_PI);
//      Serial.print("\t");
//      Serial.print(mpuVal2.ypr[1] * 180/M_PI);
//      Serial.print("\t");
//      Serial.println(mpuVal2.ypr[2] * 180/M_PI);
//      #endif
//    }
    
  }
  
    if((millis() - lastTimeLight) > lightDelay){
      lightSensorValue = analogRead(lightPin);        // value read from the pot
      soundSensorValue = analogRead(soundPin);
      events.send(String(lightSensorValue).c_str(), "light", millis());
      events.send(String(soundSensorValue).c_str(), "sound", millis());
      #ifdef DEBUG
      Serial.print("light\t");
      Serial.print(lightSensorValue);
      Serial.print("\t");
      Serial.print("sound\t");
      Serial.println(soundSensorValue);
      #endif
      lastTimeLight = millis();
    }

    if((millis() - lastTimeTouch) > touchDelay){
      touching();
      events.send(String(touchValue1).c_str(), "touch1", millis());
      events.send(String(touchValue2).c_str(), "touch2", millis());
      #ifdef DEBUG

      #endif
      lastTimeTouch = millis();
    }
    

//  if ((millis() - lastTimeAcc) > accelerometerDelay) {
//    // Send Events to the Web Server with the Sensor Readings
//    events.send(getAccReadings().c_str(), "accelerometer_readings", millis());
//    lastTimeAcc = millis();
//  }
//
//  if ((millis() - lastTimeTemperature) > temperatureDelay) {
//    // Send Events to the Web Server with the Sensor Readings
//    events.send(getTemperature().c_str(), "temperature_reading", millis());
//    lastTimeTemperature = millis();
//  }
}
