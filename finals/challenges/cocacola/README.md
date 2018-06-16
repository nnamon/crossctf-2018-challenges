Coca Cola
---------

Uninitialized stack variables allows an attacker to forge the entries in a
data struct to overwrite a C string pointer in the struct to point at the
flag page.

# Question Text

```
Catch the Wave. Coke!

nc ctf.pwn.sg 4001
```

*Creator -  amon (@nn_amon)*

# Setup Guide

0. Install docker on the hosting system
1. Replace the flag in distribute/flag
2. Build the docker image with: `sh dockerbuild.sh`
3. Replace the port 1500 with your desired port in dockerrun.sh
4. Start the docker image: `sh dockerrun.sh`
5. Test the connectivity with netcat.

# Exploit Details

Annotated working exploit is in src/exploit.py
