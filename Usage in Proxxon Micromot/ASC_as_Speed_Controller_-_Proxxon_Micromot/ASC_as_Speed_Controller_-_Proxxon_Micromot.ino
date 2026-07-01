// ATtiny412

#include <megaTinyCore.h>

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

unsigned int Period   = 0x3FF; //10bit for higher frequency (20000000/2^10 = 19,5kHz)

void setup() {
  pinMode(MOTOR_PWM1_PIN, OUTPUT);
  pinMode(MOTOR_PWM2_PIN, OUTPUT);
  //analogWriteFreq(200000);
  pinMode(MOTOR_IPROPI_PIN, INPUT);
  analogReference(VDD); //INTERNAL2V5

  digitalWrite(MOTOR_PWM1_PIN, LOW);
  digitalWrite(MOTOR_PWM2_PIN, LOW);

  /*#if defined MEGATINYCORE
  #if defined PORTMUX_TCAROUTEA
  PORTMUX.TCAROUTEA   &= 1 << 1;
  #elif defined PORTMUX_CTRLC
  PORTMUX.CTRLC   &= 1 << 1;
  #endif
  #else
  PORTMUX.TCAROUTEA = (PORTMUX.TCAROUTEA & ~(PORTMUX_TCA0_gm)) | PORTMUX_TCA0_PORTC_gc;
  #endif*/
  takeOverTCA0();                             // This replaces disabling and resettng the timer, required previously.
  TCA0.SINGLE.CTRLB   = (TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc); //CMP1 = WO1 = PA1
                                              // Single slope PWM mode
  TCA0.SINGLE.PER     = Period;               // Count all the way up to 0xFFFF
  TCA0.SINGLE.CMP1    = 0;                    // At 20MHz, this gives ~305Hz PWM
  TCA0.SINGLE.CTRLA   = TCA_SINGLE_ENABLE_bm; // Enable the timer with no prescaler

  //setFrequency(2000);
}

void loop() {
  input = input * 0.9 + analogRead(POTI_POS_PIN) * 0.1; //LOW Pass

  int targetSpeed = map(input, 0, 1024, Period/3, Period);       //Mapping
  //int motorCurrent = adcAvg(MOTOR_IPROPI_PIN, 30)*3;
  //motorCurr = motorCurr * 0.9 + motorCurrent * 0.1;

  //float outVoltage = (targetSpeed / MOTOR_K) + ((float)motorCurrent/1000) * MOTOR_Ri;
  //float normCurr = targetSpeed * (300/255);
  //int outPwm = targetSpeed + (motorCurr - normCurr);

  //analogWrite(MOTOR_PWM2_PIN, targetSpeed);             //Output
  TCA0.SINGLE.CMP1 = targetSpeed;
  //setDutyCycle(targetSpeed);             //Output
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

  int64_t stdDev = 0;
  for(int i = 0; i<count; i++)
  {
    stdDev += abs(avg - ringSpeicher[i]);
  }

  //if (stdDev > 40) avg = 0;
  return avg;
}
/*
void setDutyCycle(byte duty) {
  TCA0.SINGLE.CMP1 = map(duty, 0, 255, 0, Period);
}

void setFrequency(unsigned long freqInHz) {
  unsigned long tempperiod = (F_CPU / freqInHz);
  byte presc = 0;
  while (tempperiod > 65536 && presc < 7) {
    presc++;
    tempperiod = tempperiod >> (presc > 4 ? 2 : 1);
  }
  Period = tempperiod;
  TCA0.SINGLE.CTRLA = (presc << 1) | TCA_SINGLE_ENABLE_bm;
  TCA0.SINGLE.PER = Period;
}
*/
