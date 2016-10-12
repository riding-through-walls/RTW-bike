/* 
Exercise Bike Interface to Google Maps Street View
Based on Keyboard.Message Example Program.
 Sends a text string when a button is pressed.
 Adapted to include more manipulation for 'Riding Trough Walls': a X-Canada Bike ride througuh Google Streetview, performed by Megan Smith.
 
 The circuit:
 * Magnetic reed switch attached from pin 2 to +5V
 * 10-kilohm resistor attached from pin 2 to ground
 
 created 24 Oct 2011
 modified 27 Mar 2012
 by Tom Igoe
 modified 24 June 2012
 by Jeff Adkins
 modified 13 May 2015
 by Megan Smith
 modified 15 October 2015
 by John Campbell
 
This example code is in the public domain.

http://www.arduino.cc/en/Tutorial/KeyboardButton

 */
 //initialization of constants
#define NUMBER_OF_BUTTONS  3
 
#define BUTTON_FORWARD 2
#define BUTTON_LEFT 4
#define BUTTON_RIGHT 3

// number of pedals that invokes a single "up arrow"
#define CRANK_RATIO 5

#define KEYPRESS_DELAY_ON  100
#define KEYPRESS_DELAY_OFF 100

int buttonPin[NUMBER_OF_BUTTONS] = {BUTTON_FORWARD, BUTTON_LEFT, BUTTON_RIGHT};          // input pin for pushbutton
int previousButtonState[NUMBER_OF_BUTTONS] = {HIGH,HIGH,HIGH};   // for checking the state of a pushButton
int counter = 0;                  // button push counter
int debounceFlag1[NUMBER_OF_BUTTONS] = {0,0,0};            // debounce flag 
int debounceFlag2[NUMBER_OF_BUTTONS] = {0,0,0};            // debounce flag
// The debounce flags are two separate magnetic field inputs taken one after the other.
// if they match, then the switch is assumed to have actually triggered.

void setup() {
  // make the pushButton pin an input:
  for(int i=0;i<NUMBER_OF_BUTTONS;i++) {
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
  // initialize control over the keyboard:
  Keyboard.begin();
}

// Main Loop
void loop() {
  int buttonState[NUMBER_OF_BUTTONS]={HIGH,HIGH,HIGH};
  for (int i=0; i<NUMBER_OF_BUTTONS; i++) {
    buttonState[i] = digitalRead(buttonPin[i]);
      switch(buttonPin[i]) {
        case BUTTON_FORWARD:
          if ( (buttonState[i] != previousButtonState[i]) && (buttonState[i] == LOW)) {
              debounceFlag1[i] = buttonState[i];
              delay (3);
              debounceFlag2[i] = digitalRead(buttonPin[i]);
              if (debounceFlag1[i] == debounceFlag2[i]) {
                counter++;
                if (counter>=CRANK_RATIO){
                  counter = 0;
                  Keyboard.press(218);
                  delay(KEYPRESS_DELAY_ON);
                  Keyboard.releaseAll();
                  delay(KEYPRESS_DELAY_OFF);
                }
              }
              debounceFlag1[i] = 0;
              debounceFlag2[i] = 0;
          }
          break;
        case BUTTON_LEFT:
          if(buttonState[i] == LOW) { Keyboard.press(216); }
          else { Keyboard.release(216); }
          break;
        case BUTTON_RIGHT:
          if(buttonState[i] == LOW) {Keyboard.press(215); }
          else { Keyboard.release(215); }
          break;
        default:
          break;
    }
    // save the current button state for comparison next time:
    previousButtonState[i] = buttonState[i]; 
  }
}
/*
        if ((buttonState[i]!= previousButtonState[i]) && (buttonState[i] == LOW)) {
          debounceFlag1[i] = buttonState[i];
          delay (2);
          debounceFlag2[i] = digitalRead(buttonPin[i]);
          if (debounceFlag1[i] == debounceFlag2[i]) {
            counter++;
            if (counter>=CRANK_RATIO){
              counter = 0;
              Keyboard.press(218);
              delay(KEYPRESS_DELAY_ON);
              Keyboard.release(218);
            }
          }
          debounceFlag1[i] = 0;
          debounceFlag2[i] = 0;
 */
