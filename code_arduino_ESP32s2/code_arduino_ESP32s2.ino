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
  delay(100);
  Keyboard.releaseAll();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH);
  // Type the email address
  Keyboard.print("example@email.it\t");
  delay(500);
  // Type the pwd
  Keyboard.println("StrongPassword!");
  delay(100);
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
  Keyboard.println("word");
  delay(5000);   // Opening Word
  Keyboard.print("\n");
  digitalWrite(LED_BUILTIN, LOW);
  delay(10000);   // Check printer...
  
  digitalWrite(LED_BUILTIN, HIGH);
  // Cmd > gpupdate /force (update working group policy)
  Keyboard.press(KEY_LEFT_GUI); // Windows key
  Keyboard.press('s');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.println("prompt");
  delay(1000);
  Keyboard.println("gpupdate /force");
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}