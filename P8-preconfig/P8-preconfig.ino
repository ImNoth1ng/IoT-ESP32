// Definición de pines
const int ldrPin = 36; // Pin analógico donde está conectado el LDR
const int motorOpenPin = 12; // Pin digital para abrir la persiana
const int motorClosePin = 14; // Pin digital para cerrar la persiana

// Umbrales de luz en porcentaje
const int openThreshold = 60; // Umbral para abrir la persiana
const int closeThreshold = 30; // Umbral para cerrar la persiana

// Estado de la persiana
bool isBlindOpen = false;

void setup() {
  // Configuración de pines
  pinMode(ldrPin, INPUT);
  pinMode(motorOpenPin, OUTPUT);
  pinMode(motorClosePin, OUTPUT);

  // Inicializar el motor en estado apagado
  digitalWrite(motorOpenPin, LOW);
  digitalWrite(motorClosePin, LOW);

  // Inicializar comunicación serial para monitoreo
  Serial.begin(115200);
}

void loop() {
  // Leer el valor del LDR
  int ldrValue = analogRead(ldrPin);

  // Mapear el valor del LDR a un porcentaje (0-100)
  int lightPercentage = map(ldrValue, 0, 4095, 0, 100);

  // Imprimir el porcentaje de luz para monitoreo
  Serial.print("Light Percentage: ");
  Serial.println(lightPercentage);

  // Verificar si la persiana debe abrirse o cerrarse
  if (lightPercentage > openThreshold && !isBlindOpen) {
    // Abrir la persiana
    Serial.println("Luz alta, abriendo persiana...");
    digitalWrite(motorOpenPin, HIGH);
    digitalWrite(motorClosePin, LOW);
    delay(6000); // Tiempo para abrir la persiana
    digitalWrite(motorOpenPin, LOW);
    isBlindOpen = true;
  } else if (lightPercentage < closeThreshold && isBlindOpen) {
    // Cerrar la persiana
    Serial.println("Luz baja, cerrando persiana...");
    digitalWrite(motorClosePin, HIGH);
    digitalWrite(motorOpenPin, LOW);
    delay(6000); // Tiempo para cerrar la persiana
    digitalWrite(motorClosePin, LOW);
    isBlindOpen = false;
  }

  // Esperar un segundo antes de la siguiente lectura
  delay(1000);
}