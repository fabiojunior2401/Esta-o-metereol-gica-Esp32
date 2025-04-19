#include <DHT.h>

#define DHTPIN 17     // Define o pino de leitura conectado
#define DHTTYPE DHT22 // DHT 22 (AM2302) - define o sensor via biblioteca
#define pinosensorgas 18
#define pinosensorchuva 15


const int TEMT6000_PIN = 34;  // Use um pino ADC1 do ESP32

// Limite para definir se está claro ou escuro
const float LUX_THRESHOLD = 50.0;  // Ajuste conforme o ambiente

bool sensorgas;

DHT dht(DHTPIN, DHTTYPE);
//Função para mostrar os parâmetros no terminal/serial
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(pinosensorgas, INPUT);
  pinMode(TEMT6000_PIN, INPUT);
  analogReadResolution(12); // ESP32 usa 12 bits (0-4095)
  pinMode(pinosensorchuva, INPUT);
}

void loop() {
  delay(2000); // tempo entre as medições - tempo de atualização

  float humidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
// Verifica se foi possível fazer a leitura
  if (isnan(humidade) || isnan(temperatura)) {
    Serial.println("Falha na leitura do sensor DHT22!");
    return;
  }
//Exibe as medidas realizadas
  Serial.print("HUMIDADE: ");
  Serial.print(humidade);
  Serial.print(" %	");
  Serial.print("TEMPERATURA: ");
  Serial.print(temperatura);
  Serial.println(" ºC");


//inicio sensor de gás
  //faz a leitura do pino digital selecionado para o sensor
  sensorgas = digitalRead(pinosensorgas);
  //condições que verificam o estado booleano da variável
  if(sensorgas == 0){
    Serial.print("Gás detectado");
  }
  else if(sensorgas == 1){
    Serial.print("Gás não detectado");
  }
  //chama a variavel para exibição em serial
  Serial.println(sensorgas);


  int analogValue = analogRead(TEMT6000_PIN);
  float voltage = analogValue * (3.3 / 4095.0);
  float lux = voltage * 200.0;

  Serial.print("ADC: ");
  Serial.print(analogValue);
  Serial.print(" | Tensão: ");
  Serial.print(voltage, 2);
  Serial.print(" V | Lux: ");
  Serial.print(lux, 1);
  Serial.print(" -> ");

  if (lux < LUX_THRESHOLD) {
    Serial.println("Está ESCURO");
  } else {
    Serial.println("Está CLARO");
  }


Serial.print("Digital:");
  
  if (digitalRead(pinosensorchuva)) {
     Serial.print("SEM CHUVA ");
     Serial.println("\n");
  } else {
     Serial.print("ESTA CHUVENDO ");
     Serial.println("\n");
  }



}