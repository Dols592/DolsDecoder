#pragma once

#include <stdint.h>
#include "ControlProtocolBase.h"
#include "ControlHWBase.h"

class IControlConnection
{

};

class CControlConnection: public IControlProtocol
{
public:
  CControlConnection(IControlConnection* ControlConnection);
  virtual ~CControlConnection();

public: //Interface to Controller
  void Init();
  void SetControlProtocol(CControlProtocolBase* ControlProtocol);
  void SetControlHardware(CControlHWBase* ControlHardware);

  void AddDebugString(char* String);

public: //Interface to hardware
  void AddIncommingByte(char Byte);
  uint32_t OutgoingQueuSize();
  char GetOutgoingByte();

public: //IControlProtocol overrides (Interface to Protocol)
  void AddOutgoingByteToControlConnection(char Byte);
  void AddOutgoingStringToControlConnection(char* String);
  void AddOutgoingDataToControlConnection(char* Bytes, int32_t Length);

protected: //Help functions

protected: //Variables
  IControlConnection* mControlConnection;
  CControlProtocolBase* mControlProtocol;
  CControlHWBase* mControlHardware;
};

