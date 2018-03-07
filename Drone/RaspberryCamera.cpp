#include "RaspberryCamera.h"
#include "TimeUtils.h"

#include <raspicam/raspicam.h>

#include <iostream>
#include <unistd.h>

RaspberryCamera::RaspberryCamera(unsigned width, unsigned height, unsigned fps)
  : Width(width)
  , Height(height)
  , Fps(fps)
{
  setCameraSettings();
  if (!RaspiCamera.open())
  {
    throw std::runtime_error("Error opening camera");
  }
  printCameraInfo();

  Data.resize(RaspiCamera.getImageBufferSize());
}

RaspberryCamera::~RaspberryCamera()
{
  if (CaptureThread.joinable())
    CaptureThread.join();
}

void RaspberryCamera::setCameraSettings()
{
  RaspiCamera.setWidth(Width);
  RaspiCamera.setHeight(Height);
  RaspiCamera.setFrameRate(Fps);
  RaspiCamera.setFormat(raspicam::RASPICAM_FORMAT_YUV420);
}

void RaspberryCamera::printCameraInfo()
{
  std::cout << "Camera width: " << RaspiCamera.getWidth() << std::endl;
  std::cout << "Camera height: " << RaspiCamera.getHeight() << std::endl;
  std::cout << "Camera frame rate: " << RaspiCamera.getFrameRate() << std::endl;
}

void RaspberryCamera::Capture()
{
  CaptureThread = std::thread(&RaspberryCamera::StartCapture, this);
}

void RaspberryCamera::StartCapture()
{
  try
  {
    while (true)
    {
      bool result = RaspiCamera.grab();
      if (!result)
      {
        std::cout << "Error grab frame from camera " << std::endl;
        sleep(1);
        continue;
      }
      RaspiCamera.retrieve(&Data[0]);
      Handle();
    }
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
}

void RaspberryCamera::AddHandler(std::shared_ptr<FrameHandler> handler)
{
  Handlers.push_back(handler);
}

void RaspberryCamera::RemoveHandler(std::shared_ptr<FrameHandler> handler)
{
  Handlers.remove(handler);
}

unsigned RaspberryCamera::GetWidth() const
{
  return Width;
}

unsigned RaspberryCamera::GetHeight() const
{
  return Height;
}

unsigned RaspberryCamera::GetFps() const
{
  return Fps;
}

void RaspberryCamera::Handle()
{
  for (auto handler : Handlers)
  {
    handler->Handle(&Data[0], Data.size());
  }
}