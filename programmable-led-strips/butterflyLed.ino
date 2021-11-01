/**
 * LED STRIP PROJECT FOR BUTTERFLY WING HALLOWEEN COSTUME :)
 * This code lights up LED strips with different patterns. The different patterns 
 * or "modes" are accessed through a simple button connected to an Arduino Uno
 * with a pull-down resistor. The Arduino Uno is powered with a portable cell
 * phone power bank, and the LED strips are additionally connected to a second
 * portable cell phone power bank.
 * 
 * Hardware considerations:
 * 1. 2 LED strips: WS2812B Individual Addressable RGB LED Strip Light 
 * Programmable LED
 * --> for both strips: 
 *     - black to gnd
 *     - red to 5v
 *     - green to 330 ohm resistor to pin7 (or 3 1000 ohm in parallel ;) )
 * --> also, connect 5v to a phone battery charger (you'll need the extra current) 
 *     using a usb to bare-wire cable (we got ours at a store called "make it 
 *     yourself" or something-- very similar to Micro Center)
 * (YouTube: https://www.youtube.com/watch?v=UhYu0k2woRM )
 * 
 * 2. Additional portable power:
 * --> arduino uno through usb to ANOTHER phone battery charger
 * 
 * 3. Push-button for switching light modes:
 * --> pin2 to button leg B
 * --> 5v to button leg C
 * --> ground to ~10kohm resistor to button leg D
 * (Arduino button code & circuit diagram: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button )
 * NOTE: to change modes, you have to wait for when the checkForCounterIncrement 
 * function is called. Sometimes this means holding down the button for a second
 * or two.
 */

#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    60
#define BUTTON_PIN  2
#define NUM_MODES   4

CRGB leds[NUM_LEDS];

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

int r = 0;
int g = 0;
int b = 0;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}
void loop() {
  Serial.print("START OF LOOP; BTN COUNTER: ");
  Serial.println(buttonPushCounter);

  if (buttonPushCounter == 0) {
    // MODE: All lights off
    Serial.println("IN ZERO");
    for (int i = 0; i <= NUM_LEDS - 1; i++) {
      leds[i] = CRGB (0, 0, 0);
      FastLED.show();
      delay(40);
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);

  } else if (buttonPushCounter == 1) {
    // MODE: Rotating colours back and forth across strip
    Serial.println("IN ONE");
    for (int i = 0; i <= NUM_LEDS - 1; i++) {
      leds[i] = CRGB (0, 255, 0);
      FastLED.show();
      delay(40);
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    if (buttonPushCounter == 1) {
      for (int i = NUM_LEDS - 1; i >= 0; i--) {
        leds[i] = CRGB (0, 0, 255);
        FastLED.show();
        delay(40);
      }
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    if (buttonPushCounter == 1) {
      for (int i = 0; i <= NUM_LEDS - 1; i++) {
        leds[i] = CRGB (255, 0, 0);
        FastLED.show();
        delay(40);
      }
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    if (buttonPushCounter == 1) {
      for (int i = NUM_LEDS - 1; i >= 0; i--) {
        leds[i] = CRGB (0, 255, 0);
        FastLED.show();
        delay(40);
      }
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    if (buttonPushCounter == 1) {
      for (int i = 0; i <= NUM_LEDS - 1; i++) {
        leds[i] = CRGB (0, 255, 255);
        FastLED.show();
        delay(40);
      }
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    if (buttonPushCounter == 1) {
      for (int i = NUM_LEDS - 1; i >= 0; i--) {
        leds[i] = CRGB (255, 255, 0);
        FastLED.show();
        delay(40);
      }
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    
  } else if (buttonPushCounter == 2) {
    // MODE: White lights starting from both ends of the LED strip come to center
    Serial.println("IN TWO");
    for (int i = 0; i <= (NUM_LEDS)/2 - 1; i++) {
      leds[i] = CRGB (100, 100, 100);
      leds[NUM_LEDS - i - 1] = CRGB (100, 100, 100);
      FastLED.show();
      delay(100);
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    if (buttonPushCounter == 2) {
      for (int i = 0; i <= (NUM_LEDS)/2 - 1; i++) {
        leds[i] = CRGB (0, 0, 0);
        leds[NUM_LEDS - i - 1] = CRGB (0, 0, 0);
        FastLED.show();
        delay(100);
      }
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    
  } else if (buttonPushCounter == 3) {
    // MODE: Four pretty colours move down the LED strips
    Serial.println("IN THREE");
    int del = 200;
    for (int i = 0; i <= NUM_LEDS - 1; i++) {
      if (i%4 == 0) {
        leds[i] = CRGB (100, 100, 100);        
      } else if (i%3 == 0) {
        leds[i] = CRGB (0, 100, 100);
      } else if (i%2 == 0) {
        leds[i] = CRGB (100, 0, 100);        
      } else {        
        leds[i] = CRGB (0, 0, 100);        
      }
    }
    FastLED.show();
    delay(del);
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    if (buttonPushCounter == 3) {
      for (int i = 0; i <= NUM_LEDS - 1; i++) {
        if (i%4 == 0) {
          leds[i] = CRGB (0, 0, 100);        
        } else if (i%3 == 0) {
          leds[i] = CRGB (100, 100, 100);        
        } else if (i%2 == 0) {
          leds[i] = CRGB (0, 100, 100);
        } else {        
          leds[i] = CRGB (100, 0, 100);        
        }
      }
      FastLED.show();
      delay(del);
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    if (buttonPushCounter == 3) {
      for (int i = 0; i <= NUM_LEDS - 1; i++) {
        if (i%4 == 0) {
          leds[i] = CRGB (100, 0, 100);        
        } else if (i%3 == 0) {
          leds[i] = CRGB (0, 0, 100);        
        } else if (i%2 == 0) {
          leds[i] = CRGB (100, 100, 100);        
        } else {        
          leds[i] = CRGB (0, 100, 100);
        }
      }
      FastLED.show();
      delay(del);
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    if (buttonPushCounter == 3) {
      for (int i = 0; i <= NUM_LEDS - 1; i++) {
        if (i%4 == 0) {
          leds[i] = CRGB (0, 100, 100);
        } else if (i%3 == 0) {
          leds[i] = CRGB (100, 0, 100);        
        } else if (i%2 == 0) {
          leds[i] = CRGB (0, 0, 100);        
        } else {        
          leds[i] = CRGB (100, 100, 100);        
        }
      }
      FastLED.show();
      delay(del);
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    
  } else if (buttonPushCounter == 4) {
    // MODE: Randomly change LEDs to rotating colours
    Serial.println("IN FOUR");
    int incR = 5;
    int incG = 7;
    int incB = 3;
    for (int i = 0; i <= NUM_LEDS - 1; i++) {
      int randNum = random(5);
      Serial.print("rand: ");
      Serial.println(randNum);
      if (randNum == 0) {
        leds[i] = CRGB (r, g, 0);
        FastLED.show();
        delay(40);
        if (r < 255 - incR) {
          r = r + incR;
        } else {
          r = 0;
        }
        if (g < 255 - incG) {
          g = g + incG;
        } else {
          g = 0;
        }
        if (b < 255 - incB) {
          b = b + incB;
        } else {
          b = 0;
        }
      }
    }
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    if (buttonPushCounter == 4) {
      for (int i = NUM_LEDS - 1; i >= 0; i--) {      
        int randNum = random(5);
        Serial.print("rand: ");
        Serial.println(randNum);
        if (randNum == 0) {
          leds[i] = CRGB (r, g, 0);
          FastLED.show();
          delay(40);
          if (r < 255 - incR) {
            r = r + incR;
          } else {
            r = 0;
          }
          if (g < 255 - incG) {
            g = g + incG;
          } else {
            g = 0;
          }
          if (b < 255 - incB) {
            b = b + incB;
          } else {
            b = 0;
          }
        }
      }
      buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
    }
    
  } else {
    Serial.println("NOT IN A CORRECT MODE.");
    buttonPushCounter = checkForCounterIncrement(buttonPushCounter);
  }
}

int checkForCounterIncrement(int currCounter) {
  buttonState = digitalRead(BUTTON_PIN);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:

      if (currCounter >= NUM_MODES) {
        currCounter = 0;
      } else if (currCounter < 0) {
        currCounter = 0;
      } else {
        currCounter += 1;
      }
    } 
    // else {
    // if the current state is LOW then the button went from on to off:
    //}
    
    // Delay a little bit to avoid bouncing
    delay(40);
  }
  
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
  Serial.print("after checking button, currCounter: ");
  Serial.println(currCounter);
  return currCounter;
}
