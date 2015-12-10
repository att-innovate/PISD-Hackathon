/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 More info at: http://goo.gl/kJ8Gl
 */

#include <aJSON.h>
#include "SPI.h"
#include "WiFi.h"

#include "M2XStreamClient.h"

#define trigPin 12
#define echoPin 13



char ssid[] = "HackAThon"; //  your network SSID (name)
char pass[] = "F0undry!";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

char deviceId[] = "<M2X device id>"; // Device you want to push to
char streamName[] = "distance"; // Stream you want to push to
char m2xKey[] = "<M2X API key>"; // Your M2X access key


const int temperaturePin = A0;

WiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);

void setup() {
  Serial.begin (9600);
   pinMode(RED_LED, OUTPUT); 
  pinMode(GREEN_LED, OUTPUT); 
  pinMode(BLUE_LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(RED_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("On");
  delay(1000);               // wait for a second
  digitalWrite(RED_LED, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("Off sonar");
  delay(1000);   
  // attempt to connect to Wifi network:
    Serial.print("Attempting to connect to Network named: ");
    // print the network name (SSID);
    Serial.println(ssid); 
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    WiFi.begin(ssid, pass);
    while ( WiFi.status() != WL_CONNECTED) {
      // print dots while we wait to connect
      Serial.print(".");
      delay(300);
    }
  
    Serial.println("\nYou're connected to the network");
    Serial.println("Waiting for an ip address");
  
    while (WiFi.localIP() == INADDR_NONE) {
      // print dots while we wait for an ip addresss
      Serial.print(".");
      delay(300);
    }

    Serial.println("\nIP Address obtained");
  
    // you're connected now, so print out the status  
    printWifiStatus();
    
}

void loop() {
  int duration;
  // int freq;
  float distance;
  int conversion;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 74.07;
  if (distance >= 10 || distance <= 1){
     Serial.println("Out of range");
     digitalWrite(GREEN_LED, HIGH);
     digitalWrite(RED_LED, LOW);
     digitalWrite(BLUE_LED, LOW);
    noTone(10);
  }
  else {
    // freq = map(conversion,2,12,500,1200);
    tone(10,distance*40);
     Serial.print(distance);
     Serial.println(" in");
     if (distance < 10 && distance >= 5){
         digitalWrite(GREEN_LED, HIGH);
     digitalWrite(RED_LED, HIGH);
     digitalWrite(BLUE_LED, LOW);
     } else if (distance < 5 && distance > 1){
         digitalWrite(GREEN_LED, LOW);
     digitalWrite(RED_LED, HIGH);
     digitalWrite(BLUE_LED, LOW);
     }
      int response = m2xClient.updateStreamValue(deviceId, streamName, distance);
    Serial.print("M2x client response code: ");
    Serial.println(response);

    // Flash red LED if post is successful
    if (response == 202) {
      digitalWrite(RED_LED, HIGH);   // Turn the LED on (HIGH is the voltage level)
      delay(500);                // wait for a half second
      digitalWrite(RED_LED, LOW);
    }
  }
  delay(10);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
