#include "Live.h"
#include "H264Subsession.h"
#include "TimeUtils.h"

#include "BasicUsageEnvironment.hh"
#include "RTSPServer.hh"
#include "ServerMediaSession.hh"

#include <iostream>
#include <vector>

Live::Live(Buffer& payloadBuffer)
  : PayloadBuffer(payloadBuffer)
{
  TaskScheduler* scheduler = BasicTaskScheduler::createNew();
  UsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);

  RTSPServer* rtspServer = RTSPServer::createNew(*env, 8554, NULL);
  if (rtspServer == NULL)
  {
    throw std::runtime_error(std::string("Failed to create RTSP server: ") + env->getResultMsg());
  }

  H264Subsession *h264Subsession = new H264Subsession(*env, PayloadBuffer);
  ServerMediaSession* sms = ServerMediaSession::createNew(*env, "h264Stream", "h264Stream", "Drone live stream session");
  sms->addSubsession(h264Subsession);
  rtspServer->addServerMediaSession(sms);

  if (rtspServer->setUpTunnelingOverHTTP(80) || rtspServer->setUpTunnelingOverHTTP(8000) || rtspServer->setUpTunnelingOverHTTP(8080))
  {
  }

  auto eventLoop = [&env]()
  {
    env->taskScheduler().doEventLoop();
  };
  RtspServerThread = std::thread(eventLoop);
}

Live::~Live()
{
  if (RtspServerThread.joinable())
    RtspServerThread.join();
}
