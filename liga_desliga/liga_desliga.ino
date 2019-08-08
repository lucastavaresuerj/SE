#define LED_PIN_OUT 11
#define LED_PIN_IN 13 
#define BUT_PIN_ON 4
#define BUT_PIN_OFF 2

int estado = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN_OUT, OUTPUT);
  pinMode(BUT_PIN_ON, INPUT);
  pinMode(BUT_PIN_OFF, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(BUT_PIN_ON)) {
    estado = 1;
    digitalWrite(LED_PIN_OUT, estado);
    
  }
  if(!digitalRead(BUT_PIN_OFF)) {
    estado = 0;
    digitalWrite(LED_PIN_OUT, estado);
  }
  

}
