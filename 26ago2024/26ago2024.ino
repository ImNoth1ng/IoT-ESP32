#define pmt 33

void setup() {
  Serial.begin(115200);

}

void loop() { 
  Serial.println("lectura: " +  String(analogRead(pmt)));
  delay(300);
}
