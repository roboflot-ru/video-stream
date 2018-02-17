#include "LiveStream.h"

LiveStream::LiveStream(Encoder& encoder)
  : EncoderEngine(encoder)
  , Started(false)
{
}

void LiveStream::Handle(const unsigned char* data, unsigned size)
{
  if (Started)
  {
    EncoderEngine.Encode(data, size);
  }
}

void LiveStream::Start()
{
  Started = true;
}

void LiveStream::Stop()
{
  Started = false;
}

bool LiveStream::IsStarted() const
{
  return Started;
}