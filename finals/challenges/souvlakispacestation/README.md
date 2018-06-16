Souvlaki Space Station
---------

Use of `strlen` to determine the amount to read into the buffer and
incorrectly calculating the length to read allows an attacker to overflow a
struct member to point a format string char pointer to an address they control.
The controlled `message` member of the struct can be used to do a format string
attack to overwrite the `global_state` member `admin` to enable that flag.
Next, a crash triggered by writing to null with the format string attack will
be handled by a signal handler that gives a `vi` instance to report a bug.
Escaping out of the `vi` instance gives a shell.

Also the binary is ARM and statically built.

# Question Text

```
Pictures and I've fallen
Wonder why I'm here now

nc ctf.pwn.sg 4006
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
