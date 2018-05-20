Even Flow
---------

The binary has a two byte shell command injection which can be used to get
return codes with `$?`. The attacker can bruteforce the flag byte by byte by
observing the return codes when attempting flags.

# Question Text

```
Do you like shell command injection?

nc ctf.pwn.sg 1601
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
