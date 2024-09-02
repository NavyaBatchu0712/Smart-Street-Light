#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char* ssid = " ";
const char* password = " ";

WiFiClient client;

unsigned long myChannelNumber = 1213941;
const char * myWriteAPIKey = "04SHHYB2T6L2MF7I";
const char * myReadAPIKey = "XDNHQ0S8G1KKUPZZ";

int led_1;
int led_2;
int led_3;

int ir1 = D0;
int led1 = D5;

int ir2 = D1;
int led2 = D6;

int ir3 = D2;
int led3 = D7;

int ldr = A0;
int val =0;

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(ir1,INPUT);
  pinMode(led1,OUTPUT);

  pinMode(ir2,INPUT);
  pinMode(led2,OUTPUT);

  pinMode(ir3,INPUT);
  pinMode(led3,OUTPUT);

  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}

void loop() {
  int s1 = analogRead(ir1);
  int s2 = analogRead(ir2);
  int s3 = analogRead(ir3);
  int a1 = digitalRead(led1);
  int a2 = digitalRead(led2);
  int a3 = digitalRead(led3);

  val = analogRead(ldr);

  Serial.print(s1);
  Serial.print(":");
  Serial.print(s2);
  Serial.print(":");
  Serial.print(s3);
  Serial.print("  ");
  Serial.println(val);
  Serial.println(a1);
  Serial.println(a2);
  Serial.println(a3);
  if(val<800)
  {
    if(s1<300)
    {
      digitalWrite(led1,HIGH);
    }
    else
    {
      digitalWrite(led1,LOW);
    }
    if(s2<300)
    {
      digitalWrite(led2,HIGH);
    }
    else
    {
      digitalWrite(led2,LOW);
    }

    if(s3<300)
    {
      digitalWrite(led3,HIGH);
    }
    else
    {
      digitalWrite(led3,LOW);
    }
  }
  else
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
  }

  ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2,s1, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3,s2, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 4,s3, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 5,a1, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 6,a2, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 7,a3, myWriteAPIKey);

  led_1 = ThingSpeak.readIntField(myChannelNumber, 5, myReadAPIKey);
  led_2 = ThingSpeak.readIntField(myChannelNumber, 6, myReadAPIKey);
  led_3 = ThingSpeak.readIntField(myChannelNumber, 7, myReadAPIKey);

  if(led_1==1)
  {
    digitalWrite(led1,LOW);
  }
  else
  {
    digitalWrite(led1,HIGH);
  }

  if(led_2==1)
  {
    digitalWrite(led2,LOW);
  }
  else
  {
    digitalWrite(led2,HIGH);
  }

  if(led_3==1)
  {
    digitalWrite(led3,LOW);
  }
  else
  {
    digitalWrite(led3,HIGH);
  }
}
