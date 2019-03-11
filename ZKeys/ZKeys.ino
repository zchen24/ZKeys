/*
 * USB Keyboard using Teensy
 *   - Select USB Type as Keyboard
 *   - Media keys
 *   
 * Author: Zihan Chen
 * Date: March 07, 2019
 */

#include <Bounce2.h>


// Create Bounce objects for each button.
Bounce button0;
Bounce button1;
Bounce button2;
Bounce button3;
Bounce button4;
Bounce button5;
Bounce button6;
Bounce button7;
Bounce button8;
Bounce button9;
Bounce button10;

bool ledState = LOW;

void checkKeyPress(Bounce& b, int key)
{
  b.update();
  if (b.fallingEdge()) {
    Keyboard.press(key);
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (b.risingEdge()) {
    Keyboard.release(key);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void checkKeyPressModifier(Bounce& b, int key, int mod)
{
  b.update();
  if (b.fallingEdge()) {
    Keyboard.set_modifier(mod);
    Keyboard.set_key1(key);
    Keyboard.send_now();
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (b.risingEdge()) {
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup() {
  button0.attach(0, INPUT_PULLUP);
  button1.attach(1, INPUT_PULLUP);
  button2.attach(2, INPUT_PULLUP);
  button3.attach(3, INPUT_PULLUP);
  button4.attach(4, INPUT_PULLUP);
  button5.attach(5, INPUT_PULLUP);
  button6.attach(6, INPUT_PULLUP);
  button7.attach(7, INPUT_PULLUP);
  button8.attach(8, INPUT_PULLUP);
  button9.attach(9, INPUT_PULLUP);
  button10.attach(10, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  // Update all buttons
  checkKeyPressModifier(button0, KEY_J, MODIFIERKEY_CTRL | MODIFIERKEY_ALT);
  checkKeyPressModifier(button1, KEY_P, MODIFIERKEY_CTRL | MODIFIERKEY_ALT);
  checkKeyPressModifier(button2, KEY_K, MODIFIERKEY_CTRL | MODIFIERKEY_ALT);
  checkKeyPress(button3, KEY_MEDIA_MUTE);
  checkKeyPress(button4, KEY_MEDIA_VOLUME_DEC);
  checkKeyPress(button5, KEY_MEDIA_VOLUME_INC);
}
