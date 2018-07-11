//
#pragma once

#include "DecoderBase.h"

class CDecoderArc : public CDecoderBase
{
public:
  CDecoderArc();
  virtual ~CDecoderArc();

public: //Interface
  virtual bool DecodeSignal(const SReceivedSignal& NewSignal);

protected: //Help functions
  bool CheckSignalLength(const SReceivedSignal& NewSignal);
    int32_t FindDataStart(const SReceivedSignal & NewSignal);
    int32_t FindDataEnd(const SReceivedSignal & NewSignal);
  bool CheckBitTiming(const SReceivedSignal& NewSignal);
  bool DecodeBits(const SReceivedSignal& NewSignal);
  bool GetMessageFromBits();

protected: //Variables
  int32_t mDataStart;
  int32_t mDataEnd;
  int32_t mSplitTime;
};

