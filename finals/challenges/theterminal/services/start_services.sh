#!/bin/bash

service apache2 start

cd /backend
gunicorn -w 4 -b 0.0.0.0:8082 app:app
