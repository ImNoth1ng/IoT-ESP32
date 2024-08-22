// Programa IoT 1
// Debe recibir una clave con 3 botones de 5
// Al aceptar la correcta encenderá el led


//Botones
#define btn1 36//a
#define btn2 39//b
#define btn3 34//c
#define btn4 35//d
#define btn5 32//e

bool a;
bool b;
bool c;
bool d;
bool e;

//Led
#define led 26

void setup() {
  Serial.begin(115200);

  //Configuarcion de botones
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  pinMode(btn5, INPUT);

  //Configuración de Led
  pinMode(led, OUTPUT);

}

void loop() {
  ReadBtn();
  if (a & b & c){
    digitalWrite(led, HIGH);
      delay(1000);
      Serial.println("Abierto");
      digitalWrite(led, LOW);
      delay(1000);
    }
    else if (a | b | c | d | e) {
      
      Serial.println("Clave incorrecta");
    }

    clsbtn();
    delay(400);
    
  
}



void ReadBtn(){
    
    if (digitalRead(btn1)){
      a = true;
    }
    if (digitalRead(btn2)){
      b = true;
    }
    if (digitalRead(btn3)){
      c = true;
    }
    if (digitalRead(btn4)){
      d = true;
    }
    if (digitalRead(btn5)){
      e = true;
    }
}

void clsbtn(){
  a = false;
  b = false;
  c = false;
  d = false;
  e = false;
}
