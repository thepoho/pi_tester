#include "pin.h"
#include <string>

Pin::Pin()
{

}
Pin::~Pin()
{

}

void Pin::startup(int _num, string _name, int _wpi_num)
{
  num = _num;
  name = _name;
  wpi_num = _wpi_num;
  cout << "Starting pin " << num << " name: " << name << " wpi: " << wpi_num << endl;
}

void Pin::serializeJson(Writer<StringBuffer>* writer)
{
  writer->StartObject();
  writer->String("name");
  writer->String(name.c_str());
  writer->String("num");
  writer->Int(num);
  writer->String("wpi_num");
  writer->Int(wpi_num);

  writer->String("output_state");
  if(outputState == LOW){
    writer->String("low");
  }else{
    writer->String("high");
  }

  writer->String("direction");
  if(direction == INPUT){
    writer->String("input");
  }else{
    writer->String("output");
  }
  writer->EndObject();
}

