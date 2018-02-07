#pragma once

#include "StartController.h"

#include <memory>
#include <restbed>

class WebServer
{
public:
  WebServer(StartController& record, StartController& live);
  void Run();

private:
  void GetStatus(const std::shared_ptr<restbed::Session> session);
  void GetStartRecord(const std::shared_ptr<restbed::Session> session);
  void GetStopRecord(const std::shared_ptr<restbed::Session> session);
  void GetStartLive(const std::shared_ptr<restbed::Session> session);
  void GetStopLive(const std::shared_ptr<restbed::Session> session);

private:
  StartController& Record;
  StartController& Live;
  restbed::Service WebService;
};
