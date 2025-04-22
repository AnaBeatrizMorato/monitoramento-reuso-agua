#include <SPI.h>

// === Sensor Ultrassônico ===
const int trigPin = 9;
const int echoPin = 10;

// === Relé da bomba ===
const int relePin = 7;
const int distanciaMinima = 18;  // Distância mínima para ligar
const int distanciaMaxima = 20;  // Distância máxima para desligar

// === Sensor de Fluxo ===
const int fluxoPin = 2;
volatile int pulsos = 0;
float vazao = 0;
float litros = 0;
unsigned long ultimoTempo = 0;
const float fatorCalibracao = 7.5;  // Número de pulsos por litro (ajuste conforme seu sensor)

// === Interrupção: Contador de pulsos ===
void contadorPulsos() {
  pulsos++;  // Incrementa o contador de pulsos a cada pulso do sensor
}

void setup() {
  Serial.begin(9600);

  // Configuração do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configuração do relé
  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, LOW);  // Começa com o relé desligado

  // Configuração do sensor de fluxo
  pinMode(fluxoPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(fluxoPin), contadorPulsos, FALLING);

  Serial.println("Sistema iniciado!");
}

void loop() {
  // === Leitura do sensor ultrassônico ===
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH);
  long distancia = duracao * 0.034 / 2;

  // === Controle do relé ===
  static bool releEstado = false;  // Armazena o estado anterior do relé
  if (distancia < distanciaMinima && !releEstado) {
    digitalWrite(relePin, HIGH);  // Liga o relé se distância < 18 cm
    Serial.println("Relé LIGADO (Distância < 18cm)");
    releEstado = true;  // Atualiza o estado do relé
  } else if (distancia > distanciaMaxima && releEstado) {
    digitalWrite(relePin, LOW);   // Desliga o relé se distância > 20 cm
    Serial.println("Relé DESLIGADO (Distância > 20cm)");
    releEstado = false;  // Atualiza o estado do relé
  }

  // === Cálculo da Vazão e Volume ===
  if (millis() - ultimoTempo >= 1000) {  // Atualiza a cada 1 segundo
    noInterrupts();  // Desabilita interrupções para evitar inconsistência
    vazao = (pulsos / fatorCalibracao) * 60;  // Calcula vazão em L/min
    litros += (pulsos / fatorCalibracao);     // Acumula o volume em litros
    pulsos = 0;                               // Zera o contador de pulsos
    ultimoTempo = millis();
    interrupts();  // Reabilita interrupções

    // Exibe as informações de vazão e volume no Serial Monitor
    Serial.print("Vazão: ");
    Serial.print(vazao);
    Serial.print(" L/min | Volume total: ");
    Serial.print(litros);
    Serial.println(" L");
  }

  delay(500);  // Delay para estabilidade
}
