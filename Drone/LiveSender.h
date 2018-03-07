#pragma once

#include "PacketHandler.h"
#include "UdpSendSocket.h"

#include <vector>

class LiveSender : public PacketHandler
{
public:
  LiveSender(const std::string& host, unsigned port);
  ~LiveSender();
  virtual void InitHeader(const unsigned char* packetData, unsigned size);
  virtual void Handle(const unsigned char* packetData, unsigned size);

  std::string GetHost() const;
  unsigned GetPort() const;

private:
  void SendHeader();

private:
  UdpSendSocket Socket;
  unsigned PacketCount;
  std::vector<unsigned char> Header;
};
