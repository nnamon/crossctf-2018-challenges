Lossy Oracle
---------

A simple crypto challenge which has a small element of probability involved.

# Question Text

```
No one believes I can recover the message from this crappy ORacle.

nc ctf.pwn.sg 1401
```

*Creator -  prokarius (@prokarius)*

# Setup Guide

0. Install docker on the hosting system
1. Replace the flag with a file of your choice
2. Build the docker image with: `sh dockerbuild.sh`
3. Replace the port 1500 with your desired port in dockerrun.sh
4. Start the docker image: `sh dockerrun.sh`
5. Test the connectivity with netcat.

# Exploit Details
Repeatedly ping the server a large number of times. Any bits that were ever 0 is
certain to be a 0 bit. By pinging a large number of times, we can be sure the
probability a 1 bit is actually a 0 bit is exceedingly low (0.5 ^ n).

More complex algorithms can be developed, but why?

Working exploit to be created.
