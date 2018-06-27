#pragma once

#include "DDConfig.h"
#include "ControlConnection.h"
#include "TransceiverBase.h"

#include "DecoderBase.h"

#include <map>

class CController: public IControlConnection, public ITransceiverBase
{
public:
  CController();
  virtual ~CController();

public: //Interface
  void Init(const CDDConfig& Config);
  void Heartbeat();

public: //IControlConnection overrides

public: //ITransceiverBase overrides
  virtual void OnNewReceivedSignal(const SReceivedSignal& NewSignal);

protected: //Help functions

public: //Variables
  std::map<int32_t, CControlConnection*> mControlInterfaces;
  std::map<int32_t, CTransceiverBase*> mTransceivers;
  std::map<int32_t, CDecoderBase*> mDecoders;
};


