#include <DHT.h>

int sensorUmidadeSoloPin = A0; 
int sensorUmidadeSoloValue = 0; // Variável para armazenar a leitura do sensor
int umidadePercent = 0; // Variável para armazenar a umidade do solo em porcentagem
int ldrValue = 0; // Variável para armazenar a leitura do LDR
int luminosidadePercent = 0; // Variável para armazenar a luminosidade em porcentagem

// ENTRADAS ANALÓGICAS
#define LDR_PIN A1      // Pino onde o LDR está conectado
#define DHTPIN 2        // Pino onde o DHT11 está conectado
#define DHTTYPE DHT11   // Tipo do sensor DHT11

// ENTRADAS DIGITAIS
#define LED_UMIDADE_VERDE_PIN 3   
#define LED_UMIDADE_AMARELO_PIN 4 
#define LED_UMIDADE_VERMELHO_PIN 5 
#define LED_TEMP_VERMELHO_PIN 6  
#define LED_TEMP_AMARELO_PIN 7  
#define LED_TEMP_VERDE_PIN 8  
#define LED_LUMINOSIDADE_VERMELHO_PIN 9  
#define LED_LUMINOSIDADE_AMARELO_PIN 10 
#define LED_LUMINOSIDADE_VERDE_PIN 11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  
  dht.begin();         

  pinMode(LED_UMIDADE_VERDE_PIN, OUTPUT);   
  pinMode(LED_UMIDADE_AMARELO_PIN, OUTPUT); 
  pinMode(LED_UMIDADE_VERMELHO_PIN, OUTPUT); 
  pinMode(LED_TEMP_VERMELHO_PIN, OUTPUT);  
  pinMode(LED_TEMP_AMARELO_PIN, OUTPUT);  
  pinMode(LED_TEMP_VERDE_PIN, OUTPUT);  
  pinMode(LED_LUMINOSIDADE_VERMELHO_PIN, OUTPUT); 
  pinMode(LED_LUMINOSIDADE_AMARELO_PIN, OUTPUT); 
  pinMode(LED_LUMINOSIDADE_VERDE_PIN, OUTPUT); 
}

void loop() {
  // Leitura do sensor de umidade do solo
  sensorUmidadeSoloValue = analogRead(sensorUmidadeSoloPin);  
  umidadePercent = map(sensorUmidadeSoloValue, 1023, 0, 0, 100);

  // Leitura do LDR
  ldrValue = analogRead(LDR_PIN);
  luminosidadePercent = map(ldrValue, 800, 0, 0, 100);

  // Leitura do sensor DHT11
  float temperatura = dht.readTemperature();

  Serial.print("Oi, humano! Tudo bem com você? ");

  bool mensagemAdicional = false;
  bool condicoesFavoraveis = true;

  if (temperatura > 35) {
    Serial.print("Comigo está PÉSSIMO!!!! QUE CALOOOOOOOOOR. ");
    mensagemAdicional = true;
    condicoesFavoraveis = false;
  } 

  if (temperatura < 20) {
    Serial.print("Estou congelando! Muito frio por aqui! ");
    mensagemAdicional = true;
    condicoesFavoraveis = false;
  }

  if (umidadePercent < 30) {
    if (mensagemAdicional) {
      Serial.print("E além disso, ");
    }
    Serial.print("Eu estou com sede. ");
    mensagemAdicional = true;
    condicoesFavoraveis = false;
  }

  if (luminosidadePercent > 80) {
    if (mensagemAdicional) {
      Serial.print("Ainda por cima está muito claro, me leve para a sombra. ");
    } else {
      Serial.print("Está muito claro, me leve para a sombra. ");
    }
    mensagemAdicional = true;
    condicoesFavoraveis = false;
  } else if (luminosidadePercent < 30) {
    if (mensagemAdicional) {
      Serial.print("E além disso, está muito escuro, me leve para tomar um solzinho. ");
    } else {
      Serial.print("Está muito escuro, me leve para tomar um solzinho. ");
    }
    mensagemAdicional = true;
    condicoesFavoraveis = false;
  }

  if (condicoesFavoraveis) {
    Serial.print("Tá tudo bem comigo, nem estou com sede. ");
  }

  Serial.print("Umidade do solo: ");
  Serial.print(umidadePercent);
  Serial.print("%. ");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print("°C. ");

  Serial.print("Luminosidade: ");
  Serial.print(luminosidadePercent);
  Serial.print("%. ");
  Serial.println();

  // Controle dos LEDs baseado na luminosidade
  if (luminosidadePercent > 80 || luminosidadePercent < 30) {
    digitalWrite(LED_LUMINOSIDADE_VERMELHO_PIN, HIGH); // Acende o LED para luminosidade extrema
    digitalWrite(LED_LUMINOSIDADE_AMARELO_PIN, LOW);  // Apaga o LED para luminosidade média
    digitalWrite(LED_LUMINOSIDADE_VERDE_PIN, LOW);  // Apaga o LED para luminosidade ok
  } else if (luminosidadePercent > 70 || luminosidadePercent < 40) {
    digitalWrite(LED_LUMINOSIDADE_VERMELHO_PIN, LOW);  // Apaga o LED para luminosidade extrema
    digitalWrite(LED_LUMINOSIDADE_AMARELO_PIN, HIGH); // Acende o LED para luminosidade média
    digitalWrite(LED_LUMINOSIDADE_VERDE_PIN, LOW);  // Apaga o LED para luminosidade ok
  } else {
    digitalWrite(LED_LUMINOSIDADE_VERMELHO_PIN, LOW);  // Apaga o LED para luminosidade extrema
    digitalWrite(LED_LUMINOSIDADE_AMARELO_PIN, LOW);  // Apaga o LED para luminosidade média
    digitalWrite(LED_LUMINOSIDADE_VERDE_PIN, HIGH); // Acende o LED para luminosidade ok
  }

  // Controle dos LEDs baseado na umidade do solo
  if (umidadePercent > 60) {
    digitalWrite(LED_UMIDADE_VERDE_PIN, HIGH);  // Acende o LED umidade excelente
    digitalWrite(LED_UMIDADE_AMARELO_PIN, LOW); // Apaga o LED umidade ok
    digitalWrite(LED_UMIDADE_VERMELHO_PIN, LOW); // Apaga o LED umidade ruim
  } else if (umidadePercent > 39) {
    digitalWrite(LED_UMIDADE_VERDE_PIN, LOW);   // Apaga o LED umidade excelente
    digitalWrite(LED_UMIDADE_AMARELO_PIN, HIGH); // Acende o LED umidade ok
    digitalWrite(LED_UMIDADE_VERMELHO_PIN, LOW); // Apaga o LED umidade ruim
  } else {
    digitalWrite(LED_UMIDADE_VERDE_PIN, LOW);   // Apaga o LED umidade excelente
    digitalWrite(LED_UMIDADE_AMARELO_PIN, LOW); // Apaga o LED umidade ok
    digitalWrite(LED_UMIDADE_VERMELHO_PIN, HIGH); // Acende o LED umidade ruim
  }

  // Controle dos LEDs baseado na temperatura
  if (temperatura > 35 || temperatura < 20) {
    digitalWrite(LED_TEMP_VERMELHO_PIN, HIGH);  // Acende o LED para temperatura extrema
    digitalWrite(LED_TEMP_AMARELO_PIN, LOW);   // Apaga o LED para faixa de temperatura média
    digitalWrite(LED_TEMP_VERDE_PIN, LOW);   // Apaga o LED para faixa de temperatura normal
  } else if ((temperatura >= 32 && temperatura <= 35) || (temperatura >= 20 && temperatura <= 27)) {
    digitalWrite(LED_TEMP_VERMELHO_PIN, LOW);   // Apaga o LED para temperatura extrema
    digitalWrite(LED_TEMP_AMARELO_PIN, HIGH);  // Acende o LED para faixa de temperatura média
    digitalWrite(LED_TEMP_VERDE_PIN, LOW);   // Apaga o LED para faixa de temperatura normal
  } else if (temperatura >= 27 && temperatura <= 32) {
    digitalWrite(LED_TEMP_VERMELHO_PIN, LOW);   // Apaga o LED para temperatura extrema
    digitalWrite(LED_TEMP_AMARELO_PIN, LOW);   // Apaga o LED para faixa de temperatura média
    digitalWrite(LED_TEMP_VERDE_PIN, HIGH);  // Acende o LED para faixa de temperatura normal
  }

  delay(2000);  // Aguarda 20 segundos antes de ler novamente
}
