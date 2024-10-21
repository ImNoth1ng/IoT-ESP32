#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid="";
 char* password="";

unsigned long IdCanal = 0;
const char* APIKey = "";

WiFiClient cliente;


#define ECHO_PIN 32
#define TRIG_PIN 33
#define LIGHT_SENSOR_PIN 36
#define MAX_ADC_VALUE 4095


void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(2, OUTPUT);

  Serial.println("Iniciando la conexion con WiFi");
  WiFi.begin(ssid, password);

  Serial.println("Conectando a: "+ String(ssid));
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }

  Serial.println("Conexión exitosa!");

  Serial.println("Conectando a ThingSpeak");
  ThingSpeak.begin(cliente);
  delay(5000);
  Serial.println("Conectado correctamente!");
}

void loop() {
  // Leer el sensor ultrasónico
  long duration;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);

  // Convertir la duración a distancia en centímetros
  float distanceCm = duration * 0.034 / 2;

  // Leer el sensor de luz analógico
  int lightValue = analogRead(LIGHT_SENSOR_PIN);
  float porcentaje = map(lightValue,0 , MAX_ADC_VALUE, 100, 0);
  // Mostrar los valores en la consola
  Serial.print("Distancia: ");
  Serial.print(distanceCm);
  Serial.print(" cm, Luz: ");
  Serial.print(porcentaje);
  Serial.println("%");
  //crear paquete y enviar datos 
  ThingSpeak.setField(1, distanceCm);
  ThingSpeak.setField(2, porcentaje);
  ThingSpeak.writeFields(IdCanal, APIKey);
  digitalWrite(2, 1);
  delay(700);
  digitalWrite(2, 0);
  delay(700);
  Serial.println("Valores enviados a thingspeak");

  delay(20000-1400); // Esperar 20 segundos antes de la siguiente lectura
}