﻿#include "FileWriter.h"
#include "TimeUtils.h"

FileWriter::FileWriter(const std::string& filename)
  : Output(filename)
{
}

void FileWriter::Handle(const unsigned char* packetData, unsigned size)
{
  Profile profile("Write");
  Output.Write(packetData, size);
}
