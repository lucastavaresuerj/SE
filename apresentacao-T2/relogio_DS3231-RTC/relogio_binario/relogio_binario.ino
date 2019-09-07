#include <Wire.h> //include Wire.h library
#include "RTClib.h" //include Adafruit RTC library
#define pinH0 2 
#define pinH1 3 
#define pinH2 4 
#define pinH3 5 
#define pinM0 6
#define pinM1 7
#define pinM2 8
#define pinM3 9
#define pinM4 10
#define pinM5 11

RTC_DS3231 rtc; //Make a RTC DS3231 object
int i;
void displayHora(int h) {
  Serial.println(h);
  for(i=0;i<4;i++){
    Serial.println( (h & (1<<i))>0);
    digitalWrite(i+2, (h & (1<<i))>0);  
  }
}

void displayMinutos(int m){
  Serial.println(m);
  for(i=0;i<6;i++){
    Serial.println( (m & (1<<i))>0);
    digitalWrite(i+6, (m & (1<<i))>0);  
  }
}

void setup() {
  pinMode(pinH0,OUTPUT);
  pinMode(pinH1,OUTPUT);
  pinMode(pinH2,OUTPUT);
  pinMode(pinH3,OUTPUT);
  pinMode(pinM0,OUTPUT);
  pinMode(pinM1,OUTPUT);
  pinMode(pinM2,OUTPUT);
  pinMode(pinM3,OUTPUT);
  pinMode(pinM4,OUTPUT);
  pinMode(pinM5,OUTPUT);
  
  Serial.begin(9600); //Begin the Serial at 9600 Baud
  
  //Print the message if RTC is not available
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  //Setup of time if RTC lost power or time is not set
  if (rtc.lostPower()) {
    //Sets the code compilation time to RTC DS3231
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();
  displayHora(abs(now.hour()-12));
  displayMinutos(now.minute());
  delay(3000);
}
