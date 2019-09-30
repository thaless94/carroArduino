#define receptorUC 11
#define pinoTrigger 12
#define pinoEcho 13

#include <HCSR04.h>
#include <IRremote.h>
#include <SoftwareSerial.h>

int pino1 = 7;
int pino2 = 6;
int pino3 = 5;
int pino4 = 4;
int potencia1 = 9;
int potencia2 = 10;

char comando;
float dist_cm;

UltraSonicDistanceSensor distanceSensor(pinoTrigger, pinoEcho);
SoftwareSerial bluetooth(2, 3);
IRrecv recIR(receptorUC);
decode_results resultado;

void setup() {
  Serial.begin(9600);
  pinMode(pino1, OUTPUT);
  pinMode(pino2, OUTPUT);
  pinMode(pino3, OUTPUT);
  pinMode(pino4, OUTPUT);
  pinMode(potencia1, OUTPUT);
  pinMode(potencia2, OUTPUT);
  recIR.enableIRIn();
}

void loop() {
  dist_cm = distanceSensor.measureDistanceCm();

  while (Serial.available()) {
    comando = Serial.read();

    if (comando == 'F' && dist_cm > 20) {
      frente();
    }
    else if (comando == 'B') {
      tras();
    }
    else if (comando == 'L' ) {
      esquerda();
    }
    else if (comando == 'R' ) {
      direita();
    }
    else {
      parado();
    }
  }

  if (recIR.decode(&resultado))  {
    if (dist_cm > 20 && resultado.value == 0x1FE50AF)  {
      frente();
    } else {
      parado();
      recIR.resume();
    }
    if (resultado.value == 0x1FED02F)  {
      tras();
    } else if (resultado.value == 0x1FEB04F) {
      esquerda();
    } else if (resultado.value == 0x1FE30CF) {
      direita();
    } else if (resultado.value == 0x1FE708F) {
      parado();
    }
  }
}


void tras() {
  analogWrite(potencia1, 150);
  analogWrite(potencia2, 150);
  digitalWrite(pino1, HIGH);
  digitalWrite(pino2, LOW);
  digitalWrite(pino3, HIGH);
  digitalWrite(pino4, LOW);
}
void frente() {
  analogWrite(potencia1, 150);
  analogWrite(potencia2, 150);
  digitalWrite(pino1, LOW);
  digitalWrite(pino2, HIGH);
  digitalWrite(pino3, LOW);
  digitalWrite(pino4, HIGH);
}

void esquerda() {
  analogWrite(potencia1, 150);
  analogWrite(potencia2, 150);
  digitalWrite(pino1, LOW);
  digitalWrite(pino2, HIGH);
  digitalWrite(pino3, HIGH);
  digitalWrite(pino4, LOW);
}
void direita() {
  analogWrite(potencia1, 150);
  analogWrite(potencia2, 150);
  digitalWrite(pino1, HIGH);
  digitalWrite(pino2, LOW);
  digitalWrite(pino3, LOW);
  digitalWrite(pino4, HIGH);
}
void parado() {
  digitalWrite(pino1, LOW);
  digitalWrite(pino2, LOW);
  digitalWrite(pino3, LOW);
  digitalWrite(pino4, LOW);
}
