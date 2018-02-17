#include "Config.h"
#include "FileWriter.h"
#include "LiveSender.h"
#include "LiveStream.h"
#include "RaspberryCamera.h"
#include "RaspberryEncoder.h"
#include "RecordStream.h"
#include "WebServer.h"

#include <iostream>

int main(int argc, char **argv) 
{
  try
  {
    Config config;

    std::string recordPath = config.GetString("record", "file_name");
    int width = config.GetInt("record", "width");
    int height = config.GetInt("record", "height");
    int bitrate = config.GetInt("record", "bitrate");
    int fps = config.GetInt("record", "fps");

    int liveWidth = config.GetInt("live", "width");
    int liveHeight = config.GetInt("live", "height");
    int liveBitrate = config.GetInt("live", "bitrate");

    FileWriter fileWriter(recordPath);
    LiveSender liveSender;
    RaspberryEncoder recordEncoder(width, height, bitrate, fps, fileWriter);
    RaspberryEncoder liveEncoder(liveWidth, liveHeight, liveBitrate, fps, liveSender);

    auto recordStream = std::make_shared<RecordStream>(recordEncoder);
    auto liveStream = std::make_shared<LiveStream>(liveEncoder);

    RaspberryCamera camera(width, height, fps);
    camera.AddHandler(recordStream);
    camera.AddHandler(liveStream);
    camera.Capture();

    WebServer webServer(*recordStream, *liveStream);
    webServer.Run();
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}

