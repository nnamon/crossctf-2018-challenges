#!/bin/bash

service apache2 start

cd /backend
while true; do
    sudo -u theterminal gunicorn -w 8 -b 0.0.0.0:8082 app:app
done
