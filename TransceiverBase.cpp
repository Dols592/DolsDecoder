#include "stdafx.h"
#include "TransceiverBase.h"


CTransceiverBase::CTransceiverBase(ITransceiverBase* ParentInterface)
  : mParentInterface(ParentInterface)
{
}


CTransceiverBase::~CTransceiverBase()
{
}

void CTransceiverBase::Hartbeat()
{

}