#include "pi_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

// string pinNames[] = {"dc_power","dc_power","gpio_02","dc_power","gpio_03","ground","gpio_04","gpio_14","ground","gpio_15","gpio_17","gpio_18",
// "gpio_27","ground","gpio_22","gpio_23","dc_power","gpio_24","gpio_10","ground","gpio_09","gpio_25","gpio_11","gpio_08","ground","gpio_07",
// "id_sd","id_sc","gpio_5","ground","gpio_6","gpio_12","gpio_13","ground","gpio_19","gpio_16","gpio_26","gpio_20","ground","gpio_21"};

PiIO::PiIO()
{

}
PiIO::~PiIO()
{

}

void PiIO::setupPins(){
  // for(int i =0; i < 40; i++){
    // not used yet
  // }
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