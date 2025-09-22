#!/bin/bash

set -e

DETACH=""
if [ "$1" == "-d" ]; then
    DETACH="$1"
fi

docker build -t lvgl-dev .
docker run -it $DETACH --rm --name lvgl-dev -v $(pwd):/ez-lvgl lvgl-dev /bin/bash
