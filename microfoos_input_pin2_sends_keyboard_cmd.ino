/*
  State change detection (edge detection)

 Often, you don't need to know the state of a digital input all the time,
 but you just need to know when the input changes from one state to another.
 For example, you want to know when a button goes from OFF to ON.  This is called
 state change detection, or edge detection.

 This example shows how to detect when a button or button changes from off to on
 and on to off.

 The circuit:
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 * LED attached from pin 13 to ground (or use the built-in LED on
   most Arduino boards)

 created  27 Sep 2005
 modified 30 Aug 2011
 by Tom Igoe
.
This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/ButtonStateChange

 */
//edited for microbit foosball by spencer marsden
//bits from adafruit dotstar led code

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>     

#define NUMPIXELS 90 // Number of LEDs in strip
const int  buttonPinA = 2;    // the pin that the MicrobitA is attached to
const int  buttonPinB = 3;    // the pin that the MicrobitB is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonStateA = 0;         // current state of the buttonA
int lastButtonStateA = 0;     // previous state of the buttonA
int buttonStateB = 0;         // current state of the buttonA
int lastButtonStateB = 0;     // previous state of the buttonA

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPinA, INPUT);
  pinMode(buttonPinB, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
    // initialize control over the keyboard:
  //Keyboard.begin();
  // initialize serial communication:
  Serial.begin(9600);
  strip.begin(); // Initialize led strip pins for output
  strip.show();  // Turn all LEDs off ASAP
}
// Runs 10 LEDs at a time along strip, cycling through red, green and blue.
// This requires about 200 mA for all the 'on' pixels + 1 mA per 'off' pixel.

int      head  = 0, tail = -10; // Index of first 'on' and 'off' pixels
uint32_t color = 0xFF0000;      // 'On' color (starts red)


void loop() {
  // read the pushbutton input pin:
  buttonStateA = digitalRead(buttonPinA);
  buttonStateB = digitalRead(buttonPinB);

  // compare the buttonStateA to its previous state
  if (buttonStateA != lastButtonStateA) {
    // if the state has changed, increment the counter
    if (buttonStateA == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      //Keyboard.print("."); //"." is play in omxplayer gui
      Serial.println("on");
      Serial.print("number of goals:  ");
      Serial.println(buttonPushCounter);
      
      for (int i=0; i <= 90; i++)
      {
      strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(10);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
      color = 0xFF0000;
      }
      if(++tail >= NUMPIXELS) tail = -0; // Increment, reset tail index......
    }
    //delay(1000);
    //Keyboard.print(".");
    
    }
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(10);
  }

    if (buttonStateB != lastButtonStateB) {
    // if the state has changed, increment the counter
    if (buttonStateB == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      //Keyboard.print("."); //"." is play in omxplayer gui
      Serial.println("on");
      Serial.print("number of goals:  ");
      Serial.println(buttonPushCounter);
      
      for (int i=0; i <= 90; i++)
      {
      strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(10);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
      color = 0xFF0000;
      }
      if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index......
    }
    //delay(1000);
    //Keyboard.print(".");
    
    }
    else {
      
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonStateA = buttonStateA;
    lastButtonStateB = buttonStateB;
    //perhaps put non goal LED fx here?

 // strip.show();                     // Refresh strip
  
    
//if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index

}







