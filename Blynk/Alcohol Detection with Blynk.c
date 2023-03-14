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

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX

WidgetLCD lcd(V2);

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

#define Sober 250   // Define max value that we consider sober
#define Drunk 400   // Define min value that we consider drunk
#define MQ3 A1

int redPin =7;
int greenPin = A3;
int bluePin = 4;

int buzzer = 6;

float sensorvalue;  //variable to store sensor value

void sendSensor()
{
  sensorvalue = analogRead(MQ3); // read analog input pin A1
  Serial.print("Sensor Value: ");
  Serial.print(sensorvalue);

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, sensorvalue);
  

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "CORECHAMP"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")

  if(sensorvalue <Sober){
    lcd.print(6, 1, "SOBER");
    Serial.println("  |  Status: Sober");
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH);
    digitalWrite(bluePin,LOW);
    }
    else if (sensorvalue >= Sober && sensorvalue < Drunk){
      lcd.print(0, 1,"Drunk in Limits");
      Serial.println("  |  Status: Drinking but within legal limits");
      digitalWrite(redPin,LOW);
      digitalWrite(greenPin,LOW);
      digitalWrite(bluePin,HIGH);
      }
        else {Serial.println("  |  Status: DRUNK");
        lcd.print(6, 1,"DRUNK");
        Serial.println("  |  Status: Drunk");
        tone(buzzer, 1000, 200);
        digitalWrite(redPin,HIGH);
        digitalWrite(greenPin,LOW);
        digitalWrite(bluePin,LOW);
        }        
        delay(1000); 
}

void setup() {
  // Debug console
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
  pinMode(MQ3,INPUT);
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("MQ3 Heating Up!");
  delay(20000); // allow the MQ3 to warm up
}

void loop() {
  Blynk.run();
  timer.run();
}
