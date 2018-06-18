#!/bin/sh

cd quals
./build.sh
./run.sh
cd ..

cd finals
./build.sh
./runconcurrent.sh
cd ..

