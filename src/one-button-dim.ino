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

int longpressedB1 = 0;
int longpressedB2 = 0;

// TIME GENERAL
unsigned long previous_led_Millis = 0;        // will store last time LED was update

//dimmer
int lamp1 = 9;           // the PWM pin the LED is attached to
int lamp2 = 10;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int fadeoutstart = 0;
int fadeinstart = 0;

// The actions I ca do...
typedef enum {
  ACTION_0_B1,  // init action
  ACTION_1_B1,  // first button pressure
  ACTION_2_B1,  // second button pressure
  ACTION_3_B1,  // third button pressure
  ACTION_0_B2,  // init action
  ACTION_1_B2,  // first button pressure
  ACTION_2_B2,  // second button pressure
  ACTION_3_B2,  // third button pressure
}

MyActions;

// Setup a OneButton on pin A4 and A5
OneButton button1(A4, true);
OneButton button2(A5, true);

MyActions nextActionB1 = ACTION_0_B1; // no action when starting
MyActions nextActionB2 = ACTION_0_B2; // no action when starting

// - - - - - - - - - - - - - - - - - - - - - Finish Initialisation - - - - - - - - - - - - - - - - - - - - -


// setup code here, to run once:
void setup() {

  pinMode(13, OUTPUT);     // sets the digital pin as output (Arduino Nano OnBoard LED)
  pinMode(9, OUTPUT);      // sets the digital pin as output (MOS-Fet Transistor)
  pinMode(10, OUTPUT);      // sets the digital pin as output (MOS-Fet Transistor)

  // link the myClickFunction function to be called on a click event.
  button1.attachClick(button1Click);
  button2.attachClick(button2Click);

  // link the myClickFunction function to be called on a long press event.
  button1.attachDuringLongPress(button1LongPress);
  button2.attachDuringLongPress(button2LongPress);

  Serial.begin(9600); // open the serial port at 9600 bps:
  Serial.print("START LOGGING\n");


} //END setup


// main code here, to run repeatedly:
void loop() {

  // keep watching the push button:
  button1.tick();
  button2.tick();

  // Menu Actions
  menuActionsB1();
  menuActionsB2();

} // END Main loop

void menuActionsB1() {
  if (nextActionB1 == ACTION_1_B1) {
    dim1_B1();
  }
  else if (nextActionB1 == ACTION_2_B1) {
    dim2_B1();
  }
  else if (nextActionB1 == ACTION_3_B1) {
    dim3_B1();
  }
  else if (nextActionB1 == ACTION_0_B1) {
    stop_B1();
  }
} // menuActions

void menuActionsB2() {
  if (nextActionB2 == ACTION_1_B2) {
    dim1_B2();
  }
  else if (nextActionB2 == ACTION_2_B2) {
    dim2_B2();
  }
  else if (nextActionB2 == ACTION_3_B2) {
    dim3_B2();
  }
  else if (nextActionB2 == ACTION_0_B2) {
    stop_B2();
  }
} // menuActions

//Dimmer 1
void dim1_B1() {
  Serial.print("Button 1: Action 1'\n'");
  analogWrite(lamp1, 1);
}
void dim2_B1() {
  Serial.print("Button 1: Action 2'\n'");
  analogWrite(lamp1, 15);
}
void dim3_B1() {
  Serial.print("Button 1: Action 3'\n'");
  analogWrite(lamp1, 255);
}
void stop_B1() {
  Serial.print("Button 1: STOP'\n'");
  digitalWrite(9, LOW);
}

//Dimmer 2
void dim1_B2() {
  Serial.print("Button 2: Action 1'\n'");
  analogWrite(lamp2, 1);
}
void dim2_B2() {
  Serial.print("Button 2: Action 2'\n'");
  analogWrite(lamp2, 15);
}
void dim3_B2() {
  Serial.print("Button 2: Action 3'\n'");
  analogWrite(lamp2, 255);
}
void stop_B2() {
  Serial.print("Button 2: STOP'\n'");
  digitalWrite(9, LOW);
}


void fadein() {
  if (fadeoutstart == 1) {
    // fade in from min to max in increments of 5 points:
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      // sets the value (range from 0 to 255):
      analogWrite(lamp1, fadeValue);
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
      analogWrite(lamp1, fadeValue);
      }
    }
  else {
  }
}


// this function will be called when the button was pressed 1 time and them some time has passed.
void button1Click() {
  longpressedB1 = 0;
  if (nextActionB1 == ACTION_0_B1)
    nextActionB1 = ACTION_1_B1;
  else if (nextActionB1 == ACTION_1_B1)
    nextActionB1 = ACTION_2_B1;
  else if (nextActionB1 == ACTION_2_B1)
    nextActionB1 = ACTION_3_B1;
  else if (nextActionB1 == ACTION_3_B1)
    nextActionB1 = ACTION_1_B1;
} // button1Click

// this function will be called when the button was pressed 1 time and them some time has passed.
void button2Click() {
  longpressedB2 = 0;
  if (nextActionB2 == ACTION_0_B2)
    nextActionB2 = ACTION_1_B2;
  else if (nextActionB2 == ACTION_1_B2)
    nextActionB2 = ACTION_2_B2;
  else if (nextActionB2 == ACTION_2_B2)
    nextActionB2 = ACTION_3_B2;
  else if (nextActionB2 == ACTION_3_B2)
    nextActionB2 = ACTION_1_B2;
} // button1Click


// longpress
// this function will be called when the button was for a long time
void button1LongPress() {
  longpressedB1 = 1;
  if (nextActionB1 == ACTION_0_B1)
    nextActionB1 = ACTION_0_B1;
  else if (nextActionB1 == ACTION_1_B1)
    nextActionB1 = ACTION_0_B1;
  else if (nextActionB1 == ACTION_2_B1)
    nextActionB1 = ACTION_0_B1;
  else if (nextActionB1 == ACTION_3_B1)
    nextActionB1 = ACTION_0_B1;
}

void button2LongPress() {
  longpressedB2 = 1;
  if (nextActionB2 == ACTION_0_B2)
    nextActionB2 = ACTION_0_B2;
  else if (nextActionB2 == ACTION_1_B2)
    nextActionB2 = ACTION_0_B2;
  else if (nextActionB2 == ACTION_2_B2)
    nextActionB2 = ACTION_0_B2;
  else if (nextActionB2 == ACTION_3_B2)
    nextActionB2 = ACTION_0_B2;
}

// End
