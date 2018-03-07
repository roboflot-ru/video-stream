#pragma once

#include "Live.h"
#include "LockedBuffer.h"
#include "UdpListenSocket.h"

#include <map>
#include <thread>
#include <vector>

class LiveReciever
{
public:
  LiveReciever(unsigned portIn, unsigned portOut);
  ~LiveReciever();

private:
  void ReceiveThreadFunc();
  void Receive();
  void SendIfPossible();
  void WriteNextPacket(unsigned char* data, unsigned size);
  void StoreHeader(const unsigned char* data, unsigned size);

private:
  bool Canceled;
  LockedBuffer PayloadBuffer;
  Live RtspLive;
  UdpListenSocket ListenSocket;
  std::thread ReceiveThread;
  std::vector<unsigned char> Header;
  std::map<unsigned, std::vector<unsigned char> > SequencedRtp;
  unsigned PrevPacketNumber;
};
