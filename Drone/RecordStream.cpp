#include "RecordStream.h"
#include "TimeUtils.h"

RecordStream::RecordStream(Encoder& encoder)
  : EncoderEngine(encoder)
  , Started(false)
{
}

void RecordStream::Handle(const unsigned char* data, unsigned size)
{
  if (Started)
  {
    EncoderEngine.Encode(data, size);
  }
}

void RecordStream::Start()
{
  Started = true;
}

void RecordStream::Stop()
{
  Started = false;
}

bool RecordStream::IsStarted() const
{
  return Started;
}