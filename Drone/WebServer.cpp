#include "WebServer.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <functional>
#include <iostream>

WebServer::WebServer(int port, Camera& camera, StartController& record)
  : Port(port)
  , CameraCapture(camera)
  , Record(record)
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
  rapidjson::StringBuffer s;
  rapidjson::Writer<rapidjson::StringBuffer> writer(s);
  writer.StartObject();
  if (LiveStream.get())
  {
    writer.Key("status");
    writer.String("ok");
    writer.Key("width");
    writer.Uint(LiveStream->GetWidth());
    writer.Key("height");
    writer.Uint(LiveStream->GetHeight());
    writer.Key("server");
    writer.String(Sender->GetHost().c_str());
    writer.Key("port");
    writer.Uint(Sender->GetPort());
  }
  else
  {
    writer.Key("status");
    writer.String("stopped");
  }
  writer.EndObject();

  session->close(200, s.GetString());
}

void WebServer::GetStartRecord(const std::shared_ptr<restbed::Session> session)
{
  Record.Start();
  session->close(200, "{status: \"ok\"}\n");
}

void WebServer::GetStopRecord(const std::shared_ptr<restbed::Session> session)
{
  Record.Stop();
  session->close(200, "{status: \"ok\"}\n");
}

void WebServer::GetStartLive(const std::shared_ptr<restbed::Session> session)
{
  try
  {
    auto request = session->get_request();
    int width = stoi(request->get_query_parameter("width"));
    int height = stoi(request->get_query_parameter("height"));
    int bitrate = stoi(request->get_query_parameter("bitrate"));
    int framerate = stoi(request->get_query_parameter("framerate"));
    std::string server = request->get_query_parameter("server");
    int port = stoi(request->get_query_parameter("port"));

    if (width > CameraCapture.GetWidth() || height > CameraCapture.GetHeight())
    {
      throw std::runtime_error("Requested frame size bigger than frame captured by camera");
    }
    if (framerate > CameraCapture.GetFps())
    {
      throw std::runtime_error("Requested framerate bigger than framerate captured by camera");
    }

    StartLive(width, height, bitrate, framerate, server, port);
    session->close(200, "{status: \"ok\"}\n");
  }
  catch (const std::exception& e)
  {
    std::string errorString = std::string("{status: \"") + e.what() + std::string("\"}\n");
    session->close(500, errorString.c_str());
  }
}

void WebServer::GetStopLive(const std::shared_ptr<restbed::Session> session)
{
  StopLive();
  session->close(200, "{status: \"ok\"}\n");
}

void WebServer::StartLive(unsigned width, unsigned height, unsigned bitrate, unsigned fps, const std::string& server, unsigned port)
{
  if (LiveStream.get())
  {
    StopLive();
  }
  Sender = std::make_shared<LiveSender>(server, port);
  Encoder = std::make_shared<RaspberryEncoder>(width, height, bitrate, fps, *Sender);
  LiveStream = std::make_shared<Stream>(*Encoder, CameraCapture.GetWidth(), CameraCapture.GetHeight(), CameraCapture.GetFps(), width, height, fps, true);
  LiveStream->Start();
  CameraCapture.AddHandler(LiveStream);
}

void WebServer::StopLive()
{
  LiveStream->Stop();
  CameraCapture.RemoveHandler(LiveStream);
  LiveStream.reset();
  Encoder.reset();
  Sender.reset();
}

void WebServer::Run()
{
  auto settings = std::make_shared<restbed::Settings>();
  settings->set_port(Port);
  settings->set_default_header("Connection", "close");
  WebService.start(settings);
}
