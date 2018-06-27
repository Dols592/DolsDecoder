//
#pragma once

#include <stdint.h>

class CControlConnection;

class CControlHWBase
{
public:
  CControlHWBase(CControlConnection* ParentControl);
  virtual ~CControlHWBase();

public: //CControlHWBase virtuals
  virtual void AddOutgoingByte(char Byte) = NULL;
  virtual void AddOutgoingString(char* String);
  virtual void AddOutgoingData(char* Bytes, int32_t Length);

protected: //Help functions

protected: //Variables
  CControlConnection* mParentControl;
};

