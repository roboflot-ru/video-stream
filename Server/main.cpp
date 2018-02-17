#include "Live.h"
#include "LockedBuffer.h"
#include "UdpListenSocket.h"

#include "File.h"

#include <iostream>
#include <string.h>

const unsigned RtpPacketSize = 150000;

const unsigned char KeyFrameData[] = { 0x00, 0x00, 0x00, 0x01, 0x25, 0x88 };
bool isKeyFrame(unsigned char* c)
{
  return memcmp(c, KeyFrameData, 6) == 0;
}

int main(int argc, char **argv) 
{
  try
  {
    LockedBuffer lockedBuffer(2 * RtpPacketSize);
    Live live(lockedBuffer);
    UdpListenSocket udpListenSocket(10001);
    udpListenSocket.Connect();
    unsigned char buffer[64*1024];
    unsigned PrevCount = 0;
    unsigned char header[100];
    unsigned headerSize = 0;
    while (1)
    {
      auto size = udpListenSocket.Listen(buffer, sizeof(buffer));
      unsigned count = 0;
      memcpy(&count, buffer, sizeof(count));
      if (count == 0)
      {
        headerSize = size - sizeof(count);
        memcpy(header, buffer + sizeof(count), headerSize);
      }

      if (PrevCount + 1 != count && count != 0)
      {
        std::cout << "seq mismatch" << std::endl;
      }
      PrevCount = count;

      if (isKeyFrame(buffer + sizeof(count)))
      {
        if (lockedBuffer.GetDataSize() > 2 * RtpPacketSize)
        {
          lockedBuffer.Reset();
          lockedBuffer.Add(header, headerSize);
        }
      }

      lockedBuffer.Add(buffer + sizeof(count), size - sizeof(count));
    }
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}

