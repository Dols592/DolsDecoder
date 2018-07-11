//
#pragma once


class ITransceiverHWIface
{
public: //Interface
  virtual void SetupForOOK() = 0;
  virtual void SwitchToSend() = 0;
  virtual void SwitchToReceive() = 0;
  virtual int ReadBinairyInput() = 0;
  virtual int WriteBinairyOutput() = 0;
};



