#pragma once

#include "TransceiverBase.h"

class CDecoderBase
{
public:
  CDecoderBase();
  virtual ~CDecoderBase();

public: //Interface
  virtual bool DecodeSignal(SReceivedSignal NewSignal) = NULL;

protected: //Help functions

protected: //Variables
};

