#pragma once


enum NControInterfaceTypes
{
  CIT_Direct = 0,
  //CIT_Serial,
  //CIT_TCP,
  //CIT_UDP,
  CIT_Count
};

enum NControInterfaceProtocol
{
  CIP_DEBUG = 0,
  CIP_RFLINK,
  CIP_Count
};

struct SDDConfigControlInterface
{
  NControInterfaceTypes Interfacetype;
  NControInterfaceProtocol InterfaceProtocol;
  char* Name;

  SDDConfigControlInterface()
  {
    Reset();
  }
  void Reset()
  {
    Interfacetype = CIT_Count;
    Name = "Unknown";
  }
};