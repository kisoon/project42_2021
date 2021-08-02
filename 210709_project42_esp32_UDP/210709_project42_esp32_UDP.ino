#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <AsyncUDP.h>
#include <ESPAsyncWebServer.h>

#include "IndexHTML.h"
#include "MPR121.h"
#include "NeoPixelLED.h"
#include "MPU6050.h"

#include "SPIFFS.h"

#define DEBUG
//#define SPIFFSS
//#define WEB_SERVER
//////////////////////////////////////
//자신이 연결한 센서 주석 해제 주석은(// 표시)
//#define MOVE1
//#define MOVE2
#define SOUND
//#define LIGHT
//#define TOUCH
//#define LED
//////////////////////////////////////


//////////////////////////////////////
//자신의 WIFI 환경으로 수정해야 함
//공유기에 따라 게이트웨이, 아이피 주소를 변경해야함.
const char* ssid = "kit-bakery Lab";
const char* password = "sewoon203";

IPAddress local_IP(192, 168, 1, 61);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

//const char* ssid = "project42";
//const char* password = "";
//
//IPAddress local_IP(192, 168, 0, 62);
//IPAddress gateway(192, 168, 0, 1);
//IPAddress subnet(255, 255, 255, 0);
//
AsyncUDP Udp;
const unsigned int udpPort = 9200; //9000~9999
//actor1  60, 9000 --> Light, Touch  / White
//actor2  61, 9100 --> Touch,        /
//actor3  62, 9200 --> Acc, Touch    /
//actor4  63, 9300 --> Acc1, Touch   /
//actor4  64, 9400 --> Acc2
//////////////////////////////////////



// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// Create an Event Source on /events
AsyncEventSource events("/events");

// Timer variables
unsigned long mpuLastTime = 0;  
unsigned long mpuTimerDelay = 20;

unsigned long lastTime = 0;  
unsigned long timerDelay = 50;

unsigned long touchLastTime = 0;  
unsigned long touchTimerDelay = 20;

const int soundSampleTime = 50;
int micOut;

int lightSensorPin = 39; //39
int soundSensorPin = 34; //34

int lightSensorVal = 0;
int soundSensorVal = 0;
int dataBuffer[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void initSPIFFS() {
  if (!SPIFFS.begin()) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

void initWiFi() {
  WiFi.mode(WIFI_STA);

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
  
  if(Udp.connect(WiFi.localIP(), udpPort)) {
        Serial.println("UDP connected");
        Udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());
        });
        //Send unicast
        Udp.print("Hello Server!");
    }
}

void getSensorReadings(){
  lightSensorVal = analogRead(lightSensorPin);
  soundSensorVal = analogReadMIC(soundSensorPin);
}

String processor(const String &var){
  getSensorReadings();
  getTouching();
//  Serial.println(var);
  if(var == "SOUND"){
    return String(soundSensorVal);
  }
  else if(var == "LIGHT"){
    return String(lightSensorVal);
  }
  else if(var == "TOUCH1"){
    return String(touchValue1);
  }
   else if(var == "TOUCH2"){
    return String(touchValue2);
  }
}

void handleWebServer(){
  // Handle Web Server
 

#ifdef SPIFFSS
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(SPIFFS, "/index.html", "text/html");
  });

  server.serveStatic("/", SPIFFS, "/");
#else
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //Send large webpage from PROGMEM containing templates
    request->send_P(200, "text/html", index_html, processor);
  });
#endif

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

  Wire.begin(23, 22);
  // put your setup code here, to run once:
  Serial.begin(115200);
  initWiFi();
//  #ifdef SPIFFS
//    initSPIFFS();
//  #endif

  #ifdef TOUCH
  initTouch();
  #endif
  
  #ifdef MOVE1
  initMPU();
  #endif

  #ifdef MOVE2
  initMPU1();
  #endif
  
  initLED();

  #ifdef WEB_SERVER
  handleWebServer();
  #endif

  delay(1000);
}

void loop() {
#ifdef LED
  ledShow();
#endif

  // put your main code here, to run repeatedly:
    if ((millis() - mpuLastTime) > mpuTimerDelay) {
    
    // Send Events to the Web Server with the Sensor Readings
    #ifdef MOVE1
    mpuLoop();
    dataBuffer[0] = ypr[2] * 180/M_PI;
    dataBuffer[1] = ypr[1] * 180/M_PI;
    dataBuffer[2] = ypr[0] * 180/M_PI;
    #else
    dataBuffer[0] = 0;
    dataBuffer[1] = 0;
    dataBuffer[2] = 0;
    #endif

    #ifdef MOVE2
    mpuLoop1();
    dataBuffer[3] = ypr1[2] * 180/M_PI;
    dataBuffer[4] = ypr1[1] * 180/M_PI;
    dataBuffer[5] = ypr1[0] * 180/M_PI;
    #else
    dataBuffer[3] = 0;
    dataBuffer[4] = 0;
    dataBuffer[5] = 0;
    #endif
    
//    events.send(String(ypr[2] * 180/M_PI).c_str(),"GX1",millis());
//    events.send(String(ypr[1] * 180/M_PI).c_str(),"GY1",millis());
//    events.send(String(ypr[0] * 180/M_PI).c_str(),"GZ1",millis());
//    
//    events.send(String(ypr[5] * 180/M_PI).c_str(),"GX2",millis());
//    events.send(String(ypr[4] * 180/M_PI).c_str(),"GY2",millis());
//    events.send(String(ypr[3] * 180/M_PI).c_str(),"GZ2",millis());
    
    mpuLastTime = millis();
  }
  
  if ((millis() - lastTime) > timerDelay) {
    getSensorReadings();
    // Send Events to the Web Server with the Sensor Readings
    #ifdef LIGHT
    dataBuffer[6] = lightSensorVal*0.1;
    #else
    dataBuffer[6] = 0;
    #endif

    #ifdef SOUND
    dataBuffer[7] = soundSensorVal*0.1;
    #else
    dataBuffer[7] = 0;
    #endif
//
//    events.send(String(soundSensorVal).c_str(),"sound",millis());
//    events.send(String(lightSensorVal).c_str(),"light",millis());
    lastTime = millis();
  }
  
  if((millis() - touchLastTime) > touchTimerDelay){
    
    #ifdef TOUCH
    getTouching();
    dataBuffer[8] = touchValue1;
    dataBuffer[9] = touchValue2;
    #else
    dataBuffer[8] = 0;
    dataBuffer[9] = 0;
    #endif
//    events.send(String(touchValue1).c_str(),"touch1",millis());
//    events.send(String(touchValue2).c_str(),"touch2",millis());
    touchLastTime = millis();
  }

  char udpBuffer[60];

  String udpString = String(String(dataBuffer[0]) + "," + String(dataBuffer[1]) + "," + String(dataBuffer[2]) + "," +
                            String(dataBuffer[3])+","+String(dataBuffer[4])+","+String(dataBuffer[5])+","+
                            String(dataBuffer[6])+","+String(dataBuffer[7])+","+String(dataBuffer[8])+","+String(dataBuffer[9]));
  udpString.toCharArray(udpBuffer, 60);

  Udp.broadcastTo(udpBuffer, udpPort);

#ifdef DEBUG
  Serial.println(udpString);
#endif
  delay(20);
//  ledShow();
}

int analogReadMIC(int analogPin){
// Time variables to find the peak-to-peak amplitude
   unsigned long startTime= millis();  // Start of sample window
   unsigned int PTPAmp = 0; 

// Signal variables to find the peak-to-peak amplitude
   unsigned int maxAmp = 0;
   unsigned int minAmp = 1023;

// Find the max and min of the mic output within the 50 ms timeframe
   while(millis() - startTime < soundSampleTime) 
   {
      micOut = analogRead(analogPin);
      if( micOut < 1023) //prevent erroneous readings
      {
        if (micOut > maxAmp)
        {
          maxAmp = micOut; //save only the max reading
        }
        else if (micOut < minAmp)
        {
          minAmp = micOut; //save only the min reading
        }
      }
   }

  PTPAmp = maxAmp - minAmp; // (max amp) - (min amp) = peak-to-peak amplitude

  if(PTPAmp >  1023) return 0;
  else  return PTPAmp;  
}