#pragma once

class FrameHandler
{
public:
  virtual void Handle(const unsigned char* data, unsigned size) = 0;
};
