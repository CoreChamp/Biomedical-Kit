#define BLYNK_TEMPLATE_ID "TMPLAQTecbqy"
#define BLYNK_TEMPLATE_NAME "corechamp"
#define BLYNK_AUTH_TOKEN "12VdYlEtCSGYq6buJWmmYKwy7EKDtX6n"

#define BLYNK_PRINT Serial

#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h> // Includes the PulseSensorPlayground Library.

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

int PulseWire = A2;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN A2  
int greenPin = A3;
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 580;       // Determine which Signal to "count as a beat", and which to ignore.

PulseSensorPlayground pulseSensor;

void sendSensor()
{
  int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now.
  if (pulseSensor.sawStartOfBeat()) { // Constantly test to see if "a beat happened".
  Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
  Serial.print("BPM: "); // Print phrase "BPM: "
  Serial.println(myBPM); // Print the value inside of myBPM.

  Blynk.virtualWrite(V3, myBPM);
  

  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(4, 0, "CORECHAMP");
  lcd.print(7, 1,"BPM");
  }


delay(500);
}

void setup() {

  Serial.begin(9600);
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
   Blynk.begin(auth, wifi, ssid, pass);

  timer.setInterval(1000L, sendSensor);

  pinMode(greenPin,OUTPUT);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(greenPin); //auto-magically blink LED with heartbeat.
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
  Serial.println("CORECHAMP");
  }

}

void loop() {
  Blynk.run();
  timer.run();
}  

 
