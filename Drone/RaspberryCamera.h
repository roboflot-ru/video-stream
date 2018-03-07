#pragma once

#include "Camera.h"

#include <list>
#include <memory>
#include <thread>
#include <vector>

#include <raspicam/raspicam.h>

class RaspberryCamera : public Camera
{
public:
  RaspberryCamera(unsigned width, unsigned height, unsigned fps);
  ~RaspberryCamera();
  virtual void Capture();
  virtual void AddHandler(std::shared_ptr<FrameHandler> handler);
  virtual void RemoveHandler(std::shared_ptr<FrameHandler> handler);
  virtual unsigned GetWidth() const;
  virtual unsigned GetHeight() const;
  virtual unsigned GetFps() const;

private:
  void Handle();
  void setCameraSettings();
  void printCameraInfo();
  void StartCapture();

private:
  const unsigned Width;
  const unsigned Height;
  const unsigned Fps;
  raspicam::RaspiCam RaspiCamera;
  std::vector<unsigned char> Data;
  std::list<std::shared_ptr<FrameHandler> > Handlers;
  std::thread CaptureThread;
};