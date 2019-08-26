#define PIN_LED_IN 13
#define PIN_LED_OUT 11
#define PIN_BUT_AC 2
#define PIN_BUT_DC 4

int but_ac = HIGH;// diz o estado b1
int but_dc = HIGH;// diz o estado b2

int estado = 1;
int intervalo = 1000;
int conta500 = 0;
int contaTempo = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED_IN, OUTPUT);
  pinMode(PIN_LED_OUT, OUTPUT);
  pinMode(PIN_BUT_AC, INPUT);
  pinMode(PIN_BUT_DC, INPUT);
  
  digitalWrite(PIN_LED_OUT, HIGH);
  contaTempo = millis();
}

void loop() {
  switch (estado) {
    case 1: //led_aceso
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, LOW);
        estado = 2;
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - 250;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + 250;
      } else if(!digitalRead(PIN_BUT_AC)) { //pressiona b1        
        but_ac = LOW; //pressionado
        estado = 3;
      } else if(!digitalRead(PIN_BUT_DC)) { //pressiona b2
        but_dc = LOW; //pressionado
        estado = 6;
      }  break;
      
    case 2: //led_apagado
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, HIGH);
        estado = 1;
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - 250;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + 250;
      } else if(!digitalRead(PIN_BUT_AC)) { //pressiona b1        
        but_ac = LOW; //pressionado
        estado = 4;
      } else if(!digitalRead(PIN_BUT_DC)) { //pressiona b2
        but_dc = LOW; //pressionado
        estado = 7;
      }  break;
      
    case 3: //led_aceso
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, LOW);
        estado = 4;
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - 250;
        but_ac = HIGH;
        estado = 1;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + 250;
        but_dc = HIGH;
      } else if(!digitalRead(PIN_BUT_DC)) { //pressiona b2
        estado = 5;
      } else if (millis() - conta500 > 500) { //500ms
        estado = 1;
      } break;

    case 4: //led_apagado
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, HIGH);
        estado = 3;
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - 250;
        but_ac = HIGH;
        estado = 2;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + 250;
        but_dc = HIGH;
      } else if(!digitalRead(PIN_BUT_DC)) { //pressiona b2
        estado = 5;
      } else if (millis() - conta500 > 500) { //500ms
        estado = 2;
      } break;

    case 5: //manter_estado
      while (true) {
        //fica aqui
      } break;

    case 6: //led_aceso
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, LOW);
        estado = 7;
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - 250;
        but_ac = HIGH;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + 250;
        but_dc = HIGH;
        estado = 1;
      } else if(!digitalRead(PIN_BUT_AC)) { //pressiona b1
        estado = 5;
      } else if (millis() - conta500 > 500) { //500ms
        estado = 1;
      } break;

    case 7: //led_apagado
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        digitalWrite(PIN_LED_OUT, HIGH);
        estado = 6;
      } else if(digitalRead(PIN_BUT_AC) != but_ac) { //soltar b1
        intervalo = intervalo - 250;
        but_ac = HIGH;
      } else if(digitalRead(PIN_BUT_DC) != but_dc) { //soltar b2
        intervalo = intervalo + 250;
        but_dc = HIGH;
        estado = 2;
      } else if(!digitalRead(PIN_BUT_AC)) { //pressiona b1
        estado = 5;
      } else if (millis() - conta500 > 500) { //500ms
        estado = 2;
      } break;
  }
}
