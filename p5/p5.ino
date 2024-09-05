const int MySRX = 17; // Pin RX para Serial2
const int MySTX = 16; // Pin TX para Serial2

void setup() {
  Serial.begin(115200); // Inicializa el puerto serial USB a 115200 baudios
  Serial2.begin(115200, SERIAL_8N1, MySRX, MySTX); // Inicializa Serial2 con los pines especificados
}

void loop() {
  // Si hay datos disponibles en el puerto serial USB, los lee y los envía a Serial2
  if (Serial.available() > 0) {
    String inputString = "PC-2: "+ Serial.readString() + "\n";
    Serial2.write(inputString.c_str()); // Convierte el String a const char* y lo envía
  }

  // Si hay datos disponibles en Serial2, los lee y los envía al puerto serial USB
  if (Serial2.available() > 0) {
    String inputString = Serial2.readString();
    Serial.write(inputString.c_str()); // Convierte el String a const char* y lo envía
  }
}