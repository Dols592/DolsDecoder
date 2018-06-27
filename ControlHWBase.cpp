#include "stdafx.h"
#include "ControlHWBase.h"


CControlHWBase::CControlHWBase(CControlConnection* ParentControl)
  : mParentControl(ParentControl)
{
}


CControlHWBase::~CControlHWBase()
{
}


void CControlHWBase::AddOutgoingString(char* String)
{
  uint32_t StrSize = strnlen_s(String, 1024);
  AddOutgoingData(String, StrSize);
}

void CControlHWBase::AddOutgoingData(char* Bytes, int32_t Length)
{
  for (int i = 0; i < Length; i++)
  {
    AddOutgoingByte(Bytes[i]);
  }
}
