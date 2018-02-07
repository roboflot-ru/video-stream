#pragma once

class StartController
{
public:
  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual bool IsStarted() const = 0;
};
