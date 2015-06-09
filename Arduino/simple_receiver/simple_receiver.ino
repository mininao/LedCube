// Arduino cube light program
// By Guillaume Jolin & Maxence Aïci

// Pins 23 to 50 : RGB Columns
// Pins 5,6,7 : Layers

#define baseDelay 1
#define redStartPin 23
#define colorPrecision 0.75 // Default = 1, Recommended = 0.5 // Lower = Faster, but less bright and contrasted
#define debug false


int curIndex; // Represents the number of leds currently lit
char ledsState[] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
                    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
                    255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}; // 27 leds * 3 colors //red Pin =  x*3 + y*9 + z*27;
  
void light(long time) {
    long startTime = millis();        
    while (millis() - startTime < time) {
          for (byte k = 0; k < 3; ++k) {
            
            digitalWrite(k+5, LOW);
            
            for(byte i = 0; i < 27; ++i) {
              
              int indix = i + k*27;
              
              if((int)(ledsState[indix]*colorPrecision) != 0) {
                digitalWrite(i + redStartPin, HIGH);
                delayMicroseconds((int)(ledsState[indix]*colorPrecision));
                digitalWrite(i + redStartPin, LOW);
              }
            }
            
            digitalWrite(k+5, HIGH);
          }
    }
}

void setup() {
  
  for (byte pin=5; pin<8; pin++) { // Turn off the planes (pins 5 to 7)
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
  
  for (byte pin=23; pin<51; pin++) { // Turn off the columns (pins 23 to 50)
    pinMode( pin, OUTPUT );
    digitalWrite(pin, LOW);
  }
  Serial.begin(57600);
  Serial.setTimeout(3);
}

void loop() {
    
  if(debug) {if(Serial.available() == 0) { Serial.print("Nothing to read, displaying "); }}
  while (Serial.available() == 0) { // Nothing to do, let's display the leds
    light(5); // Durée : 0ms à 20ms
  }
  Serial.readBytes(ledsState, 81);
}
