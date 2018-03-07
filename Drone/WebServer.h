#pragma once

#include "Camera.h"
#include "LiveSender.h"
#include "Stream.h"
#include "RaspberryEncoder.h"
#include "StartController.h"

#include <memory>
#include <restbed>

class WebServer
{
public:
  WebServer(int port, Camera& camera, StartController& record);
  void Run();

private:
  void GetStatus(const std::shared_ptr<restbed::Session> session);
  void GetStartRecord(const std::shared_ptr<restbed::Session> session);
  void GetStopRecord(const std::shared_ptr<restbed::Session> session);
  void GetStartLive(const std::shared_ptr<restbed::Session> session);
  void GetStopLive(const std::shared_ptr<restbed::Session> session);

  void StartLive(unsigned width, unsigned height, unsigned bitrate, unsigned fps, const std::string& server, unsigned port);
  void StopLive();

private:
  int Port;
  Camera& CameraCapture;
  StartController& Record;
  restbed::Service WebService;
  std::shared_ptr<LiveSender> Sender;
  std::shared_ptr<RaspberryEncoder> Encoder;
  std::shared_ptr<Stream> LiveStream;
};
