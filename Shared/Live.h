#pragma once

#include "Buffer.h"

#include <string>
#include <thread>

class Live
{
public:
  Live(Buffer& payloadBuffer);
  ~Live();

private:
  Buffer& PayloadBuffer;
  std::thread RtspServerThread;
};
