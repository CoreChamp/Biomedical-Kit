int redPin =7;
int greenPin = A3;
int bluePin = 4;
int buzzer = 6;
int smokeA0 = A0;
// Your threshold value
int sensorThres = 100;
 
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}
 
void loop() {
  int analogSensor = analogRead(smokeA0);
 
  Serial.print("Smoke Level: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    Serial.println("Smoke Detected!");
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    Serial.println("Normal");
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH);
    noTone(buzzer);
  }
  delay(500);

}
