#define Sober 250   // Define max value that we consider sober
#define Drunk 400   // Define min value that we consider drunk
#define MQ3 A1

int redPin =7;
int greenPin = A3;
int bluePin = 4;

float sensorValue;  //variable to store sensor value

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("MQ3 Heating Up!");
  delay(20000); // allow the MQ3 to warm up
}

void loop() {
  sensorValue = analogRead(MQ3); 
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
            

  if (sensorValue < Sober) {
    Serial.println("  |  Status: Sober");
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH);
    digitalWrite(bluePin,LOW);

  } else if (sensorValue >= Sober && sensorValue < Drunk) {
    Serial.println("  |  Status: Drinking but within legal limits");
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,HIGH);

  } else {
    Serial.println("  |  Status: DRUNK");
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,LOW);

  }
  Serial.print("\n");
  delay(1000); 

}
