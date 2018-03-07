#pragma once

#include "Encoder.h"
#include "PacketHandler.h"

extern "C" {
#include "ilclient.h"
}

class RaspberryEncoder : public Encoder
{
public:
  RaspberryEncoder(unsigned width, unsigned height, unsigned bitrate, unsigned fps, PacketHandler& packetHandler);
  virtual void Encode(const unsigned char* data, unsigned size);

private:
  const unsigned Width;
  const unsigned Height;
  const unsigned Bitrate;
  const unsigned Fps;
  PacketHandler& Handler;
  COMPONENT_T* VideoEncode;
  bool FirstPacket;
};
