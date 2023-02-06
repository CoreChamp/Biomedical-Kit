//import all required libraries
#include <SPI.h>
#include <Wire.h>
#include <OneWire.h >
#include <DallasTemperature.h >
#include <Adafruit_GFX.h >
#include <Adafruit_SSD1306.h >
#define OLED_RESET 4 
// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 5
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
Adafruit_SSD1306 display(OLED_RESET);
void setup(void) 
{
  sensors.begin(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("     CORECHAMP  ");
 //Serial.begin(9600);     // initialize the Serial Monitor at a baud rate of 9600
// Start up the library

  
}
void loop(void) 
{
   //display.display(); 
   sensors.requestTemperatures(); 
  float T = sensors.getTempCByIndex(0);
  //Serial.print("Celsius temperature: ");  
// Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
//Serial.println(sensors.getTempCByIndex(0)); 
// get and print the temperature in degree Celsius  
display.setTextSize(1);
display.setTextColor(WHITE); 
display.setCursor(10,9);
display.print("  Temperature:  ");
display.setTextSize(2);// display temperature in deg Celsius
display.setCursor(15,19);
display.print(T);
display.cp437(true);      // code page 437
display.write(167);       // character 167 is degree
display.println("C");display.display();
}
