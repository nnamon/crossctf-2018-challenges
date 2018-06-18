#!/bin/sh

cd quals
./build.sh
./quals/run.sh
cd ..

cd finals
./finals/build.sh
./finals/runconcurrent.sh
cd ..

