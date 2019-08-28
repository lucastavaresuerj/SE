#define PIN_LED_IN 13
#define PIN_LED_OUT 11
#define PIN_BUT_AC 2
#define PIN_BUT_DC 4
#define DELAY 100

int but_ac = HIGH;// diz o estado b1
int but_dc = HIGH;// diz o estado b2

int estado = 1;
int intervalo = 2000;
int conta500 = 0;
int contaTempo = 0;
int contaFim = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED_IN, OUTPUT);
  pinMode(PIN_LED_OUT, OUTPUT);
  pinMode(PIN_BUT_AC, INPUT);
  pinMode(PIN_BUT_DC, INPUT);
  
  digitalWrite(PIN_LED_OUT, HIGH);
  contaTempo = millis();
  //Serial.begin(9600);
}

void loop() {
  contaFim = millis();
  switch (estado) {
    case 1: //led_aceso
      //Serial.print("-- estado 1 --\n");
      if(contaFim - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, LOW);
        estado = 2;        
      } else if(!digitalRead(PIN_BUT_AC) && but_ac) { //pressiona b1        
        but_ac = LOW; //pressionado
        //Serial.print("-- pressiona b1 --\n");
        estado = 3;
      } else if(!digitalRead(PIN_BUT_DC) && but_dc) { //pressiona b2
        but_dc = LOW; //pressionado
        //Serial.print("-- pressiona b2 --\n");
        estado = 6;
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        //Serial.print("-- soltar b1 --\n");
        but_ac = HIGH;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        //Serial.print("-- soltar b2 --\n");
        but_dc = HIGH;
      } break;
      
    case 2: //led_apagado
      //Serial.print("-- estado 2 --\n");
      if(contaFim - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, HIGH);
        estado = 1;
      } else if(!digitalRead(PIN_BUT_AC) && but_ac) { //pressiona b1        
        but_ac = LOW; //pressionado
        //Serial.print("-- pressiona b1 --\n");
        estado = 4;
      } else if(!digitalRead(PIN_BUT_DC) && but_dc) { //pressiona b2
        but_dc = LOW; //pressionado
        //Serial.print("-- pressiona b2 --\n");
        estado = 7;
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        //Serial.print("-- soltar b1 --\n");
        but_ac = HIGH;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        //Serial.print("-- soltar b2 --\n");
        but_dc = HIGH;
      } break;
      
    case 3: //led_aceso
      //Serial.print("-- estado 3 --\n");
      if(contaFim - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, LOW);
        estado = 4;
      } else if(!digitalRead(PIN_BUT_DC) && but_dc) { //pressiona b2
        estado = 5;
        //Serial.print("-- pressiona b2 --\n");
        digitalWrite(PIN_LED_IN, HIGH);
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        //Serial.print("-- soltar b1 --\n");
        but_ac = HIGH;
        estado = 1;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        //Serial.print("-- soltar b2 --\n");
        but_dc = HIGH;
      } else if (millis() - conta500 > 500) { //500ms
        estado = 1;
        conta500 = millis();
        //Serial.print("-- 500ms --\n");
      } break;

    case 4: //led_apagado
      //Serial.print("-- estado 4 --\n");
      if(contaFim - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, HIGH);
        estado = 3;
      } else if(!digitalRead(PIN_BUT_DC) && but_dc) { //pressiona b2
        estado = 5;
        //Serial.print("-- pressiona b1 --\n");
        digitalWrite(PIN_LED_IN, HIGH);
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        //Serial.print("-- soltar b1 --\n");
        but_ac = HIGH;
        estado = 2;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        //Serial.print("-- soltar b2 --\n");
        but_dc = HIGH;
      } else if (millis() - conta500 > 500) { //500ms
        estado = 2;
        //Serial.print("-- 500ms --\n");
        conta500 = millis();
      } break;

    case 5: //manter_estado
      //Serial.print("-- estado 5 --\n");
      while (true) {
        //fica aqui
      } break;

    case 6: //led_aceso
      //Serial.print("-- estado 6 --\n");
      if(contaFim - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, LOW);
        estado = 7;
      } else if(!digitalRead(PIN_BUT_AC) && but_ac) { //pressiona b1
        estado = 5;
        digitalWrite(PIN_LED_IN, HIGH);
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        //Serial.print("-- soltar b1 --\n");
        but_ac = HIGH;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        //Serial.print("-- soltar b2 --\n");
        but_dc = HIGH;
        estado = 1;
      } else if (millis() - conta500 > 500) { //500ms
        estado = 1;
        //Serial.print("-- 500ms --\n");
        conta500 = millis();
      } break;

    case 7: //led_apagado
      //Serial.print("-- estado 7 --\n");
      if(contaFim - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, HIGH);
        estado = 6;
      } else if(!digitalRead(PIN_BUT_AC) && but_ac) { //pressiona b1
        estado = 5;
        //Serial.print("-- pressiona b1 --\n");
        digitalWrite(PIN_LED_IN, HIGH);
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        //Serial.print("-- soltar b1 --\n");
        but_ac = HIGH;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        //Serial.print("-- soltar b2 --\n");
        but_dc = HIGH;
        estado = 2;
      } else if (millis() - conta500 > 500) { //500ms
        estado = 2;
        //Serial.print("-- 500ms --\n");
        conta500 = millis();
      } break;
  }
}
