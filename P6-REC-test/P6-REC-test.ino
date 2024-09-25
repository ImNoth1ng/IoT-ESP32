#include <SoftwareSerial.h>
const int MySRX = 5; // Pin RX para Serial2
const int MySTX = 18; // Pin TX para Serial2
EspSoftwareSerial::UART myPort;

String lect = "";

int lec[2] = {};
int i = 0;

int d;

String tch = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Inicializa el puerto serial USB a 115200 baudios
  myPort.begin(38400, SWSERIAL_8N1, MySRX, MySTX, false); // Inicializa Serial2 con los pines especificados
}

void loop() {
  while(myPort.available()){
    char msg = myPort.read();
    lect.concat(msg);
    if(msg == '\n'){
      lec[i] = lect.toInt();
      if(i == 1){
        i = 0;
      }else{
        i = 1;
      }
      lect = "";
    }
  
    //Serial.print(msg);
    d = lec[0]/59;
    if(lec[1] == 1){
      tch = "Presionado";
    } else {
      tch = "No Presionado";
    }
    String msg_dat = "Distancia: " + String(d) + "cm, Touch: " + tch;
    Serial.println(msg_dat);
    Serial.println("-----------");
  }
  

}
