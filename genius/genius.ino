//Notas
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

//Portas
int sequencia[32] = {};
int leds[4] = { 8, 9, 10, 11 };
int botoes[4] = { 2, 3, 4, 5 };
int portaLDR = A0;

//Variáveis
int tons[4] = {262, 294, 330, 349};
int rodada = 0;
int passo = 0;
int botao_pressionado = 0;
bool game_over = false;
int sensorValue = 0;
bool playMarch = true;
int ldr;
int ativarMarcha;
bool ledBlink = true;

void setup() {
  //leds
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  //buzeer
  pinMode(6, OUTPUT);
  //botões
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  Serial.begin(9600);
}

void loop() {
  verificarLDR();
  if(ldr == 0  || sensorValue >= 1) {//O sensorValue comea como zero, mas se o LDR receber valor zero, ele somará mais um no sensorValeu, para iniciar o game
    beginBlink();
    ledBlink = false;
    sensorValue++;
    proximaRodada();
    reproduzirSequencia();
    aguardarJogador();
    if (game_over == true) {
      sequencia[32] = {};
      rodada = 0;
      passo = 0;
      game_over = false;
    }
    delay(1000);
  }
}

//Faz o sorteio de um led(entre 4), a posição da sequência vai receber o valor e passar uma rodada quando for concluído
void proximaRodada() {
  int sorteio = random(4);
  sequencia[rodada] = sorteio;
  rodada = rodada + 1;
  ativarMarcha = 0;
}

//Mostra o led e o tom da rodada atual, até o fim do loop
void reproduzirSequencia() {
  for (int i = 0; i < rodada; i++) {
    tone(6, tons[sequencia[i]]);
    digitalWrite(leds[sequencia[i]], HIGH);
    delay(500);
    noTone(6);
    digitalWrite(leds[sequencia[i]], LOW);
    delay(100);
  }
}

void aguardarJogador() {
  for (int i = 0; i < rodada; i++) {//Durante a rodada, executará tudo abaixo
    bool jogada_efetuada = false;
    while (!jogada_efetuada) { //Enquanto a jogada efetuada for false, ele permanecerá rodando o código dentro desse loop
      for (int i = 0; i <= 3; i++ ) { // Se mantém verificando os botões
        if (digitalRead(botoes[i]) == HIGH) { //Se um botão for pressionado, executará o código abaixo
          botao_pressionado = i;
          tone(6, tons[i]);
          digitalWrite(leds[i], HIGH);
          delay(300);
          digitalWrite(leds[i], LOW);
          noTone(6);
          jogada_efetuada = true;// Para sair do loop
        }
      }
    }
    if (sequencia[passo] != botao_pressionado) { //Se a luz correspondente da sequência for diferente do botão que foi pressionado
      if(ativarMarcha == 0) {
        marcha();
        ledBlink = true;    
        }
      for (int i = 0; i <= 3; i++) {
        tone(6, 70);
        digitalWrite(leds[i], HIGH);
        delay(100);
        digitalWrite(leds[i], LOW);
        noTone(6);
        sensorValue = 0;
      }
      game_over = true;
      
      break;
      
    }
    passo = passo + 1;
    
  }
  passo = 0;
}


void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)
{ 
    int x;   
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)   
    {    
        digitalWrite(6,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(6,LOW);
        delayMicroseconds(delayAmount);
    }    
    delay(20);
}

void marcha()
{   ativarMarcha++;
    verificarLDR();
    beep(6, a, 500);
    verificarLDR(); 
    beep(6, a, 500);  
    verificarLDR();
    beep(6, a, 500);
    verificarLDR(); 
    beep(6, f, 350);
    verificarLDR(); 
    beep(6, cH, 150);
    verificarLDR();
    
    beep(6, a, 500);
    verificarLDR();
    beep(6, f, 350);
    verificarLDR();
    beep(6, cH, 150);
    verificarLDR();
    beep(6, a, 1000);
    verificarLDR();
}
void verificarLDR(){ //Adicionar valor de leitura digital na variável
  ldr = digitalRead(portaLDR);
  //Serial.println(ldr);
}

void beginBlink(){ // As piscadas antes do game começar
  if(ledBlink)
  for(int i =0; i < 3; i++){
   digitalWrite(8, HIGH);
   digitalWrite(9, HIGH);
   digitalWrite(10, HIGH);
   digitalWrite(11, HIGH);
   delay(300);
    digitalWrite(8, LOW);
   digitalWrite(9, LOW);
   digitalWrite(10, LOW);
   digitalWrite(11, LOW);
   delay(300);
  }
  
}





