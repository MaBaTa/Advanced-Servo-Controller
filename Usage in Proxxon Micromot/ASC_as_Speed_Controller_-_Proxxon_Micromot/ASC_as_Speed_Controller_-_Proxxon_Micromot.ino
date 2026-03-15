// ATtiny412
#include <megaTinyCore.h>
//#include <SoftwareSerial.h>
#include <SendOnlySoftwareSerial.h>

#define MOTOR_PWM1_PIN PIN_PA7
#define MOTOR_PWM2_PIN PIN_PA1
#define MOTOR_IPROPI_PIN PIN_PA2
#define POTI_POS_PIN PIN_PA6
#define PWM_IN_PIN PIN_PA3
//DO NOT USE UPDI PA0

#define MOTOR_K  1667 //20000RPM at 12V
#define MOTOR_Ri 40    //winding Resistance

#define RINGGROESSE 100

int input = 0;
int output = 0;
//SendOnlySoftwareSerial serial (PWM_IN_PIN);

void setup() {
  pinMode(MOTOR_PWM1_PIN, OUTPUT);
  pinMode(MOTOR_PWM2_PIN, OUTPUT);
  //analogWriteFreq(200000);
  pinMode(MOTOR_IPROPI_PIN, INPUT);
  analogReference(VDD); //INTERNAL2V5
  
  //serial.begin(9600);

  digitalWrite(MOTOR_PWM1_PIN, LOW);
  digitalWrite(MOTOR_PWM2_PIN, LOW);

  //serial.println("= ASC Boot =");

}

void loop() {
  input = input * 0.9 + analogRead(POTI_POS_PIN) * 0.1; //LOW Pass

  int targetSpeed = map(input, 0, 1024, 25, 255);       //Mapping
  //int motorCurrent = adcAvg(MOTOR_IPROPI_PIN, 30)*3;
  //motorCurr = motorCurr * 0.9 + motorCurrent * 0.1;

  //float outVoltage = (targetSpeed / MOTOR_K) + ((float)motorCurrent/1000) * MOTOR_Ri;
  //float normCurr = targetSpeed * (300/255);
  //int outPwm = targetSpeed + (motorCurr - normCurr);

  analogWrite(MOTOR_PWM2_PIN, targetSpeed);             //Output
  //analogWrite(MOTOR_PWM2_PIN, map(adcAvg(POTI_POS_PIN, 50), 0, 1024, 25, 255));
  
  delay(1);
}



uint16_t adcAvg(uint8_t pin, uint8_t count)
{
  uint16_t ringSpeicher[count] = {0};
  //uint16_t ringPos = 0;
  for(int i = 0; i<count; i++)
  {
    ringSpeicher[i] = analogRead(pin);
    delayMicroseconds(20);
  }
  
  float avg = 0;
  for(int i = 0; i<count; i++)
  {
    avg += (float)ringSpeicher[i] / count;
  }
  //serial.print("AVG: ");
  //serial.print(avg);

  int64_t stdDev = 0;
  for(int i = 0; i<count; i++)
  {
    stdDev += abs(avg - ringSpeicher[i]);
  }
  //serial.print(" stdDev: ");
  //serial.println((int16_t)stdDev);

  //if (stdDev > 40) avg = 0;
  return avg;
}
