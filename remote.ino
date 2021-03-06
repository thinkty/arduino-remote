// IR
// LG has data bits similar to NEC but in reverse (Most Significant Bit first)
#define IR_SEND_PIN 8
#include <IRremote.h>
IRData IRSendData;

// Joystick
#define JOY_X A0
#define JOY_Y A1
enum dir { CENTER = -1, UP = 0x20DF02FD, DOWN = 0x20DF827D, LEFT = 0x20DFE01F, RIGHT = 0x20DF609F };
dir current;

// Power Button
#define POWER_BUTTON 3
#define POWER_CMD 0x20DF10EF

// Settings Button
#define SETTINGS_BUTTON 4
#define SETTINGS_CMD 0x20DFC23D

// Confirm Button
#define CONFIRM_BUTTON 5
#define CONFIRM_CMD 0x20DF22DD

// Function to read the direction of the joystick based on x and y values
void readJoystick() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  dir temp = NULL;
  // The module is in 10 bit for x and y
  if (x < 600 && x > 400 && y == 0) {
    temp = LEFT;
  }
  if (x < 600 && x > 400 && y == 1023) {
    temp = RIGHT;
  }
  if (x == 0 && y < 600 && y > 400) {
    temp = DOWN;
  }
  if (x == 1023 && y < 600 && y > 400) {
    temp = UP;
  }
  if (x < 600 && x > 400 && y < 600 && y > 400) {
    temp = CENTER;
  }

  // Only update value when change has occurred
  if (temp && temp != current) {
    current = temp;
    
    // Send all signals except for center as center is default
    // This allows sending the same signal in sequence
    if (current != CENTER) {
      IrSender.sendNECMSB(current, 32, false);
      delay(110);
    }
  }
}

// Function to read from multiple (power, settings, confirm) push-buttons
void readPushButton() {
  if (digitalRead(POWER_BUTTON) == HIGH) {
    IrSender.sendNECMSB(POWER_CMD, 32, false);
    delay(110);
  }

  if (digitalRead(SETTINGS_BUTTON) == HIGH) {
    IrSender.sendNECMSB(SETTINGS_CMD, 32, false);
    delay(110);
  }

  if (digitalRead(CONFIRM_BUTTON) == HIGH) {
    IrSender.sendNECMSB(CONFIRM_CMD, 32, false);
    delay(110);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(POWER_BUTTON, INPUT);
  pinMode(CONFIRM_BUTTON, INPUT);
  pinMode(SETTINGS_BUTTON, INPUT);
  IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);
  delay(1000);
}

void loop() {
  // Joystick input
  readJoystick();

  // PushButton input
  readPushButton();
}
