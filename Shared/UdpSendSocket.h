#pragma once

extern "C" {
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h> //sleep
#include <netdb.h> 
}

class UdpSendSocket
{
public:
  UdpSendSocket(unsigned port);
  ~UdpSendSocket();

  void Connect();
  unsigned Send(const unsigned char* data, unsigned size);

private:
  unsigned Port;
  int SendSocket;
  sockaddr_in si_me;
};