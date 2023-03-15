int PulseSensorPurplePin = A2;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN A2
int greenPin = A3 ;   

int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 580;       // Determine which Signal to "count as a beat", and which to ingore.

void setup() {
  pinMode(greenPin,OUTPUT);         // pin that will blink to your heartbeat!
   Serial.begin(9600);         // Set's up Serial Communication at certain speed.

}

void loop() {

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.
   Serial.println(Signal);                    // Send the Signal value to Serial Plotter.

   if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" LED.
     digitalWrite(greenPin,HIGH);
   } else {
     digitalWrite(greenPin,LOW);                //  Else, the sigal must be below "550", so "turn-off" LED.
   }


delay(10);

}
