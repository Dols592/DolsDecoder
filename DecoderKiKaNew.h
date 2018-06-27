//
#pragma once

#include "DecoderBase.h"

class CDecoderKiKaNew :  public CDecoderBase
{
public:
  CDecoderKiKaNew();
  virtual ~CDecoderKiKaNew();

public: //Interface
  virtual bool DecodeSignal(SReceivedSignal NewSignal);

protected: //Help functions

protected: //Variables
};

