#pragma once

#include "FrameHandler.h"

class RecordHandler : public FrameHandler
{
public:
  virtual void Handle(const unsigned char* data, unsigned size);
};
