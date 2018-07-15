//
#include "stdafx.h"

#include "MainInterface.h"

#ifdef HAL_WINDOWS
  #include "HalWindows.h"
  IHal& CMainInterface::Hardware = CHalWindows();
#endif

CMainInterface::CMainInterface()
{
}

CMainInterface::~CMainInterface()
{
}