#include "stdafx.h"
#include "DecoderBase.h"


CDecoderBase::CDecoderBase()
{
  mBitCount = 0;
}


CDecoderBase::~CDecoderBase()
{
}


uint32_t CDecoderBase::ReadUnsigned32(int32_t Start, int32_t Length)
{
  uint32_t ReturnValue = 0;
  for (int i = 0; i < Length; i++)
  {
    ReturnValue = ReturnValue << 1;
    if (mBits[Start + i] != 0)
      ReturnValue++;

  }
  return ReturnValue;
}

int32_t CDecoderBase::Read2Complement32(int32_t Start, int32_t Length)
{
  int32_t ReturnValue = 0;
  for (int i = 1; i < Length; i++)
  {
    ReturnValue = ReturnValue << 1;
    if (mBits[Start + i] != 0)
      ReturnValue++;
  }

  if (mBits[Start] != 0)
  {
    ReturnValue -= 1 << (Length - 1);
  }
  return ReturnValue;
}