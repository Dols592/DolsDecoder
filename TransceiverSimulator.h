#pragma once

#include <stdint.h>

#include "TransceiverBase.h"


class CTransceiverSimulator: public CTransceiverBase
{
public:
  CTransceiverSimulator(ITransceiverBase* ParentInterface);
  virtual ~CTransceiverSimulator();

public: //CTransceiverBase virtuals
  virtual void Hartbeat();

protected: //Help functions
  SReceivedSignal CreateRandomSignal();
  void GetEdgesFromString(SReceivedSignal& NewSignal, char* PulseTrain);

protected: //Variables
  int32_t NextSimulationCounter;
};

