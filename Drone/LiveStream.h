#pragma once

#include "Encoder.h"
#include "FrameHandler.h"
#include "StartController.h"

class LiveStream : public FrameHandler, public StartController
{
public:
  LiveStream(Encoder& encoder);
  virtual void Handle(const unsigned char* data, unsigned size);

  virtual void Start();
  virtual void Stop();
  virtual bool IsStarted() const;

private:
  Encoder& EncoderEngine;
  bool Started;
};
