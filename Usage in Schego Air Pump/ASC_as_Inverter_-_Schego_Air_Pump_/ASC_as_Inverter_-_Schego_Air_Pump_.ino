#include <megaTinyCore.h>

#define MOTOR_PWM1_PIN PIN_PA7
#define MOTOR_PWM2_PIN PIN_PA1
#define MOTOR_IPROPI_PIN PIN_PA2
#define POTI_POS_PIN PIN_PA6
#define PWM_IN_PIN PIN_PA3
//DO NOT USE UPDI PA0

//Rect Wave
#define freqency  45
#define power  0.8

int input = 0;

void setup() {
  pinMode(MOTOR_PWM1_PIN, OUTPUT);
  pinMode(MOTOR_PWM2_PIN, OUTPUT);
  //analogWriteFreq(200000);
  pinMode(MOTOR_IPROPI_PIN, INPUT);
  analogReference(VDD); //INTERNAL2V5
  
  digitalWrite(MOTOR_PWM1_PIN, LOW);
  digitalWrite(MOTOR_PWM2_PIN, LOW);

}

void loop() {

  analogWrite(MOTOR_PWM1_PIN, 255);
  analogWrite(MOTOR_PWM2_PIN, 0);
  delayMicroseconds((1000000/freqency)/2*power);
  analogWrite(MOTOR_PWM1_PIN, 0);
  analogWrite(MOTOR_PWM2_PIN, 0);
  delayMicroseconds((1000000/freqency)/2*(1-power));
  analogWrite(MOTOR_PWM1_PIN, 0);
  analogWrite(MOTOR_PWM2_PIN, 255);
  delayMicroseconds((1000000/freqency)/2*power);
  analogWrite(MOTOR_PWM1_PIN, 0);
  analogWrite(MOTOR_PWM2_PIN, 0);
  delayMicroseconds((1000000/freqency)/2*(1-power));
}
