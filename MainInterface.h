#pragma once

#include "HalIface.h"
#include "DDConfig.h"
#include "MainConfig.h"
#include "DolsVersion.h"
class CMainInterface
{
public: //Constructor
  CMainInterface();
  virtual ~CMainInterface();

public:
  CDDConfig Config;
  static IHal& Hardware;
  
};