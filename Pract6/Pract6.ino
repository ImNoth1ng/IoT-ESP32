#include <SoftwareSerial.h>

//Programa esclavo que procesa 2 sensores, uno digital y el otro analogico

//sensor de distancia
//sensor touch

#define usT 0
#define usE 4
#define touch 2

int dis; //variable para guardar la lectura del sensor ultrasonico
bool tch; //variable para guardar el estado del touch

const int MySRX = 5; // Pin RX para Serial2
const int MySTX = 18; // Pin TX para Serial2

EspSoftwareSerial::UART myPort;



void setup() {
  Serial.begin(115200); // Inicializa el puerto serial USB a 115200 baudios
  myPort.begin(38400, SWSERIAL_8N1, MySRX, MySTX, false); // Inicializa Serial2 con los pines especificados

  pinMode(usT, OUTPUT);//configuramos los pines que vamos a usar
  pinMode(usE, INPUT);
  digitalWrite(usT, 0);

  pinMode(touch, INPUT);
}

void loop() {

  dis = leerUS();//llamamos la funcion de leer el ultrasonico y guardamos su respuesta
  tch = digitalRead(touch); //leemos la entrada del puerto del touch y guardamos

  //String msg_dat = "Distancia: " + String(dis) +"cm, Touch: " + String(tch) + "\n";

  if(myPort.available() > 0){//si tenemos conexion mandamos los dos mensajes con los datos
    String msg0 = String(dis) + '\n'; 
    myPort.write(msg0.c_str());//datos del sensor ultrasonico
    String msg1 = String(tch) + '\n';
    myPort.write(msg1.c_str());//datos del touch
  }else{
    Serial.println("Error de conexión!");//se utiliza para debugear, en caso de no tener una correcta conexion imprime error
  }
  delay(300);//delay para no sobre saturar de datos
  
 }

int leerUS(){//funcion para leer el ultrasonico
  long t;//declaramos una variable grande para guardar la distancia

  digitalWrite(usT, 1);//mandamos un pulso a trigger
  delayMicroseconds(10);//esperamos 10 microsegundos para que se propage bien
  digitalWrite(usT, 0);//apagamos el trigger

  t = pulseIn(usE, 1);// leermos que ocurrio con la onda

  return t;//regresamos el dato
}

