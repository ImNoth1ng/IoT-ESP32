#include <SoftwareSerial.h>
const int MySRX = 5; // Pin RX para Serial2
const int MySTX = 18; // Pin TX para Serial2
EspSoftwareSerial::UART myPort;

String lect = "";//variable que usamos para recibir los caracteres de la comunicación uart

int lec[1] = {};//arreglo para guardar los datos recibidos y poder usarlos como enteros
int i = 0;//bandera de intercambio entre el primer y segundo dato del arreglo lec[]

int d;//variable para guardar la distancia ya procesada en centimetros

String tch = "";//variable para guardar el estado del toch en string

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Inicializa el puerto serial USB a 115200 baudios
  myPort.begin(38400, SWSERIAL_8N1, MySRX, MySTX, false); // Inicializa Serial2 con los pines especificados
}

void loop() {
  while(myPort.available()){//mientras se encuentre disponible un dato en la comunicación
    char msg = myPort.read();//leemos caracter por caracter 
    lect.concat(msg);//agregamos a la variable lect para ir guardando los caracteres
    if(msg == '\n'){//en cuanto detectamos fin de cadena, cambiamos al siguiente espacio de arreglo
      lec[i] = lect.toInt();//antes de cambiar transformamos a entero y guardamos en su posición del arreglo
      if(i == 1){//hacemos el intercambio de lugar con la bandera
        i = 0;
      }else{
        i = 1;
      }
      lect = "";//reiniciamos nuestra variable para el siguiente dato
    }
  
    //Serial.print(msg);
    d = lec[0]/59;//trandormamos los datos del ultrasonico en distancia en centimetros
    if(lec[1] == 1){//tranformamos en string el valor del touch
      tch = "Presionado";
    } else {
      tch = "No Presionado";
    }
    String msg_dat = "Distancia: " + String(d) + "cm, Touch: " + tch;//creamos el paquete de la lectura de los datos en un string
    Serial.println(msg_dat);//imprimimos en monitor serie
    Serial.println("-----------");//se utiliza solo para separar las lecturas
  }
  

}
