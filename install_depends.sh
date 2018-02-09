#!/bin/bash

rm -rf restbed/
git clone --recursive https://github.com/corvusoft/restbed.git
mkdir restbed/build
cd restbed/build
cmake [-DBUILD_TESTS=YES] [-DBUILD_EXAMPLES=YES] [-DBUILD_SSL=NO] [-DBUILD_SHARED=YES] [-DCMAKE_INSTALL_PREFIX=/output-directory] ..
make
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

cd /opt/vc/src/hello_pi
sudo chmod +x rebuild.sh
sudo ./rebuild.sh
cd -
