#pragma once

#include <stdint.h>

#include "ControlProtocolBase.h"

#define CP_INCOMMING_BUFFER_SIZE 100

class CControlProtocolDebug: public CControlProtocolBase
{
public:
  CControlProtocolDebug(IControlProtocol* ParentInterface);
  virtual ~CControlProtocolDebug();

public: //CControlProtocolBase Overrides
  virtual void AddIncommingByte(char Byte);

protected: //Help functions
  void ProcessIncommingCommand();

protected: //Variables
  char mLineBuffer[CP_INCOMMING_BUFFER_SIZE];
  int32_t mLineBufferWritePos;
  int32_t mLineCommandEnd;

};

