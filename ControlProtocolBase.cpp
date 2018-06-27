#include "stdafx.h"
#include "ControlProtocolBase.h"


CControlProtocolBase::CControlProtocolBase(IControlProtocol* ParentInterface)
  : mParentInterface(ParentInterface)
{
}


CControlProtocolBase::~CControlProtocolBase()
{
}
