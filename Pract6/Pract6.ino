#include <SoftwareSerial.h>

//Programa esclavo que procesa 2 sensores, uno digital y el otro analogico

//sensor de distancia
//sensor touch

#define usT 0
#define usE 4
#define touch 2

int dis;
bool tch;

const int MySRX = 5; // Pin RX para Serial2
const int MySTX = 18; // Pin TX para Serial2

EspSoftwareSerial::UART myPort;



void setup() {
  Serial.begin(115200); // Inicializa el puerto serial USB a 115200 baudios
  myPort.begin(38400, SWSERIAL_8N1, MySRX, MySTX, false); // Inicializa Serial2 con los pines especificados

  pinMode(usT, OUTPUT);
  pinMode(usE, INPUT);
  digitalWrite(usT, 0);

  pinMode(touch, INPUT);
}

void loop() {

  dis = leerUS();
  tch = digitalRead(touch);

  //String msg_dat = "Distancia: " + String(dis) +"cm, Touch: " + String(tch) + "\n";

  if(myPort.available() > 0){
    String msg0 = String(dis) + '\n'; 
    myPort.write(msg0.c_str());
    String msg1 = String(tch) + '\n';
    myPort.write(msg1.c_str());
  }else{
    Serial.println("Error de conexión!");
  }
  delay(300);
  


  // Si hay datos disponibles en el puerto serial USB, los lee y los envía a Serial2
  // if (Serial.available() > 0) {
  //   String inputString = "PC-2: "+ Serial.readString() + "\n";
  //   Serial2.write(inputString.c_str()); // Convierte el String a const char* y lo envía

  // }

  // Si hay datos disponibles en Serial2, los lee y los envía al puerto serial USB
//   if (Serial2.available() > 0) {
//     String inputString = Serial2.readString();
//     Serial.write(inputString.c_str()); // Convierte el String a const char* y lo envía
//   }
 }

int leerUS(){
  long t;

  digitalWrite(usT, 1);
  delayMicroseconds(10);
  digitalWrite(usT, 0);

  t = pulseIn(usE, 1);

  return t;
}

bool leertch(){
  if(digitalRead(touch)){
    return true;
  }else{
    return false;
  }
}
