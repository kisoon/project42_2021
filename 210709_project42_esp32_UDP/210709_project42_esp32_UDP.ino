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

//////////////////////////////////////
//자신이 연결한 센서 주석 해제 (// 주석 표시)석
//#define MOVE1
//#define MOVE2
//#define SOUND
//#define LIGHT
//#define TOUCH
//#define LED
//////////////////////////////////////

//////////////////////////////////////
//-------Wifi환경 설정하기---------
//자신의 WIFI 환경으로 수정해야 함
//공유기에 따라 게이트웨이, 아이피 주소를 변경해야함.
const char* ssid = "kit-bakery Lab";
const char* password = "sewoon203";
//
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


//actor1(현주쌤)  60, 9000 --> Acc,  Touch(4번 장면)    / Touch만 프로그램 재 업로드
//actor2(수연쌤)  61, 9100 --> Touch        
//actor3(문선쌤)  62, 9200 --> Acc1, Touch(4번 장면)    /arm
//actor3(문선쌤)  63, 9300 --> Acc2/leg
//actor4(난희쌤)  64, 9400 --> Light, Touch(4번 장면)   / White
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


void setup() {

  Wire.begin(23, 22);
  // put your setup code here, to run once:
  Serial.begin(115200);
  initWiFi();


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

  //test LED
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
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

    lastTime = millis();
  }
  
  if((millis() - touchLastTime) > touchTimerDelay){
    
    #ifdef TOUCH
    getTouching();
    dataBuffer[8] = touchValue1;
    dataBuffer[9] = touchValue2;
    if(touchValue1 || touchValue2) digitalWrite(13, HIGH); else digitalWrite(13, LOW);
    
    #else
    dataBuffer[8] = 0;
    dataBuffer[9] = 0;
    #endif

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
  delay(15);
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
