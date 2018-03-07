#include "Config.h"
#include "FileWriter.h"
#include "RaspberryCamera.h"
#include "RaspberryEncoder.h"
#include "Stream.h"
#include "WebServer.h"

#include <iostream>

int main(int argc, char **argv) 
{
  try
  {
    Config config;

    int cameraWidth = config.GetInt("camera", "width");
    int cameraHeight = config.GetInt("camera", "height");
    int cameraFps = config.GetInt("camera", "fps");
    bool recordStarted = config.GetInt("record", "started") == 1;
    std::string recordPath = config.GetString("record", "path");
    int width = config.GetInt("record", "width");
    int height = config.GetInt("record", "height");
    int bitrate = config.GetInt("record", "bitrate");
    int fps = config.GetInt("record", "fps");
    int clipTime = config.GetInt("record", "clip_time");
    int clipLimit = config.GetInt("record", "clip_limit");

    int httpServerPort = config.GetInt("common", "http_server_port");

    FileWriter fileWriter(recordPath, clipTime, clipLimit);
    RaspberryEncoder recordEncoder(width, height, bitrate, fps, fileWriter);

    auto recordStream = std::make_shared<Stream>(recordEncoder, cameraWidth, cameraHeight, cameraFps, width, height, fps, recordStarted);

    RaspberryCamera camera(cameraWidth, cameraHeight, cameraFps);
    camera.AddHandler(recordStream);
    camera.Capture();

    WebServer webServer(httpServerPort, camera, *recordStream);
    webServer.Run();
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}

