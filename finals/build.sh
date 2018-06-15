#!/bin/bash

cur_dir=$PWD
for directory in challenges/*/service/Dockerfile; do
    echo Building $directory
    cd $(dirname $directory)
    chmod +x dockerbuild.sh
    ./dockerbuild.sh
    cd $cur_dir
done
