/*
 * USB Keyboard using Teensy
 *   - Select USB Type as Keyboard
 *   - Media keys
 *   
 *   R1: |<<    >||    >>|
 *   R2: Mute   V+     V-
 *   
 * Author: Zihan Chen
 * Date: March 07, 2019
 */

#include <Bounce2.h>

#define LED_PIN 12

struct BounceButton {
  Bounce btn;
  unsigned long fellTime;
  unsigned long roseTime;
};

// Create Bounce objects for each button.
BounceButton buttons [10];

void checkKeyPress(Bounce& b, int key)
{
  if (b.fell()) {
    Keyboard.press(key);
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  } else if (b.rose()) {
    Keyboard.release(key);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }
}

void checkKeyPressModifier(Bounce& b, int key, int mod)
{
  if (b.fell()) {
    Keyboard.set_modifier(mod);
    Keyboard.set_key1(key);
    Keyboard.send_now();
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  } else if (b.rose()) {
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }
}

void setup() {
  for (int i = 0; i < 10; i++) {
    buttons[i].btn.attach(i, INPUT_PULLUP);
    buttons[i].fellTime = millis();
    buttons[i].roseTime = millis();
  }
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  // Update all buttons
  for (int i = 0; i < 10; i++) {
    buttons[i].btn.update();
    if (buttons[i].btn.fell()) {buttons[i].fellTime = millis();}
    if (buttons[i].btn.rose()) {buttons[i].roseTime = millis();}
  }

  checkKeyPress(buttons[0].btn, KEY_MEDIA_PREV_TRACK);
  checkKeyPress(buttons[1].btn, KEY_MEDIA_PLAY_PAUSE);
  checkKeyPress(buttons[2].btn, KEY_MEDIA_NEXT_TRACK);

  checkKeyPress(buttons[3].btn, KEY_MEDIA_MUTE);
  checkKeyPress(buttons[4].btn, KEY_MEDIA_VOLUME_DEC);
  checkKeyPress(buttons[5].btn, KEY_MEDIA_VOLUME_INC);

  // Example: How to use Modifier keys
  // checkKeyPressModifier(buttons[0].btn, KEY_J, MODIFIERKEY_CTRL | MODIFIERKEY_ALT);
}
