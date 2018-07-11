//
#pragma once

#include "TransceiverHWIface.h"

class CTransceiverHWRFM69W : public ITransceiverHWIface
{
public:
  CTransceiverHWRFM69W();
  virtual ~CTransceiverHWRFM69W();

public: //Interface ITransceiverHWIface
  virtual void SetupForOOK();
  virtual void SwitchToSend();
  virtual void SwitchToReceive();
  virtual int ReadBinairyInput();
  virtual int WriteBinairyOutput();

};

