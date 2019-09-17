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
int leSensores;
bool isAtivo;

int sequencia[10] = {3,2,1,4,1,3,3,2,4,2};
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

  //piezo 0
  ADMUX  |= (1 << REFS0);       // usa Vcc como referencia
  ADCSRA |= (1 << ADEN);        // habilita o ADC


  butONOFF = HIGH;
  Serial.begin(9600);
  
  estado = 1;
}

void pisca(int l) {
  if (l>0){
    digitalWrite(pinLedONOFF,HIGH);
    delay(100);
    digitalWrite(pinLedONOFF,LOW);
    delay(100);
    pisca(l-1);
  } else {
    digitalWrite(pinLedONOFF,HIGH);
  }
}

void desligaLeds() {
  digitalWrite(pinLedPiezo,LOW);
  digitalWrite(pinLedUs,LOW);
  digitalWrite (pinLedVib, LOW);
  digitalWrite(pinLedBtn, LOW);
}

bool lePiezo() {
  /* RETIRAR LEITURA PELO ANALOGREAD
  valPiezo = analogRead(pinSenPiezo);  // Read the voltage*/
  //Serial.println(valPiezo, DEC); // Print the voltage to the terminal
  
  ADMUX   &= ~(1<<pinSenPiezo);
  ADCSRA |= (1 << ADSC);        // inicia a conversao
  while(ADCSRA & (1 << ADSC));  // espera a conversao

  int valPiezo = ADCL;                 // tem que ser lido antes do ADCH
  valPiezo = (ADCH << 8) + valPiezo;
  if(valPiezo > 800 ) {
   digitalWrite(pinLedPiezo,HIGH);
   //leds = 1;
   return true;
  } else {
      return false;
  }
}

bool leUs() {
  distancia = hcsr04(); 
  if(distancia <= 10 ){
    digitalWrite(pinLedUs,HIGH);
    //leds = 2;
    return true;
  }else {
    return false;
  }
}

bool leVib() {
  if (digitalRead (pinSenVib) ) { // If a signal was noticed, the LED will be on
    digitalWrite (pinLedVib, HIGH);
    //leds = 3;
    return true;
  } else { 
     return false;
  }
}

bool leBtn() {
  if(!digitalRead(pinSenBtn) ){
    digitalWrite(pinLedBtn, HIGH);
    //leds = 4;
    return true;
  } else {
     return false;
  }
}


void sinaliza_sensor (int s) {
    digitalWrite(pinLedPiezo,s==1);
    digitalWrite(pinLedUs,s==2);
    digitalWrite(pinLedVib,s==3);
    digitalWrite(pinLedBtn,s==4);
}

int le_sensores(int s) {
  //A ORDEM DOS SENSORES IMPORTA POR CAUSA DA INTERACAO ENTE BOTAO E VIBRACAO
  
  senBtn = leBtn(); //4
  senPiezo = lePiezo(); //1
  senUs = leUs(); //2
  senVib = leVib(); //3

  switch (s){
    case 1:
      if ( senPiezo ) {
        return true;
      } else if ( senUs || senVib || senBtn) {
        return false;
      } else {
        return 2;
      } break;
    case 2:
      if (  senUs ) {
        return true;
      } else if ( senPiezo || senVib || senBtn){
        return false;
      } else {
        return 2;
      } break;
    case 3:
      if ( senVib ) {
        return true;
      } else if ( senPiezo || senUs || senBtn){
        return false;
      } else {
        return 2;
      } break;
    case 4:
      if ( senBtn) {
        return true;
      } else if ( senPiezo || senUs || senVib ){
        return false;
      } else {
        return 2;
      } break;
    case 5:
      return senPiezo || senUs || senVib || senBtn;

  }
    
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (estado) {
    
    case 1: //desligado 
      Serial.println("-- estado 1 --");
      Serial.print(nivelAtual);Serial.print(" | ");Serial.print(navegaSequencia);Serial.print(" | ");Serial.println(sequencia[navegaSequencia]);
        if(!digitalRead(pinBtnONOFF) && butONOFF) {
          butONOFF = LOW;
          digitalWrite(pinLedONOFF,HIGH);
      } else if(digitalRead(pinBtnONOFF) != butONOFF) {
          estado = 2;
          tmpNivel = millis();
          butONOFF = HIGH;   
          nivelAtual = 1; //mudar para 1
          navegaSequencia = 0;
      } break;
    
    case 2: //nivel
      Serial.println("-- estado 2 --");
      Serial.print(nivelAtual);Serial.print(" | ");Serial.print(navegaSequencia);Serial.print(" | ");Serial.println(sequencia[navegaSequencia]);
        if( (millis() - tmpNivel)>=4000 ){
          estado = 3;
          tmpSinaliza = millis();
      } else if(!digitalRead(pinBtnONOFF) && butONOFF) {
          butONOFF = LOW;
      } else if(digitalRead(pinBtnONOFF) != butONOFF) {
          estado = 1;
          tmpNivel = millis();
          butONOFF = HIGH;
          digitalWrite(pinLedONOFF,LOW);
          desligaLeds();
      } break;
      
    case 3: //sinaliza
      Serial.println("-- estado 3 --");
      Serial.print(nivelAtual);Serial.print(" | ");Serial.print(navegaSequencia);Serial.print(" | ");Serial.println(sequencia[navegaSequencia]);
        if(!digitalRead(pinBtnONOFF) && butONOFF) {
          butONOFF = LOW;
      } else if(digitalRead(pinBtnONOFF) != butONOFF) {
          estado = 1;
          tmpNivel = millis();
          butONOFF = HIGH;
          digitalWrite(pinLedONOFF,LOW);
          desligaLeds();
      } else if ( (navegaSequencia == nivelAtual) && (millis() - tmpSinaliza > 500) ){
          estado = 4;
          navegaSequencia = 0;
          sinaliza_sensor(0);
      } else if (millis() - tmpSinaliza > 500){ 
          sinaliza_sensor(sequencia[navegaSequencia]);
          tmpSinaliza = millis();
          navegaSequencia++;
      } else if(!digitalRead(pinBtnONOFF) && butONOFF) {
          butONOFF = LOW;
      } else if(digitalRead(pinBtnONOFF) != butONOFF) {
          estado = 1;
          tmpNivel = millis();
          butONOFF = HIGH;
          desligaLeds();
          digitalWrite(pinLedONOFF,LOW);
      } break;
    
    case 4: //analisa
      Serial.println("-- estado 4 --");
      Serial.print(nivelAtual);Serial.print(" | ");Serial.print(navegaSequencia);Serial.print(" | ");Serial.println(sequencia[navegaSequencia]);
      leSensores = le_sensores(sequencia[navegaSequencia]);
      //Serial.print("le sensores: ");Serial.println(leSensores);
      
        if(!digitalRead(pinBtnONOFF) && butONOFF) {
          butONOFF = LOW;
      } else if(digitalRead(pinBtnONOFF) != butONOFF) {
          estado = 1;
          tmpNivel = millis();
          butONOFF = HIGH;
          digitalWrite(pinLedONOFF,LOW);
          desligaLeds();
      } else if(navegaSequencia == nivelAtual) {//acertou tudo
          navegaSequencia = 0;
          estado = 2;
          desligaLeds();
          tmpNivel = millis();
          nivelAtual++;
          pisca(5);
      } else if (leSensores==2) { //2 significa ninguem ativado
          desligaLeds();
          isAtivo = false;
          break;
      }  else if (isAtivo) { //alguem ativado?
          break;
      } else if(leSensores==true) { //pode ser false, true ou 2
          navegaSequencia++;
          isAtivo = true;
      } else if(leSensores==false) { // erouuu //pode ser false true ou 2
          estado = 2;
          nivelAtual = 1;
          pisca(2);
          navegaSequencia = 0;
          isAtivo = false;
      } else if(leSensores==2) {
          break;
      } break;
  }
  
}

  
