// ATtiny412
#include <megaTinyCore.h>
//#include <SoftwareSerial.h>
#include <SendOnlySoftwareSerial.h>
//#include <AdvancedPID.h>
//#include <ArduPID.h>
#include <PID.h>

#define MOTOR_PWM1_PIN PIN_PA7
#define MOTOR_PWM2_PIN PIN_PA1
#define MOTOR_IPROPI_PIN PIN_PA2
#define POTI_POS_PIN PIN_PA6
#define PWM_IN_PIN PIN_PA3
//DO NOT USE UPDI PA0

double setpoint = 512;
double input;
double output;

//int input = 0;
//int output = 0;
//SendOnlySoftwareSerial serial (PWM_IN_PIN);

arc::PID<double> pid(0.3,0.2,0.0);

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

  //

}

void loop() {
  input = adcAvg(POTI_POS_PIN, 50);
  //setpoint = 512.0; // Target value
  pid.setTarget(512);
  if (input != 2000)
  {
    pid.setInput(input);
    driveMotor(pid.getOutput());
  }
  else
  {
    driveMotor(0);
  }

  
  
  //delay(2);
  
}

void driveMotor(int val)
{
  if(val == 0)
  {
    analogWrite(MOTOR_PWM1_PIN, 255);
    analogWrite(MOTOR_PWM2_PIN, 255);
  }
  else if (val > 0)
  {
    analogWrite(MOTOR_PWM1_PIN, (val)+5);
    analogWrite(MOTOR_PWM2_PIN, 0);
  }
  else
  {
    analogWrite(MOTOR_PWM2_PIN, (-val)+5);
    analogWrite(MOTOR_PWM1_PIN, 0);
  }
}

/*void target(uint16_t target)
{
  uint16_t pos = adcAvg(POTI_POS_PIN, 50);
  Serial.println(pos);
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

  serial.print("Pos: ");
  serial.print(pos);
  serial.print(" Curr: ");
  serial.println(adcAvg(MOTOR_IPROPI_PIN, 100)*3);
}*/

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

  if (stdDev > 20) avg = 2000;
  return avg;
}
