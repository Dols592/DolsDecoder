#pragma once

class IHal
{
public:
  virtual char* ReadConfigFileFromStorage() = 0;
  virtual void WriteConfigFileToStorage(char* XmlData) = 0;
};

