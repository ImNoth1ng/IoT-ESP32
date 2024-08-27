#define pmt 36

void setup() {
  Serial.begin(115200);

}

void loop() { 
  Serial.println("lectura: " +  String(analogRead(pmt)));
  delay(300);
}
