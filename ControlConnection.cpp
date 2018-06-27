#include "stdafx.h"
#include "ControlConnection.h"

#include "ControlProtocolDebug.h"
//------------------------------------------------------------------
CControlConnection::CControlConnection(IControlConnection* ControlConnection)
  : mControlConnection(ControlConnection)
{
  mControlProtocol = NULL;
  mControlHardware = NULL;
}

CControlConnection::~CControlConnection()
{
  if (mControlProtocol)
    delete mControlProtocol;

  if (mControlHardware)
    delete mControlHardware;
}
//------------------------------------------------------------------
void CControlConnection::Init()
{
  SetControlProtocol(new CControlProtocolDebug(this));

  //SetControlHardware(new CControlProtocolTcp(this));
}

void CControlConnection::SetControlProtocol(CControlProtocolBase* ControlProtocol)
{
  if (mControlProtocol)
    delete mControlProtocol;

  mControlProtocol = ControlProtocol;
}

void CControlConnection::SetControlHardware(CControlHWBase* ControlHardware)
{
  if (mControlHardware)
    delete mControlHardware;

  mControlHardware = ControlHardware;
}

void CControlConnection::AddDebugString(char* String)
{

}
//------------------------------------------------------------------
void CControlConnection::AddIncommingByte(char Byte)
{
  if (mControlProtocol)
    mControlProtocol->AddIncommingByte(Byte);
}

uint32_t CControlConnection::OutgoingQueuSize()
{
  return 0;
}

char CControlConnection::GetOutgoingByte()
{
  return 0;
}
//------------------------------------------------------------------
void CControlConnection::AddOutgoingByteToControlConnection(char Byte)
{
  if (mControlHardware)
    mControlHardware->AddOutgoingByte(Byte);
}

void CControlConnection::AddOutgoingStringToControlConnection(char* String)
{
  if (mControlHardware)
    mControlHardware->AddOutgoingString(String);
}

void CControlConnection::AddOutgoingDataToControlConnection(char* Bytes, int32_t Length)
{
  if (mControlHardware)
    mControlHardware->AddOutgoingData(Bytes, Length);
}
//------------------------------------------------------------------
