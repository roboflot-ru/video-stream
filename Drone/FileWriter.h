#pragma once

#include "File.h"
#include "PacketHandler.h"
#include "TimeUtils.h"

#include <list>
#include <memory>
#include <string>
#include <vector>

class FileWriter : public PacketHandler
{
public:
  FileWriter(const std::string& path, int clipTime, int clipLimit);
  virtual void InitHeader(const unsigned char* packetData, unsigned size);
  virtual void Handle(const unsigned char* packetData, unsigned size);

private:
  const std::string Path;
  int ClipTime;
  int ClipLimit;
  unsigned FileStartTime;
  std::unique_ptr<File> OutputFile;
  std::list<std::string> Files;
  std::vector<unsigned char> Header;
};
