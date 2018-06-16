The Evilness
---------

One byte fault injectino in a string lets you get access to a `ed` context
which gives you shell with `!sh`.

# Question Text

```
Ready for something ridiculously difficult?

nc ctf.pwn.sg 4020
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

Annotated working exploit is in src/exploit.sh
