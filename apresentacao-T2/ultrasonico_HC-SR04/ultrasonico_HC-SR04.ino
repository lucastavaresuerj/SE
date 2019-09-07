#include "Ultrasonic.h" //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
#define echoPin 4 //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
#define trigPin 2 //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
#define ledPin 11 //PINO DA LED

Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS

int distancia; 

void setup(){
  Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS
  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAÍDA (ENVIA)
  pinMode(ledPin, OUTPUT); //DECLARA O PINO COMO SENDO SAÍDA
}

void loop(){
  hcsr04(); // FAZ A CHAMADA DO MÉTODO "hcsr04()"
  if(distancia <= 30){// SE A DISTÂNCIA ENTRE O OBJETO E O SENSOR ULTRASONICO FOR MENOR QUE 30CM, FAZ
    digitalWrite(ledPin,HIGH);//ACENDE A LED
  }else{//SENÃO, FAZ
    digitalWrite(ledPin,LOW);//DESLIGA A LED
  }
}
//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04(){
  digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
  delayMicroseconds(2); // DELAY DE 2 MICROSSEGUNDOS
  digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
  delayMicroseconds(10); // DELAY DE 10 MICROSSEGUNDOS
  digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
  // FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
  //RESPOSTA DO ECHO EM CENTÍMETROS E ARMAZENA
  //NA VARIÁVEL "distancia"
  distancia = (ultrasonic.Ranging(CM)); // VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
}
