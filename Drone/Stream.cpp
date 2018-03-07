#include "Stream.h"
#include "Resize.h"
#include "TimeUtils.h"
#include <stdexcept>

Stream::Stream(Encoder& encoder, unsigned cameraWidth, unsigned cameraHeight, unsigned cameraFps, unsigned width, unsigned height, unsigned fps, bool started)
  : EncoderEngine(encoder)
  , CameraWidth(cameraWidth)
  , CameraHeight(cameraHeight)
  , CameraFps(cameraFps)
  , Width(width)
  , Height(height)
  , Fps(fps)
  , Started(started)
  , FrameNumber(0)
  , TakeFrame(0)
  , SkipFrame(0)
{
  if (CameraFps == Fps)
  {
    return;
  }
  else if (static_cast<float>(CameraFps) / static_cast<float>(Fps) > 2)
  {
    TakeFrame = CameraFps / Fps;
    if (TakeFrame * Fps != CameraFps)
    {
      throw std::runtime_error("Cannot adjust framerate");
    }
  }
  else
  {
    auto diffFrames = CameraFps - Fps;
    SkipFrame = CameraFps / diffFrames;
    if (SkipFrame * diffFrames != CameraFps)
    {
      throw std::runtime_error("Cannot adjust framerate");
    }
  }
}

void Stream::Handle(const unsigned char* data, unsigned size)
{
  if (!Started)
  {
    return;
  }
  ++FrameNumber;
  if (TakeFrame > 0)
  {
    if (FrameNumber % TakeFrame != 0)
    {
      return;
    }
  }
  else if (SkipFrame > 0)
  {
    if (FrameNumber % SkipFrame == 0)
    {
      return;
    }
  }

  if (Width == CameraWidth && Height == CameraHeight)
  {
    EncoderEngine.Encode(data, size);
  }
  else
  {
    auto resizedData = Resize(CameraWidth, CameraHeight, Width, Height, data);
    EncoderEngine.Encode(&resizedData[0], resizedData.size());
  }
}

void Stream::Start()
{
  Started = true;
}

void Stream::Stop()
{
  Started = false;
}

bool Stream::IsStarted() const
{
  return Started;
}

unsigned Stream::GetWidth() const
{
  return Width;
}

unsigned Stream::GetHeight() const
{
  return Height;
}

unsigned Stream::GetFps() const
{
  return Fps;
}
