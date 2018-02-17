#include "LiveSender.h"

#include <iostream>
#include <vector>
#include <string.h>

const unsigned RtpPacketSize = 15000;

LiveSender::LiveSender()
  : PacketCount(0)
  , Socket(10001)
{
  Socket.Connect();
}

LiveSender::~LiveSender()
{
}

void LiveSender::Handle(const unsigned char* packetData, unsigned size)
{
  std::vector<unsigned char> buffer(size + sizeof(PacketCount));
  memcpy(&buffer[0], &PacketCount, sizeof(PacketCount));
  memcpy(&buffer[sizeof(PacketCount)], packetData, size);
  Socket.Send(&buffer[0], buffer.size());
  ++PacketCount;
}
