#include "LiveSender.h"
#include "KeyFrame.h"

#include <iostream>
#include <vector>
#include <string.h>

LiveSender::LiveSender(const std::string& host, unsigned port)
  : PacketCount(1)
  , Socket(host, port)
{
  Socket.Connect();
}

LiveSender::~LiveSender()
{
}

void LiveSender::InitHeader(const unsigned char* packetData, unsigned size)
{
  Header.resize(size);
  memcpy(&Header[0], packetData, size);
}

void LiveSender::Handle(const unsigned char* packetData, unsigned size)
{
  if (isKeyFrame(packetData))
  {
    SendHeader();
  }

  std::vector<unsigned char> buffer(size + sizeof(PacketCount));
  memcpy(&buffer[0], &PacketCount, sizeof(PacketCount));
  memcpy(&buffer[sizeof(PacketCount)], packetData, size);
  Socket.Send(&buffer[0], buffer.size());
  ++PacketCount;
}

void LiveSender::SendHeader()
{
  unsigned headerNumber = 0;
  std::vector<unsigned char> buffer(Header.size() + sizeof(headerNumber));
  memcpy(&buffer[0], &headerNumber, sizeof(headerNumber));
  memcpy(&buffer[sizeof(headerNumber)], &Header[0], Header.size());
  Socket.Send(&buffer[0], buffer.size());
}

std::string LiveSender::GetHost() const
{
  return Socket.GetHost();
}

unsigned LiveSender::GetPort() const
{
  return Socket.GetPort();
}