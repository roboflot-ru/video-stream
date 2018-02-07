#pragma once

#include "File.h"
#include "PacketHandler.h"

#include <string>

class FileWriter : public PacketHandler
{
public:
  FileWriter(const std::string& filename);
  virtual void Handle(const unsigned char* packetData, unsigned size);

private:
  File Output;
};
