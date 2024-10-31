#include <AdafruitIO_WiFi.h>

const char* ssid = "";
char* password = "";

String lastRes;

#define IO_USERNAME  ""
#define IO_KEY       ""
AdafruitIO_WiFi clienteIO(IO_USERNAME, IO_KEY, ssid, password);

// Feeds para recibir comandos y enviar datos
AdafruitIO_Feed *FeedLuz = clienteIO.feed("PruebaLuz");
AdafruitIO_Feed *FeedOscuro = clienteIO.feed("PruebaOscuro");
AdafruitIO_Feed *FeedDatos = clienteIO.feed("PruebaIoT28");

// Definición de pines
const int ldrPin = 36; // Pin analógico donde está conectado el LDR
const int motorOpenPin = 12; // Pin digital para abrir la persiana
const int motorClosePin = 14; // Pin digital para cerrar la persiana

// Umbrales de luz en porcentaje
const int openThreshold = 60; // Umbral para abrir la persiana
const int closeThreshold = 30; // Umbral para cerrar la persiana

// Estado de la persiana
bool isBlindOpen = false;

void MensajeRecibido(AdafruitIO_Data *data) {
  Serial.println("Recibido: ");

  String sRecibido = data->value();
  Serial.println(sRecibido);
  
  if(lastRes == sRecibido){
    Serial.println("Mismo estado!");
  } else {
    if (sRecibido == "Luz") {
      lastRes = "Luz";
      Serial.println("Abriendo persiana!");
      Serial.println("Luz alta, abriendo persiana...");
      digitalWrite(motorOpenPin, HIGH);
      digitalWrite(motorClosePin, LOW);
      delay(6000); // Tiempo para abrir la persiana
      digitalWrite(motorOpenPin, LOW);
    } else if (sRecibido == "Oscuro") {
      lastRes = "Oscuro";
      Serial.println("Luz baja, cerrando persiana...");
      digitalWrite(motorClosePin, HIGH);
      digitalWrite(motorOpenPin, LOW);
      delay(6000); // Tiempo para cerrar la persiana
      digitalWrite(motorClosePin, LOW);
      isBlindOpen = false;
    }
  }
}

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
  Serial.println("Iniciando la conexion con WiFi");
  clienteIO.connect();

  Serial.println("Conectando a: " + String(ssid));
  while (clienteIO.status() < AIO_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  Serial.println("Conexión exitosa");

  // Asignar callbacks a los feeds de comandos
  FeedLuz->onMessage(MensajeRecibido);  
  FeedOscuro->onMessage(MensajeRecibido);

  Serial.println("Conectando a AdafruitIO");
  delay(5000);
}

void loop() {
  // Leer el valor del LDR
  int ldrValue = analogRead(ldrPin);

  // Mapear el valor del LDR a un porcentaje (0-100)
  int lightPercentage = map(ldrValue, 0, 4095, 100, 0);

  // Imprimir el porcentaje de luz para monitoreo
  Serial.print("Light Percentage: ");
  Serial.println(lightPercentage);

  // Enviar el porcentaje de luz al feed de datos
  Serial.println("Enviando el porcentaje de luz: " + String(lightPercentage));
  FeedDatos->save(lightPercentage);
  Serial.println("Valor enviado a AdafruitIO");
  
  clienteIO.run();
  delay(30000);
  Serial.println("---------------");
}
