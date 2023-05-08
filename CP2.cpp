#include <LiquidCrystal.h>
#include "dht.h" //INCLUSÃO DE BIBLIOTECA

// Definição das constantes
const int LDR_PIN = A0;
const int TMP_PIN = A1;
const int LED_VERDE = 9;
const int LED_AMARELO = 8;
const int LED_VERMELHO = 7;
const float MAX_LUMINOSIDADE = 100.0;
//const long periodo = 5000;
const float pinoDHT11 = A1; 
//PINO ANALÓGICO UTILIZADO PELO DHT11
dht DHT; //VARIÁVEL DO TIPO DHT

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Declaração das variáveis
float sensorValue = 0.0;
float sensorLido = 0.0;
float luminosidade = 0.0;

// Declaração das variáveis de temperatura
float sensor = 0;
float celsius = 0;
float voltage = 0;

// Declaração das médias das variáveis
float mediaLuz = 0;
float mediaTemp = 0;
float mediaUmid = 0;

// Declaração da variável de saída do sensor de umidade
int humiditysensorOutput = 0;

void setup() {
  Serial.begin(9600);

  // Configuração dos pinos de saída dos LEDs
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  // Configuração do display LCD
  lcd.begin(16, 2);

  // Inicialização do sistema
  lcd.print("Inicializando...");

  // Aguarda 5 segundos para leitura da luminosidade
  delay(5000);
  
   Serial.begin(9600); //INICIALIZA A SERIAL
  delay(2000); //INTERVALO DE 2 SEGUNDO ANTES DE INICIAR
}
{
  Serial.begin(9600); //INICIALIZA A SERIAL
  delay(2000); //INTERVALO DE 2 SEGUNDO ANTES DE INICIAR
}


void loop() {

  // Leitura da luminosidade
  mediaLuz = 0;
  for (int i = 0; i < 5; i++) {
    sensorValue = analogRead(LDR_PIN);
    sensorLido = (sensorValue / 1023.0) * MAX_LUMINOSIDADE;
    mediaLuz += sensorLido;
    delay(500);
  }
  mediaLuz /= 5.0;
  
  // Exibe média de luminosidade por 5 segundos
  lcd.clear();
  Serial.println(mediaLuz);
  if (mediaLuz < 30) {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    lcd.print("Ambiente escuro"); 
    noTone(10); }
  else if (mediaLuz >= 30 && mediaLuz <= 60) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    lcd.print("Ambiente a meia");
    lcd.setCursor(0, 1);
    lcd.print("luz"); 
    noTone(10); }
  else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    lcd.print("Ambiente muito");
    lcd.setCursor(0, 1);
    lcd.print("claro");
    tone(10,800); } //Toca o buzzer
  delay(5000);

  // Leitura da temperatura
  mediaTemp = 0;
  for (int i = 0; i < 5; i++) {
    sensor = analogRead(TMP_PIN);
    voltage = (sensor / 1023.0) * 5.0;
    celsius = (voltage - 0.5) * 100.0;
    mediaTemp += celsius;
    delay(500);
  }
  mediaTemp /= 5.0;

  // Exibe média de temperatura por 5 segundos
  lcd.clear();
  Serial.println(mediaTemp);
  if (mediaTemp < 10) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    lcd.print("Temp. Baixa");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = ");  
    lcd.print(round(mediaTemp));
    lcd.print("C");
    tone(10,800); }
  else if (mediaTemp >= 10 && mediaTemp <= 15) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    lcd.print("Temperatura OK");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = "); 
    lcd.print(round(mediaTemp));
    lcd.print("C");
    noTone(10); }
  else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    lcd.print("Temp. Alta");
    lcd.setCursor(0, 1);
    lcd.print("Temp. = ");
    lcd.print(round(mediaTemp));
    lcd.print("C");
    tone(10,800); } //Toca o buzzer
  delay(5000);

  // Leitura da umidade
  mediaUmid = 0;
  for (int i = 0; i < 5; i++) {
    humiditysensorOutput = analogRead(A2);
    mediaUmid += map(humiditysensorOutput, 0, 1023, 0, 100);
    delay(500);
  }
  mediaUmid /= 5.0;

  // Exibe umidade atual e reinicia o loop
  lcd.clear();
  Serial.println(mediaUmid);
  if (mediaUmid < 50) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    lcd.print("Umid. Baixa");
    lcd.setCursor(0, 1);
    lcd.print("Umid. = ");  
    lcd.print(mediaUmid);
    lcd.print("%");
    tone(10,800); } //Toca o buzzer
  else if (mediaUmid >= 50 && mediaUmid <= 70) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, LOW);
    lcd.print("Umidade OK");
    lcd.setCursor(0, 1);
    lcd.print("Umid. = "); 
    lcd.print(mediaUmid);
    lcd.print("%");
    noTone(10); }
  else {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    lcd.print("Umid. Alta");
    lcd.setCursor(0, 1);
    lcd.print("Umid. = ");
    lcd.print(mediaUmid);
    lcd.print("%");
    tone(10,800); } //Toca o buzzer
  delay(5000);
  }
  DHT.read11(pinoDHT11); //LÊ AS INFORMAÇÕES DO SENSOR
  Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(DHT.humidity); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
  Serial.print("%"); //ESCREVE O TEXTO EM SEGUIDA
  Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(DHT.temperature, 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL
  delay(2000); //INTERVALO DE 2 SEGUNDOS *NÃO DIMINUIR ESSE VALOR