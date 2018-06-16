#!/bin/bash

docker kill $(docker ps -q)
docker rm $(docker ps -a -q)

cur_dir=$PWD
for directory in challenges/*/service/Dockerfile; do
    echo Building $directory
    cd "$(dirname "$directory")"
    chmod +x dockerbuild.sh
    ./dockerbuild.sh
    cd $cur_dir
done

for directory in challenges/*/service/Dockerfile; do
    echo Running $directory
    cd "$(dirname "$directory")"
    chmod +x dockerrun.sh
    ./dockerrun.sh
    cd $cur_dir
done
