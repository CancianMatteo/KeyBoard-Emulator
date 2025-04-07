#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard(LAYOUT_IT);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Keyboard.begin();
  USB.begin();
  delay(700);
  delay(300);

  digitalWrite(LED_BUILTIN, HIGH);
  // Press Ctrl+ALt+Canc
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_DELETE);
  delay(100);
  Keyboard.releaseAll();
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);

  digitalWrite(LED_BUILTIN, HIGH);
  // Type the email address
  Keyboard.print("example@email.com\t");
  delay(100);
  // Type the pwd
  Keyboard.print("YourStrongPassword!\n");
  delay(500);
  // Erase all
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('a');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_DELETE);
  delay(100);
  Keyboard.releaseAll();
  digitalWrite(LED_BUILTIN, LOW);

  // Login...
  delay(10000);
  
  digitalWrite(LED_BUILTIN, HIGH);
  // Cmd > gpupdate /force
  Keyboard.print("\tprompt\n");
  delay(2000);
  Keyboard.print("gpupdate /force\n");
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}