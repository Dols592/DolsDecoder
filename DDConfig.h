#pragma once

class CDDConfig
{
public:
  CDDConfig();
  ~CDDConfig();

public: //Interface
  void ReadFromStorage();
  void SerializeToBinaryBlob();
  void DeSerialize();
  
protected: //Help functions

public: //ConfigItems

};

