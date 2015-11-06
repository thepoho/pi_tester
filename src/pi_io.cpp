#include "pi_io.h"
#include <stdio.h>
#include <stdlib.h>

PiIO::PiIO()
{

}
PiIO::~PiIO()
{

}

#ifdef BUILD_RASPI
#include <wiringPi.h>
void PiIO::startup()
{
  if (wiringPiSetup() == -1)
    exit(0);
}

void PiIO::setPinMode(int pin, int mode)
{
  pinMode(pin, mode);
}

void PiIO::pinWrite(int pin, int value)
{
  digitalWrite(pin, value);
}

int PiIO::pinRead(int pin)
{
  return(digitalRead(pin));
}

void PiIO::flushSerialData()
{
  // cout << "TODO" << endl;
  // if(serialOutputsDirty){
    // digitalWrite(SERIAL_LATCH_PIN, LOW);
    
    // digitalWrite(SERIAL_CLOCK_PIN, LOW);
    // for (int i = 0; i < SIZEOF(currentSerialState); i++){
    //   digitalWrite(SERIAL_DATA_PIN, currentSerialState[i]);
    //   digitalWrite(SERIAL_CLOCK_PIN, HIGH);
    //   digitalWrite(SERIAL_CLOCK_PIN, LOW);
    // }
    // digitalWrite(SERIAL_LATCH_PIN, HIGH);
  // }
}

void PiIO::doDelay(unsigned int howLong)
{
  delay(howLong);
}

unsigned int PiIO::getMillis(void)
{
  return(millis());
}
#else
void PiIO::startup(){}
void PiIO::setPinMode(int pin, int mode){}
void PiIO::pinWrite(int pin, int value){}
int  PiIO::pinRead(int pin){ return(0); }
void PiIO::doDelay(unsigned int howLong){ /*usleep(howLong * 1000);*/}
void PiIO::flushSerialData(){}

unsigned int tmp = 0;
unsigned int PiIO::getMillis(void){ return(++tmp); }
#endif