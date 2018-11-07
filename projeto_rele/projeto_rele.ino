#include "Ultrasonic.h"
//Definição de variáveis
char leitura;

//Definiçao de portas
const int rele =8;
const int echoPin = 13;
const int trigPin = 12;
const int btn = 1;
Ultrasonic ultrasonic(12,13);

void setup() {
  Serial.begin(9600);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  while (Serial.available() > 0){
    leitura = Serial.read();
    if (leitura == 'd' || leitura == 'D'){
      digitalWrite(rele, LOW);
    }
    else if(leitura == 'l' || leitura == 'L'){
      digitalWrite(rele, HIGH);
    }
    Serial.println(leitura);
  }

}
