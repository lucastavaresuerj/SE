#define pinLed 11
#define sensor 0

int val = 0;      // Initializing the variable for the voltage value

void setup() {
  Serial.begin(9600);  // Initializing the serial port at 9600 baud
}

void loop() {
  val = analogRead(sensor);  // Read the voltage
  Serial.println(val, DEC); // Print the voltage to the terminal
  if(val > 30) {
    digitalWrite(pinLed,HIGH);
  } else {
    digitalWrite(pinLed,LOW);
  }
}
