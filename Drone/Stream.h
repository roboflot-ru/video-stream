#pragma once

#include "Encoder.h"
#include "FrameHandler.h"
#include "StartController.h"

class Stream : public FrameHandler, public StartController
{
public:
  Stream(Encoder& encoder, unsigned cameraWidth, unsigned cameraHeight, unsigned cameraFps, unsigned width, unsigned height, unsigned fps, bool started);

  virtual void Handle(const unsigned char* data, unsigned size);

  virtual void Start();
  virtual void Stop();
  virtual bool IsStarted() const;

  unsigned GetWidth() const;
  unsigned GetHeight() const;
  unsigned GetFps() const;

private:
  Encoder& EncoderEngine;
  unsigned CameraWidth;
  unsigned CameraHeight;
  unsigned CameraFps;
  unsigned Width;
  unsigned Height;
  unsigned Fps;
  bool Started;
  unsigned FrameNumber;
  unsigned TakeFrame;
  unsigned SkipFrame;
};
