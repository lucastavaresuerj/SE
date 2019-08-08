#define LED_PIN_OUT 11
#define LED_PIN_IN 13 
#define BUT_PIN_BREAK 4
#define BUT_PIN_CLICK 2

int est_led_out = 0;
int est_led_in = 0;
int est_but_break = 0;
int cont = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN_OUT, OUTPUT);
  pinMode(LED_PIN_IN, OUTPUT);
  pinMode(BUT_PIN_BREAK, INPUT);
  pinMode(BUT_PIN_CLICK, INPUT);

}

void pisca(int q) {
  if(q>0) {
    digitalWrite(LED_PIN_OUT, HIGH);
    delay(500);
    digitalWrite(LED_PIN_OUT, LOW);
    delay(500);
    pisca(q-1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(BUT_PIN_BREAK)) {
    digitalWrite(LED_PIN_IN, HIGH);
    est_but_break = 1;
    while(est_but_break) {
      delay(100);
      if(!digitalRead(BUT_PIN_CLICK)) {
        cont++;
      }
      else if(!digitalRead(BUT_PIN_BREAK)) {
        digitalWrite(LED_PIN_IN, LOW);
        est_but_break = 0;
      }
    }
  }
  pisca(cont);
  cont = 0;
  
}
