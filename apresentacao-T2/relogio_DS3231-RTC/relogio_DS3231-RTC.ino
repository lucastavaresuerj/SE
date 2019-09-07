include <Wire.h> //include Wire.h library
#include "RTClib.h" //include Adafruit RTC library

RTC_DS3231 rtc; //Make a RTC DS3231 object

//Set the names of days
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {  
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

void loop () {
  //Set now as RTC time
  DateTime now = rtc.now();
  
  //Print RTC time to Serial Monitor
  Serial.println(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  
  delay(3000);
}
