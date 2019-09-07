#define pinLed 11 // Declaration of the LED output pin
#define pinVibra 4 //Declaration of the Sensor input pin
  
void setup ()
{
  pinMode (pinLed, OUTPUT) ; // Initialisation output pin
  pinMode (pinVibra, INPUT) ; // Initializstion sensor pin
  digitalWrite(pinVibra, HIGH); // Activating of the internal pull-up resistors
}
  
void loop ()
{
  if (digitalRead (pinVibra)) { // If a signal was noticed, the LED will be on
    digitalWrite (pinLed, HIGH);
  } else {
    digitalWrite (pinLed, LOW);
  }
}
