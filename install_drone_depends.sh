#!/bin/bash

sudo apt-get install cmake
sudo apt-get install libssl-dev
sudo apt-get install libopencv-dev

rm -rf restbed/
git clone --recursive https://github.com/corvusoft/restbed.git
mkdir restbed/build
cd restbed/build
sudo cmake [-DBUILD_TESTS=YES] [-DBUILD_EXAMPLES=YES] [-DBUILD_SSL=NO] [-DBUILD_SHARED=YES] [-DCMAKE_INSTALL_PREFIX=/output-directory] ..
sudo make
sudo make install
sudo ldconfig
make test
cd ../..

rm -rf raspicam
git clone https://github.com/cedricve/raspicam
cd raspicam
mkdir build
cd build
cmake ..
make
sudo make install
sudo ldconfig
cd ../..

rm -rf rapidjson
git clone https://github.com/Tencent/rapidjson.git

cd /opt/vc/src/hello_pi
sudo chmod +x rebuild.sh
sudo ./rebuild.sh
cd -
