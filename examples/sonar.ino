/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 More info at: http://goo.gl/kJ8Gl
 */

#define trigPin 12
#define echoPin 13

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
  }
  delay(10);
}
