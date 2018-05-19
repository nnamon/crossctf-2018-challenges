#!/bin/bash

docker kill $(docker ps -q)

for directory in challenges/*/service/Dockerfile; do
    echo Running $directory
    cd $(dirname $directory)
    chmod +x dockerrun.sh
    ./dockerrun.sh
    cd $cur_dir
done
