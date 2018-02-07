#pragma once

class PacketHandler
{
public:
  virtual void Handle(const unsigned char* packetData, unsigned size) = 0;
};
