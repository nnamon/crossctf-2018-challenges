Kryptonight 2
---------

Challenge requiring the user to hash data with cryptonight lite variant 1.

# Question Text

```
Have I got a little story for you
What you thought was your daddy
Was nothin' but a

nc ctf.pwn.sg 1503
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

Annotated working exploit is in src/exploit.sh
