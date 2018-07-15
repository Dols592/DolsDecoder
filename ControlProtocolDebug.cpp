//
#include "stdafx.h"
#include "ControlProtocolDebug.h"

//#include "StaticConfig.h"
#include "ControlConnection.h"

CControlProtocolDebug::CControlProtocolDebug(IControlProtocol* ParentInterface)
  : CControlProtocolBase(ParentInterface)
{
  mLineBufferWritePos = 0;
  mLineCommandEnd = 0;
}

CControlProtocolDebug::~CControlProtocolDebug()
{
}

void CControlProtocolDebug::AddIncommingByte(char Byte)
{
  if (mLineBufferWritePos >= CP_INCOMMING_BUFFER_SIZE)
    return;
  else if (Byte == '\r')
  {
    if (mLineCommandEnd == 0)
      mLineCommandEnd = mLineBufferWritePos;

    mLineBuffer[mLineBufferWritePos++] = 0;
    ProcessIncommingCommand();
    mLineBufferWritePos = 0;
    mLineCommandEnd = 0;
  }
  else if (Byte < 0x20 || Byte >= 0x80)
    return;
  else if (Byte == 0x20)
  {
    if (mLineBufferWritePos == 0)
      return;

    if (mLineCommandEnd == 0)
      mLineCommandEnd = mLineBufferWritePos;

    mLineBuffer[mLineBufferWritePos++] = 0;
  }
  else
    mLineBuffer[mLineBufferWritePos++] = Byte;
}


void CControlProtocolDebug::ProcessIncommingCommand()
{ 
  for (int32_t i = 0; i < mLineCommandEnd; i++)
    mLineBuffer[i] = toupper(mLineBuffer[i]);

  if (strcmp(mLineBuffer, "VER") == 0)
  {
    char VersionString[_MAX_ITOSTR_BASE10_COUNT];
    //_itoa_s(DD_VERSION, VersionString, _MAX_ITOSTR_BASE10_COUNT, 10);
    mParentInterface->AddOutgoingStringToControlConnection("Version ");
    mParentInterface->AddOutgoingStringToControlConnection(VersionString);
    mParentInterface->AddOutgoingStringToControlConnection("\r\n");
  }
}