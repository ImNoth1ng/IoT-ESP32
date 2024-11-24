#include <DHT.h>

// Definimos los pines para los sensores
const int ldrPin = 4;          // Pin analógico para el LDR
const int rainSensorPin = 0;   // Pin analógico para el sensor de lluvia
const int dhtPin = 2;           // Pin digital para el sensor DHT

// Definimos el tipo de sensor DHT
#define DHTTYPE DHT11   // Cambia a DHT22 si usas ese modelo

// Creamos una instancia del sensor DHT
DHT dht(dhtPin, DHTTYPE);

void setup() {
// Inicializamos la comunicación serie
Serial.begin(9600);

// Inicializamos el sensor DHT
dht.begin();
}

void loop() {
// Leemos los valores de los sensores
int ldrValue = analogRead(ldrPin);
int rainValue = analogRead(rainSensorPin);

// Leemos la temperatura y la humedad
float humidity = dht.readHumidity();
float temperature = dht.readTemperature();

// Verificamos si la lectura del sensor DHT falló
if (isnan(humidity) || isnan(temperature)) {
  Serial.println("Error al leer el sensor DHT!");
} else {
  // Mostramos los valores en la consola
  Serial.print("LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(" | Rain Sensor Value: ");
  Serial.print(rainValue);
  Serial.print(" | Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}

// Esperamos un segundo antes de la siguiente lectura
delay(1000);
}
