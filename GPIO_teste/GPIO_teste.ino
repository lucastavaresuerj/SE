int estado;
unsigned int tempo;

void setup() {
  DDRB |= 1 << 3; //pin 11 output LED
  DDRD &= ~(1 << 2);  //pin 2 input BTN
  estado = 1;
  tempo = millis();
}

void loop() {
  switch (estado){
    case 1:
      if (millis()-tempo>1000) { //intervalo
        estado = 2;
        PORTB &= ~(1 << 3); //led low
        tempo = millis();
      } else if( !(PIND & (1 << 2)) ) { // BTN precionado
        estado = 3;
      } break;
     
    case 2:
      if (millis()-tempo>1000) { //intervalo
        estado = 1;
        PORTB |= 1 << 3; //led high
        tempo = millis();
      } else if( !(PIND & (1 << 2)) ) { // BTN precionado
        estado = 3;
      } break;
      
    case 3:
      while (true) {
        //fica aqui
      }
  }
  
}
