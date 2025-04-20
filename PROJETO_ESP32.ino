#include <DHT.h>

#define DHTPIN 17             // Pino de leitura do DHT22
#define DHTTYPE DHT22         // Tipo do sensor DHT
#define PINO_SENSOR_GAS 18    // Pino digital do sensor de gás
#define PINO_SENSOR_CHUVA 15  // Pino digital do sensor de chuva
#define TEMT6000_PIN 34       // Pino analógico do sensor de luz

const float LUX_THRESHOLD = 50.0; // Limite para considerar claro ou escuro

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(PINO_SENSOR_GAS, INPUT);
  pinMode(PINO_SENSOR_CHUVA, INPUT);
  pinMode(TEMT6000_PIN, INPUT);
  analogReadResolution(12); // ESP32 tem resolução de 0–4095
}

void loop() {
  delay(2000); // Intervalo entre medições

  // Leitura do DHT22
  float humidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (isnan(humidade) || isnan(temperatura)) {
    Serial.println("Falha na leitura do sensor DHT22!");
    return;
  }

  Serial.print("HUMIDADE: ");
  Serial.print(humidade);
  Serial.print(" %\tTEMPERATURA: ");
  Serial.print(temperatura);
  Serial.println(" ºC");

  // Leitura do sensor de gás
  bool gasDetectado = digitalRead(PINO_SENSOR_GAS) == LOW;
  Serial.print("Sensor de Gás: ");
  Serial.println(gasDetectado ? "GÁS DETECTADO" : "Sem gás detectado");

  // Leitura do sensor de luminosidade (TEMT6000)
  int analogValue = analogRead(TEMT6000_PIN);
  float voltage = analogValue * (3.3 / 4095.0);
  float lux = voltage * 200.0;

  Serial.print("Luz - ADC: ");
  Serial.print(analogValue);
  Serial.print(" | Tensão: ");
  Serial.print(voltage, 2);
  Serial.print(" V | Lux: ");
  Serial.print(lux, 1);
  Serial.print(" -> ");
  Serial.println(lux < LUX_THRESHOLD ? "Está ESCURO" : "Está CLARO");

  // Leitura do sensor de chuva
  bool estaChovendo = digitalRead(PINO_SENSOR_CHUVA) == LOW;
  Serial.print("Sensor de Chuva: ");
  Serial.println(estaChovendo ? "ESTÁ CHOVENDO" : "SEM CHUVA");
  
  Serial.println("\n------------------------------\n");
}
