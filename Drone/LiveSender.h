#pragma once

#include "PacketHandler.h"
#include "UdpSendSocket.h"

class LiveSender : public PacketHandler
{
public:
  LiveSender();
  ~LiveSender();
  virtual void Handle(const unsigned char* packetData, unsigned size);

private:
  UdpSendSocket Socket;
  unsigned PacketCount;
};
