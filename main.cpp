#define BLYNK_PRINT Serial
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiManager.h>
#include <Servo.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org");  


char auth[] = "gX3lvqNaZyNMsMwCmPWyz4f8fDowDB1R"; 
char ssid[] = "Uilatech2";   
char pass[] = "J*7Uilatech*777";  

#define echoPin D0 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin D1//attach pin D3 Arduino to pin Trig of HC-SR04

Servo servo_1; 

int servo_PIN = D3;
int i,j,h,m,s,n;

long duration;
int distanceCm;
int depth=20; 
int Availability;
int rohan;

int tm_hour;
int tm_min;
int tm_sec; 
struct tm *getFormattedTime();

void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  servo_1.attach(0);

  WiFi.begin(ssid,pass);                       //connection status wifi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("OK!");
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed

  timeClient.begin();
  timeClient.setTimeOffset(19820);
}


void loop()
{ 
   Blynk.run();
   
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

        duration = pulseIn(echoPin, HIGH);
        distanceCm= duration*0.034/2;
        rohan=depth*0.034 / 2;
        Availability=distanceCm-rohan;

    if (Availability != 0)
    {
      Blynk.virtualWrite(V5, Availability,"ava");
    }
     
    else{
      Blynk.virtualWrite(V5,Availability,"plz refill"); 
      
      delay(10);
    }   
   
    timeClient.update();                         //time interval
    Serial.println(timeClient.getFormattedTime());
    delay(1000);
    if (tm_hour==9)
    {
      servo_1.write (60); // Servo will move to 45 degree angle.
      delay (500);
      servo_1.write (0);  // servo will move to 90 degree angle.
      delay (1000);
      Blynk.virtualWrite(V6,"Done feeding");
    } 
  
    if (tm_hour==14)
    {
     servo_1.write (60); // Servo will move to 45 degree angle.
      delay (500);
      servo_1.write (0);  // servo will move to 90 degree angle.
      delay (1000);
      Blynk.virtualWrite(V6,"Done feeding");
    } 

    if (tm_hour==20)
    {
     servo_1.write (60); // Servo will move to 45 degree angle.
      delay (500);
      servo_1.write (0);  // servo will move to 90 degree angle.
      delay (1000);
      Blynk.virtualWrite(V6,"Done feeding");
    }  
}
