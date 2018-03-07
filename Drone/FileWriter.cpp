#include "FileWriter.h"
#include "KeyFrame.h"
#include "TimeUtils.h"

#include <iostream>

FileWriter::FileWriter(const std::string& path, int clipTime, int clipLimit)
  : Path(path)
  , ClipTime(clipTime)
  , ClipLimit(clipLimit)
  , FileStartTime(0)
{
  OutputFile.reset();
}

void FileWriter::InitHeader(const unsigned char* packetData, unsigned size)
{
  Header.resize(size);
  memcpy(&Header[0], packetData, size);
}

void FileWriter::Handle(const unsigned char* packetData, unsigned size)
{
  if (!OutputFile.get() || (GetTicks() - FileStartTime > 1000 * ClipTime && isKeyFrame(packetData)))
  {
    std::string fileName = Path + GetTime() + ".h264";
    OutputFile.reset(new File(fileName.c_str(), "wb"));
    OutputFile->Write(&Header[0], Header.size());
    FileStartTime = GetTicks();
    Files.push_back(fileName);
    if (Files.size() > ClipLimit)
    {
      auto path = Files.front();
      std::remove(path.c_str());
      Files.pop_front();
    }
  }

  OutputFile->Write(packetData, size);
}
