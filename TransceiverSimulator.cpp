#include "stdafx.h"

#include "TransceiverSimulator.h"

#include <ctime>
#include <string>

CTransceiverSimulator::CTransceiverSimulator(ITransceiverBase* ParentInterface)
  : CTransceiverBase(ParentInterface)
{
}


CTransceiverSimulator::~CTransceiverSimulator()
{
}

void CTransceiverSimulator::Hartbeat()
{
  NextSimulationCounter--;
  if (NextSimulationCounter <= 0)
  {
    SReceivedSignal NewSignal = CreateRandomSignal();
    mParentInterface->OnNewReceivedSignal(NewSignal);
    NextSimulationCounter = 50;
  }
}

SReceivedSignal CTransceiverSimulator::CreateRandomSignal()
{
  SReceivedSignal NewSignal;

  NewSignal.SourceId = 1;
  NewSignal.TimeStamp = std::time(nullptr);
  NewSignal.SignalLevel = 0;
  NewSignal.SignalType = RST_PulsePosition;

  char* PulseTrain1 = "175, 2575, 150, 200, 150, 1200, 150, 200, 150, 1200, 150, 1200, 150, 200, 125, 1200, 150, 200, 125, 200, 150, 1200, 125, 200, 150, 1200, 150, 1200, 150, 200, 150, 200, 150, 1225, 150, 1200, 125, 225, 150, 200, 125, 1200, 150, 1200, 150, 200, 150, 1200, 150, 200, 150, 200, 125, 1225, 125, 200, 150, 1200, 125, 200, 150, 1200, 125, 200, 150, 1200, 150, 200, 150, 1200, 150, 1200, 125, 200, 150, 200, 125, 1200, 150, 1200, 125, 225, 150, 200, 125, 1200, 150, 200, 150, 1200, 150, 200, 150, 1200, 150, 200, 150, 1225, 125, 1200, 150, 200, 125, 200, 150, 1200, 150, 200, 125, 1200, 150, 200, 150, 1200, 150, 200, 150, 1200, 150, 200, 125, 1225, 125, 200, 125, 1200, 150, 200, 150, 1200, 150";
  char* PulseTrain2 = "20; B9; DEBUG; Pulses = 132; Pulses(uSec) = 200, 2550, 150, 200, 125, 1200, 150, 200, 150, 1200, 125, 1200, 150, 225, 125, 1200, 125, 225, 125, 200, 150, 1200, 150, 200, 150, 1200, 150, 1200, 125, 200, 125, 200, 125, 1225, 125, 1200, 125, 225, 150, 200, 150, 1200, 150, 1200, 150, 200, 150, 1200, 150, 225, 125, 200, 150, 1200, 125, 200, 150, 1200, 125, 200, 150, 1200, 150, 200, 125, 1225, 150, 200, 125, 1200, 150, 1200, 125, 225, 125, 200, 125, 1200, 150, 1200, 125, 225, 125, 200, 125, 1225, 125, 200, 125, 1225, 125, 200, 125, 1200, 125, 200, 150, 1225, 125, 1200, 150, 200, 125, 200, 125, 1200, 125, 200, 150, 1200, 125, 200, 125, 1200, 150, 200, 125, 1200, 125, 200, 125, 1200, 150, 200, 125, 1200, 150, 200, 150, 1200, 125";

  GetEdgesFromString(NewSignal, PulseTrain2);
  return NewSignal;
}

void CTransceiverSimulator::GetEdgesFromString(SReceivedSignal& NewSignal, char* SourcePulseTrain)
{
  std::string PulseTrain(SourcePulseTrain);  
  size_t StartPos = PulseTrain.find("Pulses(uSec) = ");
  if (StartPos == std::string::npos)
    StartPos = 0;
  else
    StartPos += 15;
  
  size_t EndPos = PulseTrain.find(",", StartPos);
  while (EndPos != std::string::npos)
  {
    NewSignal.Edges.push_back(std::stoi(PulseTrain.substr(StartPos, EndPos - StartPos)));

    StartPos = EndPos+1;
    EndPos = PulseTrain.find(",", StartPos);
  }

  NewSignal.Edges.push_back(std::stoi(PulseTrain.substr(StartPos)));
}
