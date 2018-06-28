#pragma once

#include "TransceiverBase.h"

#define MAX_NR_OF_BITS  512

class CDecoderBase
{
public:
  CDecoderBase();
  virtual ~CDecoderBase();

public: //Interface
  virtual bool DecodeSignal(const SReceivedSignal& NewSignal) = NULL;

protected: //Help functions
  uint32_t ReadUnsigned32(int32_t Start, int32_t Length);
  int32_t Read2Complement32(int32_t Start, int32_t Length);

protected: //Variables
  int32_t mBitCount;
  char mBits[MAX_NR_OF_BITS];
};

