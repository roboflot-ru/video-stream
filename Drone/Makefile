INC=-I../Shared -I../raspicam/src -I/opt/vc/src/hello_pi/libs/ilclient -I/opt/vc/include -I/usr/include -I../restbed/source -I../restbed/dependency/asio/asio/include -I.. -I/usr/local/include/liveMedia -I/usr/local/include/groupsock -I/usr/local/include/UsageEnvironment -I/usr/local/include/BasicUsageEnvironment
PRELIB=/opt/vc/src/hello_pi/libs/ilclient/libilclient.a ../restbed/build/librestbed.a -L/opt/vc/lib -lbcm_host -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lraspicam -lssl -lcrypto -lliveMedia -lBasicUsageEnvironment -lgroupsock -lUsageEnvironment
CPPFLAGS = -std=c++11
BUILDLIST=FileWriter.cpp LiveSender.cpp LiveStream.cpp main.cpp RaspberryCamera.cpp RaspberryEncoder.cpp RecordStream.cpp WebServer.cpp
SHAREDBUILDLIST=../Shared/Buffer.cpp ../Shared/Config.cpp ../Shared/File.cpp ../Shared/H264Subsession.cpp ../Shared/LockedBuffer.cpp ../Shared/MutexHolder.cpp ../Shared/PacketFrameSource.cpp ../Shared/TimeUtils.cpp ../Shared/UdpSendSocket.cpp
THIRDPARTYBUILDLIST=../ini/cpp/INIReader.cpp ../ini/ini.c

all:
	g++ $(CPPFLAGS) $(INC) $(BUILDLIST) $(SHAREDBUILDLIST) $(THIRDPARTYBUILDLIST) $(PRELIB) -o VideoService -ldl -lrt

	
clean:
	rm -rf VideoService *.o
	rm -r *.h264
