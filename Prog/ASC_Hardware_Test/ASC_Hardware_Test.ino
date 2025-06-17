#include <megaTinyCore.h>

#define MOTOR_PWM1_PIN PIN_PA7
#define MOTOR_PWM2_PIN PIN_PA1
#define MOTOR_IPROPI_PIN PIN_PA2
#define POTI_POS_PIN PIN_PA6
#define PWM_IN_PIN PIN_PA3
//DO NOT USE UPDI PA0

//3,3V Signal
//#define factor  1.68
//5V Signal
#define factor  2.55

int input = 0;

void setup() {
  pinMode(MOTOR_PWM1_PIN, OUTPUT);
  pinMode(MOTOR_PWM2_PIN, OUTPUT);
  //analogWriteFreq(200000);
  pinMode(MOTOR_IPROPI_PIN, INPUT);
  analogReference(VDD); //INTERNAL2V5
  
  Serial.begin(9600);

  //analogWrite(FAN_PWM_PIN, 100*1.68);
  //analogWrite(FAN_PWM_PIN, pwm);

  digitalWrite(MOTOR_PWM1_PIN, LOW);
  digitalWrite(MOTOR_PWM2_PIN, LOW);

  Serial.println("Type in a Number between 0 - 100:");

}

void loop() {
  /*if(Serial.available()>0)
  {
    input = 0;
    while(Serial.available()>0)
    {
      char a = Serial.read();
      if (a >= '0' && a <= '9')
      {
        input = (input * 10) + a - '0';
      }
      delay(10);
    }
    Serial.print("Input: ");
    Serial.println(input);
    //input -= 100;
    if (input > 100)
    {
      //pwm(MOTOR_PWM2_PIN, 500, 0);
      //pwm(MOTOR_PWM1_PIN, 500, (input-100)*11);
      //analogWrite(MOTOR_PWM1_PIN, (input-100)*11);
      digitalWrite(MOTOR_PWM1_PIN, HIGH);
    }
    else if (input < 100)
    {
      //pwm(MOTOR_PWM1_PIN, 500, 0);
      //pwm(MOTOR_PWM2_PIN, 500, (100-input)*11);
    }
    else
    {
      //pwm(MOTOR_PWM1_PIN, 500, 1024);
      //pwm(MOTOR_PWM2_PIN, 500, 1024);
    }
    
  }*/
  Serial.print("Current: ");
  Serial.println(analogRead(MOTOR_IPROPI_PIN));
  delay(500);
  for(int i = 0; i<255; i++)
  {
    analogWrite(MOTOR_PWM1_PIN, i);
    delay(10);
  }
  delay(500);
  analogWrite(MOTOR_PWM1_PIN, 255);
  analogWrite(MOTOR_PWM2_PIN, 255);
  delay(500);

  analogWrite(MOTOR_PWM1_PIN, 0);
  delay(200);
    
  //delay(5000);
  for(int i = 0; i<255; i++)
  {
    analogWrite(MOTOR_PWM2_PIN, 255-i);
    delay(10);
  }

  while(true) target(900);
  
}

void target(uint16_t target)
{
  uint16_t pos = analogRead(POTI_POS_PIN);
  if(pos > target + 5)
  {
    analogWrite(MOTOR_PWM1_PIN, ((pos - target) /2) + 40);
    analogWrite(MOTOR_PWM2_PIN, 0);
  }
  else if(pos < target - 5)
  {
    analogWrite(MOTOR_PWM2_PIN, ((target - pos) /2) + 40);
    analogWrite(MOTOR_PWM1_PIN, 0);
  }
  else
  {
    analogWrite(MOTOR_PWM1_PIN, 255);
    analogWrite(MOTOR_PWM2_PIN, 255);
  }
}
