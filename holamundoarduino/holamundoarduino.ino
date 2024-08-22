// Este programa prende y apaga un led en la veriable led

//Led
#define led 26
#define btn1 36//a

void setup() {
  pinMode(led, OUTPUT); //Declarando puerto led como salida
  pinMode(btn1, INPUT);

}

void loop() {
  if (!digitalRead(btn1)) {
    digitalWrite(led, 1);
  }else {
    digitalWrite(led,0);
  }
  

}
