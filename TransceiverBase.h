#pragma once

#include <stdint.h>
#include <vector>

enum NReceivedSignalType
{
  RST_PulsePosition = 0,
  RST_Count
};

struct SReceivedSignal
{
  uint32_t SourceId;
  uint64_t TimeStamp;
  uint32_t SignalLevel;
  NReceivedSignalType SignalType;

  std::vector<uint32_t> Edges;
};

class ITransceiverBase
{
public:
  virtual void OnNewReceivedSignal(const SReceivedSignal& NewSignal) = 0;
};

class CTransceiverBase
{
public:
  CTransceiverBase(ITransceiverBase* ParentInterface);
  virtual ~CTransceiverBase();

public: //Interface
  virtual void Hartbeat();

protected: //Help functions

protected: //Variables
  ITransceiverBase * mParentInterface;
};

