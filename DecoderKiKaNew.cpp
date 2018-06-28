#include "stdafx.h"
#include "DecoderKiKaNew.h"


CDecoderKiKaNew::CDecoderKiKaNew()
{
  mDataStart = 0;
  mDataEnd = 0;
  mIsDimmer = false;
}


CDecoderKiKaNew::~CDecoderKiKaNew()
{
}

bool CDecoderKiKaNew::DecodeSignal(const SReceivedSignal& NewSignal)
{
  if (!CheckSignalLength(NewSignal)) return false;
  if (!CheckBitTiming(NewSignal)) return false;
  if (!DecodeBits(NewSignal)) return false;
  if (!GetMessageFromBits()) return false;

  return false;
}

#define NUMBER_OF_EDGES_SWITCH  128
#define NUMBER_OF_EDGES_DIMMER  144
bool CDecoderKiKaNew::CheckSignalLength(const SReceivedSignal& NewSignal)
{
  if (NewSignal.Edges.size() < 130) return false;
  if (NewSignal.Edges.size() > 160) return false;

  mDataStart = FindDataStart(NewSignal);
  mDataEnd = FindDataEnd(NewSignal);
  int32_t NumberOfPulses = mDataEnd - mDataStart;

  if (NumberOfPulses == NUMBER_OF_EDGES_SWITCH)
  {
    mIsDimmer = false;
    return true;
  }
  
  if (NumberOfPulses == NUMBER_OF_EDGES_DIMMER)
  {
    mIsDimmer = true;
    return true;
  }

  return false;
}

  int32_t CDecoderKiKaNew::FindDataStart(const SReceivedSignal & NewSignal)
  {
    int32_t DataStart(0);

    for (int i = 0; i < 20; i++)
    {
      if (NewSignal.Edges[i] >= 2000)
        DataStart = i + 1;
    }

    return DataStart;
  }

  int32_t CDecoderKiKaNew::FindDataEnd(const SReceivedSignal & NewSignal)
  {
    int32_t DataEnd(((int32_t)NewSignal.Edges.size()) - 1);

    if (NewSignal.Edges[DataEnd] >= 6000)
      DataEnd--;

    return DataEnd;
  }

#define BIT_TIME_MAX 2250
#define BIT_TIME_MIN 1250
#define BIT_DIMMER 112
bool CDecoderKiKaNew::CheckBitTiming(const SReceivedSignal& NewSignal)
{
  for (int i = mDataStart; i < mDataEnd; i += 4)
  {
    int32_t TotalBitTime = NewSignal.Edges[i] + NewSignal.Edges[i+1] + NewSignal.Edges[i+2] + NewSignal.Edges[i+3];

    if (TotalBitTime > BIT_TIME_MAX)
      return false;

    if (TotalBitTime < BIT_TIME_MIN)
    {
      if (mIsDimmer && i == BIT_DIMMER)
        continue;
      
      return false;
    }
  }
  return true;
}

#define BIT_0_MIN_TIME  750
bool CDecoderKiKaNew::DecodeBits(const SReceivedSignal& NewSignal)
{
  mBitCount = 0;
  for (int i = mDataStart; i < mDataEnd; i += 4)
  {
    if (NewSignal.Edges[i + 1] > BIT_0_MIN_TIME)
      mBits[mBitCount++] = 1;
    else
      mBits[mBitCount++] = 0;
  }

  return true;
}

bool CDecoderKiKaNew::GetMessageFromBits()
{
  uint32_t Address = ReadUnsigned32(0, 26);
  uint32_t Group = ReadUnsigned32(26, 1);
  uint32_t On = ReadUnsigned32(27, 1);
  uint32_t Unit = ReadUnsigned32(28, 4);
  uint32_t DimmerValue = 0;
  if (mIsDimmer)
    DimmerValue = ReadUnsigned32(32, 4);

  return true;
}