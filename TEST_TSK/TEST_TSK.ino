#include <WiFi.h>
#include <ThingSpeak.h>

const char* ssid="";
 char* password="";

unsigned long IdCanal = 0;
const char* APIKey = ""

WiFiClient cliente;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando la conexion con WiFi");
  WiFi.begin(ssid, password);

  Serial.println("Conectando a: "+ String(ssid));
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }

  Serial.println("Conexión exitosa");

  Serial.println("COnectando a ThingSpeak");
  ThingSpeak.begin(cliente);
  delay(5000);
  
  
  

}

void loop() {
  for(int i = 0; i <=10; i++){
    Serial.println("Enviando el valor el contador: "+String(i));
    ThingSpeak.setField(1, i);
    ThingSpeak.writeFields(IdCanal, APIKey);
    Serial.println("Valor enviado a tspk");
    delay(20000);
  }

}
