#include <SoftwareSerial.h>

#define TX 36
#define RX 39

SoftwareSerial MiSerial(RX, TX);
String tmsg= "";
String rmsg= "";

const String Id = "PC1  :";

void setup() {
  // put your setup code here, to run once:
  MiSerial.begin(9600);
  Serial.begin(9600);

}

void loop() {
  tmsg = Serial.read();
  if(tmsg != ""){
    MiSerial.print(Id + tmsg);
    tmsg = "";
  }

  rmsg = MiSerial.read();
  if(rmsg != ""){
  Serial.println(rmsg);
  rmsg = "";  
  }
  

  

}
