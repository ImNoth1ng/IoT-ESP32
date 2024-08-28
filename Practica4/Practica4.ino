#define pmt 32//definimos el pin del potenciometro

const int led[5] = {14, 27, 26, 25, 33};//declaramos el pin de cada led como constante

int lvl; //variable para guardar el valor del nivel del potenciometro

void setup() {
  Serial.begin(115200);
  pinMode(led[0],OUTPUT);
  pinMode(led[1],OUTPUT);
  pinMode(led[2],OUTPUT);
  pinMode(led[3],OUTPUT);
  pinMode(led[4],OUTPUT);

}

void loop() {
  apagar();//Apagamos todos los led
  Serial.println("---------------");
  lvl = nivel(int(analogRead(pmt)));
 switch(lvl){
  case 0:
    Serial.println("Nivel 0");
    Serial.println("Ningún led encendido");
    break;
  case 1:
    Serial.println("Nivel 1");
    Serial.println("■");
    encender(1);
    break;
  case 2:
    Serial.println("Nivel 2");
    Serial.println("■ ■");
    encender(2);
    break;
  case 3:
    Serial.println(" Nivel 3");
    Serial.println("■ ■ ■");
    encender(3);
    break;
  case 4:
    Serial.println(" Nivel 4");
    Serial.println("■ ■ ■ ■");
    encender(4);
    break;
  case 5:
    Serial.println(" Nivel 5");
    Serial.println("■ ■ ■ ■ ■");
    encender(5);
    break;
 };
 delay(20);
}

int nivel(int x){
  return map(x, 0, 4095, 0, 5);//Utiliza el mapeado para asignar un nivel del 0 a 5 dependiendo de la lectura recibida
}

void apagar(){//funcion que apaga todos los led
  digitalWrite(led[1], LOW);
  digitalWrite(led[2], LOW);
  digitalWrite(led[3], LOW);
  digitalWrite(led[4], LOW);
  digitalWrite(led[0], LOW);
}

void encender(int x){

  switch(x){

    case 1:
    digitalWrite(led[0], HIGH);
    break;

    case 2:
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
    break;

    case 3:
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], HIGH);
    break;

    case 4:
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], HIGH);
    break;

    case 5:
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], HIGH);
    digitalWrite(led[4], HIGH);
    break;

  }
}
