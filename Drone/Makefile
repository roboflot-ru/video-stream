INC=-I../../raspicam/src -I/opt/vc/src/hello_pi/libs/ilclient -I/opt/vc/include -I/usr/include -I../../restbed/source -I..
PRELIB=/opt/vc/src/hello_pi/libs/ilclient/libilclient.a ../../restbed/build/librestbed.a -L/opt/vc/lib -lbcm_host -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lraspicam -lssl -lcrypto
CPPFLAGS = -std=c++11
BUILDLIST=Config.cpp File.cpp FileWriter.cpp LiveStream.cpp main.cpp RaspberryCamera.cpp RaspberryEncoder.cpp RecordStream.cpp TimeUtils.cpp WebServer.cpp 
THIRDPARTYBUILDLIST=../ini/cpp/INIReader.cpp ../ini/ini.c

all:
	g++ $(CPPFLAGS) $(INC) $(BUILDLIST) $(THIRDPARTYBUILDLIST) $(PRELIB) -o VideoService -ldl -lrt

	
clean:
	rm -rf VideoService *.o
	rm -r *.h264