#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

const int trigPin = 5;      // Pin compartido para todos los triggers
const int echoPin1 = 6;     // Echo del sensor 1
const int echoPin2 = 7;     // Echo del sensor 2
const int echoPin3 = 8;     // Echo del sensor 3
const int echoPin4 = 9;     // Echo del sensor 4

#define SD_CS 10            // Chip Select para la SD (ajustar según tu conexión)
#define SD_MOSI 11          // MOSI (no cambiar - pin fijo para SPI)
#define SD_MISO 13          // MISO (no cambiar - pin fijo para SPI)
#define SD_SCK 12           // SCK (no cambiar - pin fijo para SPI)

File dataFile;
unsigned long measurementCount = 0;

float measureDistance(int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}


void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);
  digitalWrite(trigPin, LOW);
  
  if (!SD.begin(SD_CS)) {
    Serial.println("Error al inicializar la tarjeta SD");
    while (1);
  }
  Serial.println("SD card inicializada correctamente");
  
  dataFile = SD.open("/datalog.txt", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Error al abrir el archivo");
    while (1);
  }
  
  if (dataFile.size() == 0) {
    dataFile.println("Medición,Sensor1(cm),Sensor2(cm),Sensor3(cm),Sensor4(cm)");
  }
  dataFile.close();
  
  Serial.println("Sistema listo");
}

void loop() {
  float distances[4];
  distances[0] = measureDistance(echoPin1);
  delay(30);
  distances[1] = measureDistance(echoPin2);
  delay(30);
  distances[2] = measureDistance(echoPin3);
  delay(30);
  distances[3] = measureDistance(echoPin4);
  
  Serial.print(measurementCount);
  Serial.print(", ");
  for (int i = 0; i < 4; i++) {
    Serial.print(distances[i]);
    Serial.print(i < 3 ? ", " : "\n");
  }
  
  dataFile = SD.open("/datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print(measurementCount);
    dataFile.print(", ");
    for (int i = 0; i < 4; i++) {
      dataFile.print(distances[i]);
      dataFile.print(i < 3 ? ", " : "\n");
    }
  }
}