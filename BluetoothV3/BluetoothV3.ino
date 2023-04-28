#include <LCD_1602_RUS.h>
#include <Stepper.h>
#include <NewPing.h>
#include <Wire.h>
String msg, cmd;
LCD_1602_RUS lcd(0x27, 20 , 21); // LCD 16x2

#define TRIGGER_PIN_R 39 //ESR
#define ECHO_PIN_R 41 //ESR

#define TRIGGER_PIN_L 43 //ESL
#define ECHO_PIN_L 45

#define MAX_DISTANCE 200

NewPing sonar_R(TRIGGER_PIN_R, ECHO_PIN_R, MAX_DISTANCE);

NewPing sonar_L(TRIGGER_PIN_L, ECHO_PIN_L, MAX_DISTANCE);
const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 4, 5, 6, 7); //MD module
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  myStepper.setSpeed(40);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600); // Communication rate of the Bluetooth Module
  msg = "";
}

void loop() {

  // To read message received from other Bluetooth Device
  if (Serial.available() > 0) { // Check if there is data coming
    msg = Serial.readString(); // Read the message as String
    Serial.println("Android Command: " + msg);
  }

  // Control LED in Arduino board
  if (msg == "<go left>") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ИДУ НАЛЕВО");
    // Turn on LED
    myStepper.step(-200);
    Serial.println("Goind to the left\n"); // Then send status message to Android
    msg = ""; // reset command
  }
  else if (msg == "<go right>") {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ИДУ НАПРАВО");
    myStepper.step(200);
    Serial.println("Going to the right\n"); // Then send status message to Android
    msg = ""; // reset command
  }

  else if (msg == "<go corner right>") {
    unsigned int ESR = sonar_R.ping_cm();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ИДУ НАПРАВО");
    Serial.println("Goind to the right\n");
    while (ESR > 5 or ESR == 0) {
      msg = "";
      unsigned int ESR = sonar_R.ping_cm();
      Serial.print("ESR");
      Serial.println(ESR);
      
      myStepper.step(10);
      if (Serial.available() > 0) { // Check if there is data coming
        msg = Serial.readString(); // Read the message as String
        Serial.println("Android Command: " + msg);
      }
      if (msg == "<stop>") {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        msg = "";
        break;
      }
      if (ESR < 5 and ESR != 0) {
        msg = "";
        break;
      }
    }
    // reset command
  }

  else if (msg == "<go corner left>") {
    unsigned int ESL = sonar_L.ping_cm();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ИДУ НАЛЕВО");
    Serial.println("Going to the left\n");
    while (ESL > 5 or ESL == 0) {
      msg = "";
      unsigned int ESL = sonar_L.ping_cm();
      Serial.print("ESL");
      Serial.println(ESL);
      myStepper.step(-10);
      if (Serial.available() > 0) { // Check if there is data coming
        msg = Serial.readString(); // Read the message as String
        Serial.println("Android Command: " + msg);
      }
      if (msg == "<stop>") {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        msg = "";
        break;
      }
      if (ESL < 5 and ESL != 0) {
        msg = "";
        break;
      }
    }
    // reset command
  }
}
