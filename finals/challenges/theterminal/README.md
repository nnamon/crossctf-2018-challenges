The Terminal
---------

Various vulnerabilities in a web application allows an attacker to leak local
files and get code execution through a date to image generator.

# Question Text

```
How long more can you stand it?

http://ctf.pwn.sg:4083
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
