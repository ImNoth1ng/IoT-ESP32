// Programa IoT 1
// Debe recibir una clave con 3 botones de 5
// Al aceptar la correcta encenderá el led


//Botones
#define btn1 36//a
#define btn2 39//b
#define btn3 34//c
#define btn4 35//d
#define btn5 32//e

//Led
#define led 26

//CLAVE
const String pass = "acb";
//intento
String entrada;
char press;

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
  delay(180);//delay para la lectura correcta de los botones
  press = '\0';// reseteando el boton pulsado
  digitalWrite(led, LOW);//apagando led
  if (ReadBtn() != '\0'){// si se preciona algo se agrega a entrada
    entrada = entrada + press;
  }
  Serial.println(entrada);

  if (entrada.length() == 3){// si la entrada ya es igual a 3 se verifica
    if (entrada == pass){// si la contraseña es correcta enciende el led
      digitalWrite(led, HIGH);
      delay(1000);
      entrada = "";
    }
    else {//si no es correcta manda dos parpadeos indicativos
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
      entrada = "";
    }
  }
}



char ReadBtn(){
    
    if (digitalRead(btn1) == HIGH) {
    press = 'a';
    Serial.println("a agregado");
    }
    if (digitalRead(btn2) == HIGH) {
    press = 'b';
    Serial.println("b agregado");
    }
    if (digitalRead(btn3) == HIGH) {
    press = 'c';
    Serial.println("c agregado");
    }
    if (digitalRead(btn4) == HIGH) {
    press = 'd';
    Serial.println("d agregado");
    }
    if (digitalRead(btn5) == HIGH) {
    press = 'e';
    Serial.println("e agregado");
    }
    return press;
}
