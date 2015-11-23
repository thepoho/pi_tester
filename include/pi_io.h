#ifndef _PIIO_H
#define _PIIO_H
#include "pin.h"
#include "common_defines.h"

#ifdef BUILD_RASPI
  #include <wiringPi.h>
#else
  #define LOW 0
  #define HIGH 1
  #define INPUT 0
  #define OUTPUT 1
#endif


class PiIO
{
public:
  PiIO();
  ~PiIO();
  void startup();
  void setPinMode(int pin, int mode);
  //void pullUpDnControl(int pin, int pud);
  void pinWrite(int pin, int value);
  //void pwmWrite(int pin, int value);
  int pinRead(int pin);  //needed
  void shiftOut(Document* document);
  void test(string poho);

  //int analogRead(int pin);
  //void analogWrite(int pin, int value);
  void doDelay(unsigned int howLong);
  unsigned int getMillis(void);

  void flushSerialData();

  void setupPins();
  //void setSerialOutput(int num, char state);

private:
  //char currentSerialState[SERIAL_NUM_OUTPUTS];

  //bool serialOutputsDirty;
  void loadPins();
  Pin pins[40];
};

#endif
