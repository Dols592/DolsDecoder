//
#include "stdafx.h"

#include "HalWindows.h"

CHalWindows::CHalWindows()
{
}

CHalWindows::~CHalWindows()
{
}

char* CHalWindows::ReadConfigFileFromStorage()
{
  FILE* ConfigFile = fopen("c:\\DolsConfig.xml", "r");

  if (ConfigFile == NULL)
    return NULL;

  fseek(ConfigFile, 0, SEEK_END);
  long FileSize = ftell(ConfigFile);
  rewind(ConfigFile);

  if (FileSize < 5)
  {
    fclose(ConfigFile);
    return NULL;
  }

  char* Buffer = (char*) malloc(sizeof(char) * FileSize);
  if (Buffer == NULL)
  {
    fclose(ConfigFile);
    return NULL;
  }

  size_t BytesRead = fread(Buffer, 1, FileSize, ConfigFile);
  if (BytesRead != FileSize)
  {
    free(Buffer);
    fclose(ConfigFile);
    return NULL;
  }

  fclose(ConfigFile);
  return Buffer;
}

void CHalWindows::WriteConfigFileToStorage(char* XmlData)
{
  FILE* ConfigFile = fopen("c:\\DolsConfig.xml", "w");
  if (ConfigFile == NULL)
    return;

  size_t XmlSize = strlen(XmlData);
  if (XmlSize < 5)
    return;

  fwrite(XmlData, 1, XmlSize, ConfigFile);

  fclose(ConfigFile);
}

