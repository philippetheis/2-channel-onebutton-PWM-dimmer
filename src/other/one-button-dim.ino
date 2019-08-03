/*
LED-dimming-switch.ino
 ==========================

 Copyright (c) by Philippe Theis

 **********************
 SW Version: 0.1
 HW Version: 0.1
 Date: 20-07-2019
 **********************

 The library internals are explained at
 http://www.mathertel.de/Arduino/OneButtonLibrary.aspx

 Setup a test circuit:
 * Connect a pushbutton to pin A4 (ButtonPin) and ground.
 * The pin 9 (StatusPin) is used for output attach a led and resistor to ground.

 Button: A4
 LED red: pin9
 */

// 20.07.2018 created by Philippe Theis

#include "OneButton.h"
#include "avdweb_VirtualDelay.h"
#include <Streaming.h>

int longpressed = 0;

//Non-Blicking LED
int stateled = 0;
int ledState = LOW;
const long ledInterval = 100;
// TIME GENERAL
unsigned long previous_led_Millis = 0;        // will store last time LED was update

//dimmer
int lamp = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int fadeoutstart = 0;
int fadeinstart = 0;

// The actions I ca do...
typedef enum {
  ACTION_0,  // init action
  ACTION_1,  // first button pressure
  ACTION_2,  // second button pressure
  ACTION_3,  // third button pressure
  //ACTION_OPEN_3,  // open to position 3
}

MyActions;

// Setup a OneButton on pin A1.
OneButton button(A4, true);

MyActions nextAction = ACTION_0; // no action when starting

// - - - - - - - - - - - - - - - - - - - - - Finish Initialisation - - - - - - - - - - - - - - - - - - - - -


// setup code here, to run once:
void setup() {

  // delay(3000);

  pinMode(13, OUTPUT);     // sets the digital pin as output (Arduino Nano OnBoard LED)
  pinMode(9, OUTPUT);      // sets the digital pin as output (MOS-Fet Transistor)
  //pinMode(3, OUTPUT);      // sets the digital pin as output (MOS-Fet Transistor)
  //digitalWrite(2, HIGH);   // need to activated the the rails ticks not in the initialisation

  // link the myClickFunction function to be called on a click event.
  button.attachClick(myClickFunction);

  // link the myClickFunction function to be called on a long press event.
  button.attachDuringLongPress(longPress);

  Serial.begin(9600); // open the serial port at 9600 bps:
  Serial.print("START LOGGING\n");


} //END setup


// main code here, to run repeatedly:
void loop() {

  // keep watching the push button:
  button.tick();

  // Function motorControl (Relais)
  menuActions();

  // Function LED
  //LEDblink();

} // END Main loop

void menuActions() {

  // if ((nextAction == ACTION_100) && (initPosition == 0)) {
  if (nextAction == ACTION_1) {
    dim1();
  }

  else if (nextAction == ACTION_2) {
    dim2();
  }

  else if (nextAction == ACTION_3) {
    dim3();
  }

  else if (nextAction == ACTION_0) {
    stop();
  }

} // menuActions


void dim1() {
  Serial.print("Action 1'\n'");
  analogWrite(lamp, 1);
}

void dim2() {
  Serial.print("Action 2'\n'");
  analogWrite(lamp, 15);
}

void dim3() {
  Serial.print("Action 3'\n'");
  analogWrite(lamp, 255);
}

void stop() {
  Serial.print("STOP'\n'");
  digitalWrite(9, LOW);
}





void LEDblink()
{
    // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();

  if ((stateled == 1) && (currentMillis - previous_led_Millis >= ledInterval))
  {
    previous_led_Millis = currentMillis;
     // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(13, ledState);
  }

}


void fadein() {
  if (fadeoutstart == 1) {
    // fade in from min to max in increments of 5 points:
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      // sets the value (range from 0 to 255):
      analogWrite(lamp, fadeValue);
      }
    }
  else {
  }
}

void fadeout() {
  if (fadeinstart == 1) {
    // fade out from max to min in increments of 5 points:
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      // sets the value (range from 0 to 255):
      analogWrite(lamp, fadeValue);
      }
    }
  else {
  }
}


// this function will be called when the button was pressed 1 time and them some time has passed.
void myClickFunction() {
  longpressed = 0;
  if (nextAction == ACTION_0)
    nextAction = ACTION_1;
  else if (nextAction == ACTION_1)
    nextAction = ACTION_2;
  else if (nextAction == ACTION_2)
    nextAction = ACTION_3;
  else if (nextAction == ACTION_3)
    nextAction = ACTION_1;
} // myClickFunction


// longpress
// this function will be called when the button was for a long time
void longPress() {
  longpressed = 1;
  if (nextAction == ACTION_0)
    nextAction = ACTION_0;
  else if (nextAction == ACTION_1)
    nextAction = ACTION_0;
  else if (nextAction == ACTION_2)
    nextAction = ACTION_0;
  else if (nextAction == ACTION_3)
    nextAction = ACTION_0;
}

// End
