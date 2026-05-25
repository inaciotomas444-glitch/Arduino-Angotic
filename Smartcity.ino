// Projeto: Smartcity / Cidade Digital - ANGOTIC 2026
// Placa: Arduino Uno + Sensores + ESP32 via Serial
// Autor: Angola Makers

#include <SoftwareSerial.h>
SoftwareSerial espSerial(2, 3); // RX, TX para ESP32

const int LDR_PIN = A0;
const int LED_RUA = 13;
const int TRIG_PIN = 8;
const int ECHO_PIN = 9;

long duracao;
int distancia;
int luminosidade;

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(LED_RUA, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("Smartcity Arduino iniciado");
}

void loop() {
  // 1. Lê luminosidade para iluminação inteligente
  luminosidade = analogRead(LDR_PIN);
  if (luminosidade < 400) {
    digitalWrite(LED_RUA, HIGH); // Liga poste à noite
  } else {
    digitalWrite(LED_RUA, LOW);  // Desliga de dia
  }

  // 2. Lê sensor ultrassônico para lixeira inteligente
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duracao = pulseIn(ECHO_PIN, HIGH);
  distancia = duracao * 0.034 / 2;

  // 3. Envia dados para ESP32 via Serial
  espSerial.print("LUM:");
  espSerial.print(luminosidade);
  espSerial.print(",DIST:");
  espSerial.println(distancia);

  // Debug no monitor serial
  Serial.print("Luz: ");
  Serial.print(luminosidade);
  Serial.print(" | Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  delay(2000); // Envia a cada 2 segundos
}
