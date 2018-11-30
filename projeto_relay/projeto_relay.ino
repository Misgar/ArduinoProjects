#include "Ultrasonic.h"
#include <LiquidCrystal.h>

//Definição de variáveis
char leitura;
int contador = 0;
int buttonState = 0;

//Definiçao de portas
const int rele = 8;
const int btn = 9;
const int echoPin = 7;
const int trigPin = 6;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Ultrasonic ultrasonic(7,6);

void setup() {
  Serial.begin(9600);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(btn, INPUT);
  
}

void loop() {
    buttonState = digitalRead(btn);
    if (buttonState == HIGH){
      contador++;
      delay(150);
    }
    if (contador % 2 == 0){
      digitalWrite(rele, LOW);
    }
    else{
      digitalWrite(rele, HIGH);
    }
    Serial.println(contador);
 }
