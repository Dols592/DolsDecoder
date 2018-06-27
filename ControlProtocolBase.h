#pragma once

#include <stdint.h>

class CControlConnection;

class IControlProtocol
{
public:
  virtual void AddOutgoingByteToControlConnection(char Byte) = NULL;
  virtual void AddOutgoingStringToControlConnection(char* String) = NULL;
  virtual void AddOutgoingDataToControlConnection(char* Bytes, int32_t Length) = NULL;
};

class CControlProtocolBase
{
public:
  CControlProtocolBase(IControlProtocol* ParentInterface);
  virtual ~CControlProtocolBase();

public: //CControlProtocolBase virtuals
  virtual void AddIncommingByte(char Byte) = NULL;

protected: //Help functions

protected: //Variables
  IControlProtocol* mParentInterface;
};

