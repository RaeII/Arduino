#define pinSom 7 // porta que vai receber o som
#define pinRele1 2 //porta de saida para o rele
#define pinRele2 3 //porta de saida para o rele
#define tempoMaximoDeUmaPalma  150 //milisegundos
#define tempoMaximoEntrePalmas 500 //milisegundos

int contaPalmas = 0;
long tempoEspera = 0;
long tempoEsperaEntrePalmas = 0;

void executarAcao();

void setup() {
  pinMode(pinSom, INPUT); //entrada do som
  pinMode(pinRele1, OUTPUT); //saida rele
  pinMode(pinRele2, OUTPUT); //saida rele
}

void loop() {
  //verifica o estado do sensor de som (ele fica normalmente com a porta ligada. Quando ouver uma palma, ele desliga momentaneamente a porta)
  int sensorSom = digitalRead(pinSom);

  //se o sensor detectou palmas
  if (sensorSom == LOW) { //se tiver som a porta vai desligar

     //espera um tempo para nao detectar a mesma palma mais de uma vez 
     if (tempoEspera == 0) {
        tempoEspera = tempoEsperaEntrePalmas = millis(); 
        contaPalmas++;
     } else if ((millis() - tempoEspera) >= tempoMaximoDeUmaPalma) {
        tempoEspera = 0;
     }
  }

  //caso exceda o tempo maximo entre palmas, zera o contador de palmas
  if ( (contaPalmas != 0) && ((millis() - tempoEsperaEntrePalmas) > 500) ) {
     executarAcao();
     contaPalmas = 0;
     tempoEsperaEntrePalmas = millis();
  }
  
}


void executarAcao() 
{
  
  switch (contaPalmas) {
    case 2: 
       digitalWrite(pinRele1, !digitalRead(pinRele1));
       break;
  }
}

