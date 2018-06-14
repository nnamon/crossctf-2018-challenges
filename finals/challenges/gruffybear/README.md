GruffyBear
---------

The binary is compiled with all protections. The key vulnerabilities are an
information leak that allows the attacker to get the address of free in libc
and a use-after-free that lets the attacker craft an arbitrary function pointer
to evoke after certain conditions are met.

# Question Text

```
There's something fishy about this Build-A-Bear workshop...

nc ctf.pwn.sg 4002
```

*Creator -  amon (@nn_amon)*

# Setup Guide

0. Install docker on the hosting system
1. Replace the flag in distribute/flag
2. Build the docker image with: `sh dockerbuild.sh`
3. Replace the exposed port with your desired port in dockerrun.sh
4. Start the docker image: `sh dockerrun.sh`
5. Test the connectivity with netcat.

# Exploit Details

Annotated working exploit is in src/exploit.sh
