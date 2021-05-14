#include <Servo.h>
Servo myservo;

const int button1 = 7; // first button is on pin 7
const int button2 = 6; // second is on pin 6
const int button3 = 5; // third is pin 5
const int button4 = 4; // fourth is pin 4
const int button5 = 3; // code reset button
const int speaker = 11; // Piezo
const int pingPin = A0; // ultrasonic trigger pin
const int echoPin = 10; // ultrasonic echo input pin
const int tiltSwitch = 2; // tilt switch
const int depth = A5; // depth sensor
const int joyX = A1; // joystick X-axis, if I get around to implementing it.
const int joyY = A2; // joystick Y-axis
const int Red = 9; // red LED is on pin 8
const int greenLed = 8; // green LED is pin 9

int code[] = {1, 2, 3, 4, 3, 2}; // The password, in the order you want it input. Set zeroes if you want to enter your own password.
int entered[6]; // The array to store input pattern

void setup() {
  myservo.attach(12); // Servo opens the door.
  pinMode(button1, INPUT_PULLUP); // buttons 1-4
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(Red, OUTPUT); // RGB LED components. Blue is not used.
  pinMode(greenLed, OUTPUT);
  pinMode(pingPin, OUTPUT); // Ultrasonic distance sensor
  pinMode(echoPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(tiltSwitch), tilted, CHANGE); // attaches interrupts to tilt switch, so it works no matter what.
  myservo.write(12); // set servos to the closed position
  delay(500);
  Serial.begin(9600); // for debugging.
}

void loop() { // watch for inputs from buttons and depth sensor
  while (analogRead(depth) > 100) { // box won't function if the depth sensor detects water
    delay(75);
  }
  if (digitalRead(button1) == LOW) { // if button 1 is pressed
    Serial.println("one"); // all serial calls are debugging and aren't necessary
    tone(speaker, 1500, 100);
    checkEntered1(1); // call checkEntered1 and pass it a 1
    delay(200); // prevents repeated presses
  }
  else if (digitalRead(button2) == LOW) { // if button 2 is pressed
    Serial.println("Two");
    tone(speaker, 2000, 100);
    checkEntered1(2); // call checkEntered1 and pass it a 2
    delay(200); // wait
  }
  else if (digitalRead(button3) == LOW) { // if button 3 is pressed
    Serial.println("Three");
    tone(speaker, 3000, 100);
    checkEntered1(3); // call checkEntered1 and pass it a 3
    delay(200); // wait
  }
  else if (digitalRead(button4) == LOW) { // if button 4 is pressed
    Serial.println("Four");
    tone(speaker, 4000, 100);
    checkEntered1(4); // call checkEntered1 and pass it a 4
    delay(200); // wait
  }
  else if (digitalRead(button5) == LOW) { // if the reset passcode button is pressed.
    for (int i = 0; i < 6; i++) {
      code[i] = 0;
    }
  }
}

void checkEntered1(int button) { // check the first element of the entered[] array
  digitalWrite(Red, HIGH); // flash the RGB LED orange when a button is pressed.
  digitalWrite(greenLed, HIGH);
  delay(50);
  digitalWrite(Red, LOW);
  digitalWrite(greenLed, LOW);
  if (entered[0] != 0) { // if it is not a zero, i.e. it has already been input
    checkEntered2(button); // move on to checkEntered2, passing it "button"
  }
  else if (entered[0] == 0) { // if it is zero, i.e. if it hasn't been defined with a button yet
    entered[0] = button; // set the first element as the button that has been pressed
  }
  if (code[0] == 0) { // if you want to enter your own password.
    code[0] = button;
  }
}

void checkEntered2(int button) { // check the second element of entered[]
  if (entered[1] != 0) { // if it is not a zero, i.e. it has already been input
    checkEntered3(button); // move on to checkEntered3, passing it "button"
  }
  else if (entered[1] == 0) { // if it is zero, i.e. if it hasn't been defined with a button yet
    entered[1] = button; // set the second element as the button that has been pressed
  }
  if (code[1] == 0) { // if you want to enter your own code
    code[1] = button;
  }
}

void checkEntered3(int button) { // check the third element of the entered[] array

  if (entered[2] != 0) { // if it is not a zero, i.e. it has already been input
    checkEntered4(button); // move on to checkEntered4, passing it "button"
  }

  else if (entered[2] == 0) { // if it is zero, i.e. if it hasn't been defined with a button yet
    entered[2] = button; // set the third element as the button that has been pressed
  }
  if (code[2] == 0) { // if you want to enter your own code
    code[2] = button;
  }
}

void checkEntered4(int button) { // check the fourth element of the entered[] array

  if (entered[3] != 0) { // if it is not a zero, i.e. it has already been input
    checkEntered5(button); // move on to checkEntered5, passing it "button"
  }
  else if (entered[3] == 0) { // if it is zero, i.e. if it hasn't been defined with a button yet
    entered[3] = button; // set the fourth element as the button that has been pressed
  }
  if (code[3] == 0) { // if you want to enter your own code
    code[3] = button;
  }
}
void checkEntered5(int button) { // check the fifth element of the entered[] array
  if (entered[4] != 0) { // if it is not a zero, i.e. it has already been input
    checkEntered6(button); // move on to checkEntered6, passing it "button"
  }
  else if (entered[4] == 0) { // if it is zero, i.e. if it hasn't been defined with a button yet
    entered[4] = button; // set the fifth element as the button that has been pressed
  }
  if (code[4] == 0) { // if you want to enter your own code
    code[4] = button;
  }
}

void checkEntered6(int button) { // check the sixth element of the entered[] array
  entered[5] = button; // set the final element as the button that has been pressed
  if (code[5] == 0) { // if you want to enter your own code
    code[5] = button;
  }
  delay(150);
  compareCode(); // check the input code
}

void compareCode() { // checks if the code entered is correct
  int flag = 0;
  for (int i = 0; i < 6; i++) {
    if (entered[i] != code[i]) {
      flag = 1;
    }
  }
  if (flag == 1) { // incorrect password
    noBox();
  }
  else { // correct password entered
    openBox();
    flag = 0;
  }
}
void correctSound() { // when the password is correct, a sound is played.
  tone(speaker, 5000, 150);
  delay(300);
  tone(speaker, 5000, 150);
  delay(300);
  tone(speaker, 5000, 150);
  delay(300);
}
long getDist() { // use the ultrasonic sensor
  long duration; // time between pulse sent & received
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration / 74 / 2; // Ultrasonic reading converted to inches and returned.
}
void tilted() { // method called when the interrupt is switched (tilt switch turns off)
  while (digitalRead(tiltSwitch) != HIGH) {
    delay(150); // Delay doesn't work in interrupt functions, this is just to have something in the loop.
  }
}
void openBox() {
  digitalWrite(greenLed, HIGH); // turn the green LED on
  correctSound(); // play the correct sound
  myservo.write(170); // open the box
  delay(1500);
  digitalWrite(greenLed, LOW); // turn the green LED off
  while (getDist() > 3) { // box will stay open until you place your hand near the ultrasonic sensor.
    delay(100);
  }
  myservo.write(5); // close the box
  delay(1000);
  for (int i = 0; i < 6; i++) { // reset all values to zero
    entered[i] = 0;
  }
}
void noBox() { // password is incorrect. Box doesn't open
  digitalWrite(Red, HIGH);
  delay(1000);
  digitalWrite(Red, LOW);
  badSound();
  for (int i = 0; i < 6; i++) { // reset all values to zero
    entered[i] = 0;
  }
}
void badSound() { // sound that plays when the incorrect password is input.
  tone(speaker, 2500, 150);
  delay(300);
  tone(speaker, 2500, 150);
  delay(300);
  tone(speaker, 2500, 150);
  delay(300);
}
