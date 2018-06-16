FTLOG
---------

ARM shellcoding challenge.

# Question Text

```
https://youtu.be/RW2vXFLXtps

nc ctf.pwn.sg 4004

Hint: The raspberry Pis might come in handy but you can look at using qemu too.
```

*Creator -  amon (@nn_amon)*

# Setup Guide

0. Install docker on the hosting system
1. Replace the flag in distribute/flag
2. Build the docker image with: `sh dockerbuild.sh`
3. Replace the port with your desired port in dockerrun.sh
4. Start the docker image: `sh dockerrun.sh`
5. Test the connectivity with netcat.

# Exploit Details

Annotated working exploit is in src/exploit.py
