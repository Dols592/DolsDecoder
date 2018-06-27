#include "stdafx.h"

#include "Controller.h"

#include "TransceiverSimulator.h"

#include "DecoderKiKaNew.h"

CController::CController()
{
}


CController::~CController()
{
}

void CController::Init(const CDDConfig& Config)
{
  //mControlInterfaces[0] = new CControlConnection();
  //mControlInterfaces[0]->Init();

  mTransceivers[0] = new CTransceiverSimulator(this);

  mDecoders[0] = new CDecoderKiKaNew();

}

void CController::Heartbeat()
{
  mTransceivers[0]->Hartbeat();
}

void CController::OnNewReceivedSignal(const SReceivedSignal& NewSignal)
{
  mDecoders[0]->DecodeSignal(NewSignal);
}