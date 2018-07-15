#pragma once

#include "MainConfig.h"

#ifdef HAL_WINDOWS

#include "HalIface.h"

class CHalWindows : public IHal
{
public: //Constructor
  CHalWindows();
  virtual ~CHalWindows();

public: //IHal interface
  virtual char* ReadConfigFileFromStorage();
  virtual void WriteConfigFileToStorage(char* XmlData);
};

#endif