#pragma once

#include "FrameHandler.h"

#include <memory>

class Camera
{
public:
  virtual void Capture() = 0;
  virtual void AddHandler(std::shared_ptr<FrameHandler> handler) = 0;
};
