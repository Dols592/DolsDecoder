//
#include "stdafx.h"
#include "DecoderArc.h"


CDecoderArc::CDecoderArc()
{
  mDataStart = 0;
  mDataEnd = 0;
  mSplitTime = 500;
}

CDecoderArc::~CDecoderArc()
{
}

bool CDecoderArc::DecodeSignal(const SReceivedSignal& NewSignal)
{
  if (!CheckSignalLength(NewSignal)) return false;
  if (!CheckBitTiming(NewSignal)) return false;
  if (!DecodeBits(NewSignal)) return false;
  if (!GetMessageFromBits()) return false;

  return true;
}

#define NUMBER_OF_EDGES_SWITCH  48
bool CDecoderArc::CheckSignalLength(const SReceivedSignal& NewSignal)
{
  if (NewSignal.Edges.size() < 48) return false;
  if (NewSignal.Edges.size() > 55) return false;

  mDataEnd = FindDataEnd(NewSignal);
  mDataStart = mDataEnd - NUMBER_OF_EDGES_SWITCH;

  return true;
}

int32_t CDecoderArc::FindDataEnd(const SReceivedSignal & NewSignal)
{
  int32_t DataEnd(((int32_t)NewSignal.Edges.size()) - 1);

  if (NewSignal.Edges[DataEnd] >= 6000)
    DataEnd--;

  return DataEnd;
}

#define BIT_TIME_MAX_DIFF 100
bool CDecoderArc::CheckBitTiming(const SReceivedSignal& NewSignal)
{
  int32_t ShortMin = 0xFFFF;
  int32_t ShortMax = 0;
  int32_t LongMin = 0xFFFF;
  int32_t LongMax = 0;
  for (int i = mDataStart+4; i <= mDataEnd-4; i += 4)
  {
    ShortMin = min(ShortMin, NewSignal.Edges[i]);
    ShortMax = max(ShortMax, NewSignal.Edges[i]);
    LongMin = min(LongMin, NewSignal.Edges[i+1]);
    LongMax = max(LongMax, NewSignal.Edges[i+1]);
  }

  if (ShortMax - ShortMin > BIT_TIME_MAX_DIFF) return false;
  if (LongMax - LongMin > BIT_TIME_MAX_DIFF) return false;

  mSplitTime = (ShortMin + ShortMax + LongMin + LongMax) / 4;

  return true;
}

bool CDecoderArc::DecodeBits(const SReceivedSignal& NewSignal)
{
  mBitCount = 0;
  for (int i = mDataStart+3; i < mDataEnd; i += 4)
  {
    if (NewSignal.Edges[i] > mSplitTime)
      mBits[mBitCount++] = 0;
    else
      mBits[mBitCount++] = 1;
  }

  return true;
}


bool CDecoderArc::GetMessageFromBits()
{
  uint32_t Address = ReadUnsigned32(0, 26); // Sender address
  uint32_t Group = ReadUnsigned32(26, 1); // Group function 1 = On, 0 = Off
  uint32_t Action = ReadUnsigned32(27, 1); // On = 1, Off = 0, Dim = 0
  uint32_t Key = ReadUnsigned32(28, 4); // 
  uint32_t DimmerValue = 0;

  return true;
}