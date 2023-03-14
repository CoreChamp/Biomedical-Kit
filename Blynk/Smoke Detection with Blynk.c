#define BLYNK_TEMPLATE_ID "TMPLAQTecbqy"
#define BLYNK_TEMPLATE_NAME "corechamp"
#define BLYNK_AUTH_TOKEN "12VdYlEtCSGYq6buJWmmYKwy7EKDtX6n"

#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Enter Wifi Name";
char pass[] = "Enter Password";

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX

WidgetLCD lcd(V2);

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

int redPin =7;
int greenPin = A3;
int bluePin = 4;

int buzzer = 6;
int smokeA0 = A0;
// Your threshold value
int sensorThres = 100;

void sendSensor()
{
  int analogSensor = analogRead(smokeA0);

 
  Serial.print("Smoke Level: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value

 Blynk.virtualWrite(V3, analogSensor);
  

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "CORECHAMP"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  
  if (analogSensor > sensorThres)
  {
    Serial.println("Smoke Detected!");
    lcd.print(0, 1, "Smoke Detected!");
    tone(buzzer, 1000, 200);
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
  }
  else
  {
    Serial.println("Normal");
    lcd.print(6, 1,"Normal");
    noTone(buzzer);
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH);
  }
  delay(1000);

}

void setup() {

  Serial.begin(9600);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
   Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  Blynk.run();
  timer.run();
}
