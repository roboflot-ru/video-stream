#pragma once

class PacketHandler
{
public:
  virtual void InitHeader(const unsigned char* packetData, unsigned size) = 0;
  virtual void Handle(const unsigned char* packetData, unsigned size) = 0;
};
