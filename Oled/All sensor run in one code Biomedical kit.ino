#include <OneWire.h>
#include <DallasTemperature.h>
#define echoPin 3 
#define trigPin 2 

long duration; // Variable to store time taken to the pulse
               // to reach receiver
int distance; // Variable to store distance calculated using
              // formula


// Data wire is plugged into digital pin 5 on the Arduino
#define ONE_WIRE_BUS 5

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define MQ2_PIN A1
int smoke = A0;
int sensorThres = 200;
//pulse




#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NEXT_BUTTON_PIN 12    // Digital pin connected to the "Next" button
#define PREV_BUTTON_PIN 10// Digital pin connected to the "Previous" button

int nextButtonState = 0;
int prevButtonState = 0;
int currentSensor = 1; // Default sensor is temp

//#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math
//#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library
//
//const int PulseWire = A2;       // 'S' Signal pin connected to A2
////const int LED13 = 13;          // The on-board Arduino LED
//int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore
//                               
//PulseSensorPlayground pulseSensor;  // Creates an object
//


void setup() {
  Serial.begin(9600);
  pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistors
  pinMode(PREV_BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistors
  pinMode(trigPin,OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(smoke, INPUT);


   //pulseSensor.analogInput(PulseWire);   
//  pulseSensor.blinkOnPulse(LED13);       // Blink on-board LED with heartbeat
 // pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and began seeing a signal
//  if (pulseSensor.begin()) {
//    Serial.println("PulseSensor object created!");
//  }


  
// Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  //display.display();
  //delay(1000);  // Pause for 2 seconds
  display.clearDisplay();
  displayCurrentSensor();
}





void loop() {
  // Read the button states
  nextButtonState = digitalRead(NEXT_BUTTON_PIN);
  prevButtonState = digitalRead(PREV_BUTTON_PIN);

  if (nextButtonState == LOW) {
    // Move to the next sensor when the "Next" button is pressed
    currentSensor++;
    if (currentSensor > 5) {
      currentSensor = 1;
    }
    displayCurrentSensor();
    delay(500); // Debounce delay
  } else if (prevButtonState == LOW) {
    // Move to the previous sensor when the "Previous" button is pressed
    currentSensor--;
    if (currentSensor < 0) {
      currentSensor = 5;
    }
    displayCurrentSensor();
    delay(500); // Debounce delay
  }
   switch (currentSensor) {
    case 1:
      readtemprature();
      break;
    case 2:
       readMQ2();
      break;
      case 3:
       readhight();
      break;
      case 4:
       readsmoke();
      break;
//      case 5:
//       readbp();
//      break;
       default:
      break;
  }
}
void displayCurrentSensor() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Sensor: ");
  display.print(currentSensor);
  display.setCursor(0, 1);
  display.print("Reading: ");
  display.print(sensorName(currentSensor));

}
String sensorName(int sensor) {
  switch (sensor) {
    case 1:
      return "DHT11 Temp & Hum";
    case 2:
      return "MQ-2 Air Qual";
      default:
      return "Unknown";
      
  }
}
void readtemprature() {

  sensors.requestTemperatures();
  
 display.clearDisplay();
  display.setCursor(10,1);
  display.setTextSize(2);
  display.print("Innova8");
  delay(100);
   display.setCursor(0,25);
  display.setTextSize(2);
  display.print("Temp: "); 
  delay(100);
  display.setCursor(10,45);
  display.setTextSize(1);
  display.print(sensors.getTempCByIndex(0));
  display.print("  deg C");
  delay(100);
  display.setCursor(10,55);
  display.setTextSize(1);
  display.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  display.print("  deg F");
  delay(100);

  display.display();

}
void readMQ2() {
  int analogValue = analogRead(MQ2_PIN);
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("MQ-2 Air Quality");
  display.setCursor(1, 40);
  display.print("Value: ");
  display.print(analogValue);
  display.display();
  
  Serial.print("MQ-2 Sensor - Air Quality: ");
  Serial.println(analogValue);
  
  delay(1000);
}
void readhight() {
   digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // wait for 2 ms to avoid
                          // collision in serial monitor
 
    digitalWrite(trigPin,HIGH); // turn on the Trigger to generate pulse
    delayMicroseconds(10);      // keep the trigger "ON" for 10 ms to generate
                                // pulse for 10 ms.
 
    digitalWrite(trigPin,LOW); // Turn off the pulse trigger to stop
                               // pulse generation
 
    
 
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.0344 / 2; // Expression to calculate
                                 // distance using time
 
    Serial.print("HEIGHT: ");
    Serial.print(distance); 
    Serial.println(" cm");
    delay(100);

    display.clearDisplay();
  display.setCursor(10,1);
  display.setTextSize(2);
  display.print("innova8");
  delay(100);
  display.setCursor(0,20);
  display.setTextSize(2);
  display.print("Height: "); 
  delay(100);
  display.setCursor(0,40);
  display.setTextSize(2);
  display.print(distance);
  display.print("cm");
  delay(100);

  display.display();

  delay(2000);
}
void readsmoke() {
    int analogSensor = analogRead(smoke);
 
  Serial.print("Smoke Level: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value

  display.clearDisplay();
//  display.setCursor(10,1);
//  display.setTextSize(2);
//  display.print("CORECHAMP");
//  delay(100);
  display.setCursor(10,1);
  display.setTextSize(2);
  display.print("Alcohal VALUE: "); 
  delay(100);
  display.print(analogSensor);
  delay(100);
  
  if (analogSensor > sensorThres)
  {
    Serial.println("Smoke Detected!");
    //tone(buzzer, 1000, 200);
    display.setCursor(9,30);
    display.setTextSize(2);
    display.print("!!SMOKE!!"); 
    delay(100);
    display.setCursor(15,48);
    display.print("DETECTED"); 
    delay(100);
    
  }
  else
  {
    display.setCursor(15,39);
    display.setTextSize(2);
    display.print("NORMAL"); 
    delay(100);
  }
  delay(500);

  display.display();

  delay(1000);
}
//void readbp(){
// int myBPM = pulseSensor.getBeatsPerMinute();      // Calculates BPM
//
//  if (pulseSensor.sawStartOfBeat()) {               // Constantly test to see if a beat happened
//    Serial.println("♥  A HeartBeat Happened ! "); // If true, print a message
//    Serial.print("BPM: ");
//    Serial.println(myBPM); // Print the BPM value
//    
//    display.clearDisplay();
//  display.setTextSize(2);
//  display.setTextColor(SSD1306_WHITE);
//  display.setCursor(0, 0);
//  display.print("BPM");
//  display.setCursor(1, 40);
//  display.print("Value: ");
//  display.print(myBPM);
//  display.display();
//  
//  delay(1000);
//    }
//
//  //delay(100);
//
//}




  
