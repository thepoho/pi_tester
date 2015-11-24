#include "pin.h"
#include <string>

Pin::Pin()
{

}
Pin::~Pin()
{

}

void Pin::startup(int _num, string _name, int _wpi_num, int idx)
{
  num = _num;
  name = _name;
  wpi_num = _wpi_num;
  index = idx;
  cout << "Starting pin idx " << index << " num: " << num << " name: " << name << " wpi: " << wpi_num << endl;
}

void Pin::serializeJson(Writer<StringBuffer>* writer)
{
  writer->StartObject();
  writer->String("name");
  writer->String(name.c_str());
  writer->String("num");
  writer->Int(num);

  writer->String("index");
  writer->Int(index);

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

