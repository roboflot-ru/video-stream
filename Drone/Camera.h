#pragma once

#include "FrameHandler.h"

#include <memory>

class Camera
{
public:
  virtual void Capture() = 0;
  virtual void AddHandler(std::shared_ptr<FrameHandler> handler) = 0;
  virtual void RemoveHandler(std::shared_ptr<FrameHandler> handler) = 0;
  virtual unsigned GetWidth() const = 0;
  virtual unsigned GetHeight() const = 0;
  virtual unsigned GetFps() const = 0;
};
