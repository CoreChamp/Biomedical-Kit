#define BLYNK_TEMPLATE_ID "TMPL3nZ3eUBgo"
#define BLYNK_TEMPLATE_NAME "Bio Medical"
#define BLYNK_AUTH_TOKEN "v6spT9zMWIA3iiFXT95L2T_7is9PBMwO"

#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "Innova8";
char pass[] = "innova8.in";


#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 12); // RX, TX

WidgetLCD lcd(V2);

// Your ESP8266 baud rate:
#define ESP8266_BAUD 4800

ESP8266 wifi(&EspSerial);

BlynkTimer timer;


#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 5 on the Arduino
#define ONE_WIRE_BUS 5

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
//ALCOHAL SENSOR
#define MQ3 A1

float sensorvalue;
//ULTRASONIC FOR HIGHT
#define echoPin 3 
#define trigPin 2                                           
 
 
long duration; // Variable to store time taken to the pulse
               // to reach receiver
 
int distance; // Variable to store distance calculated using


//SMOKE
int smokeA0 = A0;
// Your threshold value


void sendSensor(){

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, sensors.getTempCByIndex(0));
  Blynk.virtualWrite(V1, (sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "INNOVA8");

  // Send the command to get temperatures
  sensors.requestTemperatures(); 

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("°C  |  ");
  
  //print the temperature in Fahrenheit
  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.println("°F");

  lcd.print(2, 1, "TEMPERATURE:");

  
  delay(500);
}
void sendalcohalvalue()
{
  sensorvalue = analogRead(MQ3); // read analog input pin A1
  Serial.print("Sensor Value: ");
  Serial.print(sensorvalue);

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, sensorvalue);
     
        delay(100); 
}
void sendHIGHT(){

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V4, distance);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // wait for 2 ms to avoid
                          // collision in serial monitor
 
  digitalWrite(trigPin,HIGH); // turn on the Trigger to generate pulse
  delayMicroseconds(10);      // keep the trigger "ON" for 10 ms to generate
                                // pulse for 10 ms.
 
  digitalWrite(trigPin,LOW); // Turn off the pulse trigger to stop
                               // pulse generation
 
  // If pulse reached the receiver echoPin
  // become high Then pulseIn() returns the
  // time taken by the pulse to reach the
  // receiver
 
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2; // Expression to calculate
                               
  Serial.print("HEIGHT: ");
  Serial.print(distance); // Print the output in serial monitor
  Serial.println(" cm");
  lcd.print(0, 1, "HEIGHT:");
  lcd.print(8,1,distance);
  lcd.print(12,1,"cm");
  delay(100);              
}

void sendSMOKE()
{
  int analogSensor = analogRead(smokeA0);

 
  Serial.print("Smoke Level: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value

 Blynk.virtualWrite(V5, analogSensor);
}
  void setup(void)
{
  // Debug console
  Serial.begin(4800);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
   Blynk.begin(auth, wifi, ssid, pass);
  pinMode(MQ3,INPUT);
   pinMode(trigPin,OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  timer.setInterval(100L, sendSensor);
  timer.setInterval(100L, sendalcohalvalue);
   timer.setInterval(100L, sendHIGHT);
   timer.setInterval(100L, sendSMOKE);

  sensors.begin();  // Start up the library
  Serial.begin(4800);
  Serial.println("INNOVA8");
    delay(500);
}

void loop() {
  Blynk.run();
  timer.run();
}
