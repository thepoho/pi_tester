#ifndef _PIN_H
#define _PIN_H

#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1



class Pin
{
public:
  Pin();
  ~Pin();
  void startup();
private:
  string name;
  int num;
  int direction;
  int outputState;
};

#endif
