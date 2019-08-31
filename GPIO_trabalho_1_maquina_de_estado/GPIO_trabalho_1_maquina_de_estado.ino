#define DELAY 100

int btn_ac = HIGH;// diz o estado b1
int btn_dc = HIGH;// diz o estado b2

int estado = 1;
int intervalo = 2000;
unsigned int conta500 = 0;
unsigned int contaTempo = 0;

void setup() {
  DDRB |= 1 << 5; //pin_led_in input
  DDRB |= 1 << 3; //pin_led_out input
  DDRD &= ~(1 << 2); //pin_btn_ac output
  DDRD &= ~(1 << 4); //pin_btn_dc output

  PORTB |= 1 << 3; //pin_led_out high
  contaTempo = millis();
  Serial.begin(9600);
}

void loop() {
  switch (estado) {
    case 1: //led_aceso
      Serial.print("-- estado 1 --\n");
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        PORTB &= ~(1 << 3); //pin_led_out low
        estado = 2;        
      } else if(!(PIND & (1 << 2)) && btn_ac) { //pressiona b1 
        btn_ac = LOW; //pressionado
        Serial.print("-- pressiona b1 --\n");
        conta500 = millis();
        estado = 3;
      } else if(!(PIND & (1 << 4)) && btn_dc) { //pressiona b2 
        btn_dc = LOW; //pressionado
        Serial.print("-- pressiona b2 --\n");
        conta500 = millis();
        estado = 6;
      } else if( (PIND & (1 << 2))>0 != btn_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        Serial.print("-- soltar b1 --\n");
        btn_ac = HIGH;
      } else if( (PIND & (1 << 4))>0 != btn_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        Serial.print("-- soltar b2 --\n");
        btn_dc = HIGH;
      } break;
      
    case 2: //led_apagado
      Serial.print("-- estado 2 --\n");
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        PORTB |= 1 << 3; //pin_led_out high
        estado = 1;
      } else if(!(PIND & (1 << 2)) && btn_ac) { //pressiona b1        
        btn_ac = LOW; //pressionado
        Serial.print("-- pressiona b1 --\n");
        conta500 = millis();
        estado = 4;
      } else if(!(PIND & (1 << 4)) && btn_dc) { //pressiona b2
        btn_dc = LOW; //pressionado
        Serial.print("-- pressiona b2 --\n");
        conta500 = millis();
        estado = 7;
      } else if( (PIND & (1 << 2))>0 != btn_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        Serial.print("-- soltar b1 --\n");
        btn_ac = HIGH;
      } else if( (PIND & (1 << 4))>0 != btn_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        Serial.print("-- soltar b2 --\n");
        btn_dc = HIGH;
      } break;
      
    case 3: //led_aceso
      Serial.print("-- estado 3 --\n");
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        PORTB &= ~(1 << 3); //pin_led_out low
        estado = 4;
      } else if(!(PIND & (1 << 4)) && btn_dc) { //pressiona b2
        estado = 5;
        PORTB |= 1 << 5; //pin_led_in high
        Serial.print("-- pressiona b2 --\n");
      } else if( (PIND & (1 << 2))>0 != btn_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        Serial.print("-- soltar b1 --\n");
        btn_ac = HIGH;
        estado = 1;
      } else if( (PIND & (1 << 4))>0 != btn_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        Serial.print("-- soltar b2 --\n");
        btn_dc = HIGH;
      } else if (millis() - conta500 > 500) { //500ms
        estado = 1;
        conta500 = millis();
        Serial.print("-- 500ms --\n");
      } break;

    case 4: //led_apagado
      Serial.print("-- estado 4 --\n");
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        PORTB |= 1 << 3; //pin_led_out high
        estado = 3;
      } else if(!(PIND & (1 << 4)) && btn_dc) { //pressiona b2
        estado = 5;
        PORTB |= 1 << 5; //pin_led_in high
        Serial.print("-- pressiona b1 --\n");
      } else if( (PIND & (1 << 2))>0 != btn_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        Serial.print("-- soltar b1 --\n");
        btn_ac = HIGH;
        estado = 2;
      } else if( (PIND & (1 << 4))>0 != btn_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        Serial.print("-- soltar b2 --\n");
        btn_dc = HIGH;
      } else if (millis() - conta500 > 500) { //500ms
        estado = 2;
        Serial.print("-- 500ms --\n");
        conta500 = millis();
      } break;

    case 5: //manter_estado
      Serial.print("-- estado 5 --\n");
      while (true) {
        //fica aqui
      } break;

    case 6: //led_aceso
      Serial.print("-- estado 6 --\n");
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        PORTB &= ~(1 << 3); //pin_led_out low
        estado = 7;
      } else if(!(PIND & (1 << 2)) && btn_ac) { //pressiona b1
        estado = 5;
        PORTB |= 1 << 5; //pin_led_in high
        Serial.print("-- pressiona b1 --\n");
      } else if( (PIND & (1 << 2))>0 != btn_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        Serial.print("-- soltar b1 --\n");
        btn_ac = HIGH;
      } else if( (PIND & (1 << 4))>0 != btn_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        Serial.print("-- soltar b2 --\n");
        btn_dc = HIGH;
        estado = 1;
      } else if ((millis() - conta500) > 500) { //500ms
        estado = 1;
        Serial.print("-- 500ms --\n");
        conta500 = millis();
      } break;

    case 7: //led_apagado
      Serial.print("-- estado 7 --\n");
      if(millis() - contaTempo > intervalo) { //intervalo
        contaTempo = millis();
        PORTB |= 1 << 3; //pin_led_out high
        estado = 6;
      } else if(!(PIND & (1 << 2)) && btn_ac) { //pressiona b1
        estado = 5;
        PORTB |= 1 << 5; //pin_led_in high
        Serial.print("-- pressiona b1 --\n");
      } else if( (PIND & (1 << 2))>0 != btn_ac) { //soltar b1
        intervalo = intervalo - DELAY;
        Serial.print("-- soltar b1 --\n");
        btn_ac = HIGH;
      } else if( (PIND & (1 << 4))>0 != btn_dc) { //soltar b2
        intervalo = intervalo + DELAY;
        Serial.print("-- soltar b2 --\n");
        btn_dc = HIGH;
        estado = 2;
      } else if ((millis() - conta500) > 500) { //500ms
        estado = 2;
        Serial.print("-- 500ms --\n");
        conta500 = millis();
      } break;
  }
}
