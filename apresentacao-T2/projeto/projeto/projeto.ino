#include "Ultrasonic.h"

#define pinLedPiezo 11
#define pinLedUs 10
#define pinLedVib 9
#define pinLedBtn 8

#define pinSenPiezo 0
#define pinSenUsTrg 6
#define pinSenUsEcho 7
#define pinSenVib 4
#define pinSenBtn 5

#define pinBtnONOFF 2
#define pinLedONOFF 13

int estado;
int valPiezo;
bool butONOFF;
int leds; //1,2,3,4 piezo,ultrasonico,vibracao,butao
bool sensores[4];
bool ativado[4];

int sequencia[10] = {1,3,2,4,1,3,3,2,4,2};
int nivelAtual;
int navegaSequencia;

Ultrasonic ultrasonic(pinSenUsTrg,pinSenUsEcho);
int distancia;

unsigned long int tmpNivel;
unsigned long int tmpSinaliza;
unsigned long int tmpLe;

int senPiezo;
int senUs;
bool senVib; 
bool senBtn;

int hcsr04(){/*
   digitalWrite(pinSenUsTrg, HIGH); 
   delayMicroseconds(10); 
   digitalWrite(pinSenUsTrg, LOW); */
   return (ultrasonic.Ranging(CM)); 
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pinLedPiezo,OUTPUT);
  pinMode(pinLedUs,OUTPUT);
  pinMode(pinLedVib,OUTPUT);
  pinMode(pinLedBtn,OUTPUT);
  pinMode(pinLedONOFF,OUTPUT);

  pinMode(pinSenUsTrg,INPUT);
  pinMode(pinSenUsEcho,INPUT);
  pinMode(pinSenVib,INPUT);
  pinMode(pinSenBtn,INPUT);
  pinMode(pinBtnONOFF,INPUT);

  digitalWrite(pinSenVib, HIGH);

  butONOFF = HIGH;

  Serial.begin(9600);
  
  estado = 1;
}

void testaLeds() {
  digitalWrite(pinLedPiezo,HIGH);
  digitalWrite(pinLedUs,HIGH);
  digitalWrite(pinLedVib,HIGH);
  digitalWrite(pinLedBtn,HIGH);
  digitalWrite(pinLedONOFF,HIGH);
}

void testaVib() {
  if (digitalRead (pinSenVib)) { // If a signal was noticed, the LED will be on
    digitalWrite (pinLedVib, HIGH);
  } else {
    digitalWrite (pinLedVib, LOW);
  }
}

void testaPiezo() {
  valPiezo = analogRead(pinSenPiezo);  // Read the voltage
  Serial.println(valPiezo, DEC); // Print the voltage to the terminal
  if(valPiezo > 800) {
   digitalWrite(pinLedPiezo,HIGH);
  } else {
   digitalWrite(pinLedPiezo,LOW);
  }
}

void testaUs() {
  distancia = hcsr04(); 
  if(distancia <= 10){
    digitalWrite(pinLedUs,HIGH);
  }else{
    digitalWrite(pinLedUs,LOW);
  }
}

void testaBtn() {
  if(!digitalRead(pinSenBtn)){
    digitalWrite(pinLedBtn, HIGH);
  } else {
    digitalWrite(pinLedBtn, LOW);
  }
  if(!digitalRead(pinBtnONOFF)){
    digitalWrite(pinLedONOFF, HIGH);
  } else {
    digitalWrite(pinLedONOFF, LOW);
  }
}

void desligaLeds() {
  switch (leds) { // piezo,ultrasonico,vibracao,butao
    case (1):
      digitalWrite(pinLedPiezo,LOW);
      break;
    case (2):
      digitalWrite(pinLedUs,LOW);
      break;
    case (3):
      digitalWrite (pinLedVib, LOW);
      break;
    case (4):
      digitalWrite(pinLedBtn, LOW);
      break;  
    default:
      break;  
  }
}

bool lePiezo() {
  valPiezo = analogRead(pinSenPiezo);  // Read the voltage
  //Serial.println(valPiezo, DEC); // Print the voltage to the terminal
  if(valPiezo > 800 && !sensores[0]) {
   digitalWrite(pinLedPiezo,HIGH);
   leds = 1;
   sensores[0] = true;
   return true;
  } else {
    if (valPiezo > 800) {
      ativado[0] = true;
      return false;
    } else {
      ativado[0] = false;
      return false;
    }
  }
}

bool leUs() {
  distancia = hcsr04(); 
  if(distancia <= 10 && !sensores[1]){
    digitalWrite(pinLedUs,HIGH);
    leds = 2;
    sensores[1] = true;
    return true;
  }else {
    if(distancia<=10){
      ativado[1] = true;
      return false;
    } else {
      ativado[1] = false;
      return false;
    }
  }
}

bool leVib() {
  if (digitalRead (pinSenVib) && !sensores[2]) { // If a signal was noticed, the LED will be on
    digitalWrite (pinLedVib, HIGH);
    leds = 3;
    sensores[2] = true;
    return true;
  } else {
    if (digitalRead (pinSenVib)) {
      ativado[2] = true;
      return false;
    } else {
      ativado[3] = false;
      return false;
    }
  }
}

bool leBtn() {
  if(!digitalRead(pinSenBtn) && !sensores[3]){
    digitalWrite(pinLedBtn, HIGH);
    leds = 4;
    sensores[3] = true;
    return true;
  } else {
    if (!digitalRead(pinSenBtn) ){
      ativado[3] = true;
      return false;
    } else {
      ativado[3] = false;
      return false;
    }
  }
}

bool algumSensorAtivado() {
  return (sensores[0] || sensores[1] || sensores[2] || sensores[3]);
}

void sinaliza_sensor (int s) {
  switch (s) {
    case 1: //piezo
      digitalWrite(pinLedPiezo,HIGH);
    case 2: //ultrasonico
      digitalWrite(pinLedUs,HIGH);
    case 3: //vibracao
      digitalWrite(pinLedVib,HIGH);
    case 4: //botao
      digitalWrite(pinLedBtn,HIGH);
  }
  
}

int le_sensores(int s) {
  senPiezo = lePiezo(); //1
  senUs = leUs(); //2
  senVib = leVib(); //3
  senBtn = leBtn(); //4

  switch (s){
    case 1:
      if ( senPiezo && !senUs  && !senVib && !senBtn) {
        return true;
      } else if ( senUs || senVib || senBtn) {
        return false;
      } else {
        return 2;
      } break;
    case 2:
      if ( !senPiezo && senUs && !senVib && !senBtn) {
        return true;
      } else if ( senPiezo || senVib || senBtn){
        return false;
      } else {
        return 2;
      } break;
    case 3:
      if ( !senPiezo && !senUs && senVib && !senBtn) {
        return true;
      } else if ( senPiezo || senUs || senBtn){
        return false;
      } else {
        return 2;
      } break;
    case 4:
      if ( !senPiezo && !senUs && !senVib && senBtn) {
        return true;
      } else if ( senPiezo || senUs || senVib ){
        return false;
      } else {
        return 2;
      } break;
    case 5:
      return ativado[0] || ativado[1] || ativado[2] || ativado[3];

  }
    
}

void loop() {
  // put your main code here, to run repeatedly:
  //testaLeds();
  //testaVib();
  //testaPiezo();
  //testaUs();
  //testaBtn();

  switch (estado) {
    
    case 1: //desligado
        if(!digitalRead(pinBtnONOFF) && butONOFF) {
          butONOFF = LOW;
      } else if(digitalRead(pinBtnONOFF) != butONOFF) {
          estado = 2;
          tmpNivel = millis();
          butONOFF = digitalRead(pinBtnONOFF);
          nivelAtual = 1;
          navegaSequencia = 0;
      } break;
    
    case 2: //nivel
        if( (millis() - tmpNivel)>=4000 ){
          estado = 3;
          tmpSinaliza = millis();
      } else if(!digitalRead(pinBtnONOFF) && butONOFF) {
          butONOFF = LOW;
      } else if(digitalRead(pinBtnONOFF) != butONOFF) {
          estado = 1;
          tmpNivel = millis();
          butONOFF = digitalRead(pinBtnONOFF);
      } break;
      
    case 3: //sinaliza
        if (navegaSequencia == nivelAtual) {
          estado = 4;
          navegaSequencia = 0;
      } else if (millis() - tmpSinaliza){
          sinaliza_sensor(sequencia[navegaSequencia]);
          tmpSinaliza = millis();
          navegaSequencia++;
      } else if(!digitalRead(pinBtnONOFF) && butONOFF) {
          butONOFF = LOW;
      } else if(digitalRead(pinBtnONOFF) != butONOFF) {
          estado = 1;
          tmpNivel = millis();
          butONOFF = digitalRead(pinBtnONOFF);
      } break;
    
    case 4: //analisa
        if(navegaSequencia == nivelAtual) {
          estado = 2;
          nivelAtual++;
          navegaSequencia = 0;
      } else if (algumSensorAtivado()) {
          if (!le_sensores(5)) {
            navegaSequencia++;
          }
          break;
      } else if(le_sensores(sequencia[navegaSequencia])==true) {
          navegaSequencia++;
          tmpLe = millis();
      } else if(!digitalRead(pinBtnONOFF) && butONOFF) {
          butONOFF = LOW;
      } else if(digitalRead(pinBtnONOFF) != butONOFF) {
          estado = 1;
          tmpNivel = millis();
          butONOFF = digitalRead(pinBtnONOFF);
      } break;
  }
  
}

  
