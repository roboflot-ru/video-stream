#pragma once

#include "Camera.h"

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
  std::vector<std::shared_ptr<FrameHandler> > Handlers;
  std::thread CaptureThread;
};