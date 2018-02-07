#include "WebServer.h"

#include <functional>
#include <iostream>

WebServer::WebServer(StartController& record, StartController& live)
  : Record(record)
  , Live(live)
{
  auto statusResource = std::make_shared<restbed::Resource>();
  statusResource->set_path("/status");
  statusResource->set_method_handler("GET", std::bind(&WebServer::GetStatus, this, std::placeholders::_1));
  WebService.publish(statusResource);

  auto startRecordResource = std::make_shared<restbed::Resource>();
  startRecordResource->set_path("/start_record");
  startRecordResource->set_method_handler("GET", std::bind(&WebServer::GetStartRecord, this, std::placeholders::_1));
  WebService.publish(startRecordResource);

  auto stopRecordResource = std::make_shared<restbed::Resource>();
  stopRecordResource->set_path("/stop_record");
  stopRecordResource->set_method_handler("GET", std::bind(&WebServer::GetStopRecord, this, std::placeholders::_1));
  WebService.publish(stopRecordResource);

  auto startLiveResource = std::make_shared<restbed::Resource>();
  startLiveResource->set_path("/start_live");
  startLiveResource->set_method_handler("GET", std::bind(&WebServer::GetStartLive, this, std::placeholders::_1));
  WebService.publish(startLiveResource);

  auto stopLiveResource = std::make_shared<restbed::Resource>();
  stopLiveResource->set_path("/stop_live");
  stopLiveResource->set_method_handler("GET", std::bind(&WebServer::GetStopLive, this, std::placeholders::_1));
  WebService.publish(stopLiveResource);
}

void WebServer::GetStatus(const std::shared_ptr<restbed::Session> session)
{
  std::string answer = "record=" + std::to_string(Record.IsStarted()) + "&live=" + std::to_string(Live.IsStarted()) + "\n";
  session->close(200, answer);
}

void WebServer::GetStartRecord(const std::shared_ptr<restbed::Session> session)
{
  Record.Start();
  session->close(200);
}

void WebServer::GetStopRecord(const std::shared_ptr<restbed::Session> session)
{
  Record.Stop();
  session->close(200);
}

void WebServer::GetStartLive(const std::shared_ptr<restbed::Session> session)
{
  Live.Start();
  session->close(200);
}

void WebServer::GetStopLive(const std::shared_ptr<restbed::Session> session)
{
  Live.Stop();
  session->close(200);
}

void WebServer::Run()
{
  auto settings = std::make_shared<restbed::Settings>();
  settings->set_port(8080);
  settings->set_default_header("Connection", "close");
  WebService.start(settings);
}
