 #include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//define pin numbers
#define IN1  4
#define IN2  0
#define IN3  14
#define IN4  12

const char *ssid     = "Dilakshi Peiris";
const char *password = "AS991226";

int ang = 0;
//for the delay
int mils = 1;
const long utcOffsetInSeconds = 19800;
const int daylightoffset = 0;
int ledpin1= D0;
int ledpin2= D8;

int buzzer = D7;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {

  pinMode(ledpin1,OUTPUT);
  pinMode(ledpin2,OUTPUT);  
  pinMode(buzzer,OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.begin(9600);

   WiFi.begin(ssid, password);
   timeClient.begin();
}


void rotate(int angle)
{
  int numberOfRounds = (int) angle * 1.42222; // angle*512/360
  for (int i = 0; i < numberOfRounds; i++) {

    //1000
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(mils);

    //1100
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(mils);

    //0100
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(mils);

    //0110
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(mils);

    //0011
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    delay(mils);

    //0010
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(mils);

    //0001
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(mils);

    //1001
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(mils);


  }
  // Switch off all phases
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


void loop() 
{
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
 
  /*Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  */

    
  

  if( (timeClient.getHours() == 13) && (timeClient.getMinutes() == 57))
  {
      
      //checks the time of the clock as 6.00 am
      if((timeClient.getSeconds() == 00 ))
      {
        Serial.println("Read " + String(365) + " degrees");
        rotate(365); 
      }
      digitalWrite(ledpin1,HIGH);
      digitalWrite(ledpin2,LOW);
      delay(100);
      digitalWrite(ledpin1,LOW);
      digitalWrite(ledpin2,HIGH);
      delay(100);
      
      tone(buzzer,2000,250);
      delay(1000);
      
  }
  else
  {
      digitalWrite(ledpin1,LOW); 
      digitalWrite(ledpin2,LOW); 
  }
    
  delay(1000);
}
