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

  loadPins();
}

void PiIO::setPinMode(int pin, int mode)
{
  assert(pin < 40);
  assert(pins[pin].getWpiNum() != -1);
  pinMode(pins[pin].getWpiNum(), mode);
}

void PiIO::pinWrite(int pin, int value)
{
  setPinMode(pin, OUTPUT);
  digitalWrite(pins[pin], value);
}

int PiIO::pinRead(int pin)
{
  setPinMode(pin, INPUT);
  return(digitalRead(pins[pin]));
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
void PiIO::startup()
{
  loadPins();
}

void PiIO::setPinMode(int pin, int mode)
{
  assert(pin < 40);
  assert(pins[pin].getWpiNum() != -1);
}
void PiIO::pinWrite(int pin, int value)
{
  setPinMode(pin, OUTPUT);
}
int  PiIO::pinRead(int pin)
{ 
  setPinMode(pin, OUTPUT);
  return(0); 
}

void PiIO::doDelay(unsigned int howLong){ /*usleep(howLong * 1000);*/}

unsigned int tmp = 0;
unsigned int PiIO::getMillis(void){ return(++tmp); }
#endif

void PiIO::test(string poho){
  cout << poho << endl;
}
void PiIO::shiftOut(Document* document)
{
  int clockPin = document->FindMember("clock_pin")->value.GetInt();
  int dataPin = document->FindMember("data_pin")->value.GetInt();
  int latchPin = document->FindMember("latch_pin")->value.GetInt();

  cout << "pins: " << clockPin << " " << dataPin << " " << latchPin << endl;

  setPinMode(clockPin, OUTPUT);
  setPinMode(dataPin, OUTPUT);
  setPinMode(latchPin, OUTPUT);

  pinWrite(dataPin, LOW);
  pinWrite(latchPin, LOW);
  pinWrite(clockPin, LOW);
  
  const Value& data = document->FindMember("data")->value;
  int size = data.Size();
  size = size - 1;
  
  cout << "Shifting out: ";
  for (int i = size; i >= 0; i--){ // Uses SizeType instead of size_t
    cout << data[i].GetInt();
    pinWrite(dataPin, data[i].GetInt());
    pinWrite(clockPin, HIGH);
    pinWrite(clockPin, LOW);
  }
  pinWrite(latchPin, HIGH);
  cout << endl;
}

void PiIO::loadPins()
{
  // fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("pins.json");
//http://rapidjson.org/md_doc_stream.html#FileReadStream

  cout << "load pins" << endl;
  /*FILE* pFile = fopen("pins.json", "r");
  char buffer[65536];
  FileReadStream is(pFile, buffer, sizeof(buffer));
  Document document;
  document.ParseStream<0, UTF8<>, FileReadStream>(is);
*/

  FILE* fp = fopen("/home/poho/git/pi_tester/pins.json", "r"); // non-Windows use "r"
  char readBuffer[65536];
  FileReadStream is(fp, readBuffer, sizeof(readBuffer));
  Document document;
  document.ParseStream(is);
  fclose(fp);

  assert(document.HasMember("pins"));
  assert(document.IsObject());

   const Value& data = document["pins"];
   //const Value& data = document.FindMember("pins");//.value;
   int size = data.Size();
   size = size - 1;
   cout << "Size is " << size << endl;
   for (int i = size; i >= 0; i--){ // Uses SizeType instead of size_t
     int wpi = -1;
     if(data[i].HasMember("wpi")){
       wpi = data[i]["wpi"].GetInt();
     }
     pins[i].startup(i, data[i]["name"].GetString(), wpi);
   }
}
