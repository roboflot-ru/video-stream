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

wget http://www.live555.com/liveMedia/public/live555-latest.tar.gz
tar -xf live555-latest.tar.gz
cd live
./genMakefiles linux
make
sudo make install
sudo ldconfig
