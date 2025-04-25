#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Keyboard.setLayout(it_it);
  Keyboard.begin();
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH);
  // Press Ctrl+ALt+Canc
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_DELETE);
  delay(200);
  Keyboard.releaseAll();
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);

  digitalWrite(LED_BUILTIN, HIGH);
  // Type the email address
  Keyboard.print("example@email.com\t");
  delay(1000);
  // Type the pwd
  Keyboard.println("strongPassword");
  delay(200);
  // Erase all
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('a');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_DELETE);
  delay(100);
  Keyboard.releaseAll();
  digitalWrite(LED_BUILTIN, LOW);
  delay(15000);   // Login...

  digitalWrite(LED_BUILTIN, HIGH);
  // Open Word
  Keyboard.press(KEY_LEFT_GUI); // Windows key
  Keyboard.press('s');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print("word");
  delay(1000);
  Keyboard.print("\n");
  delay(4000);   // Opening Word...
  Keyboard.print("\n");
  digitalWrite(LED_BUILTIN, LOW);
  delay(10000);   // Check printer...
  
  digitalWrite(LED_BUILTIN, HIGH);
  // Cmd > gpupdate /force (update working group policy)
  Keyboard.press(KEY_LEFT_GUI); // Windows key
  Keyboard.press('s');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.print("prompt");
  delay(1000);
  Keyboard.print("\n");
  delay(4000);
  Keyboard.println("gpupdate /force");
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // IDLE: Blink the built-in LED
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}