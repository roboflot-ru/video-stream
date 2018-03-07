#pragma once

#include "LiveReciever.h"

#include <memory>
#include <restbed>

class WebServer
{
public:
  WebServer(int port);
  void Run();

private:
  void GetRegister(const std::shared_ptr<restbed::Session> session);
  void GetUnregister(const std::shared_ptr<restbed::Session> session);

private:
  int Port;
  restbed::Service WebService;
  std::shared_ptr<LiveReciever> Reciever;
};
