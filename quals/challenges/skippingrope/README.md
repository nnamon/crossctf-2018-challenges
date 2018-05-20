Skipping Rope
---------

The binary reads shellcode into sets of 6 bytes at 12 bytes apart. The trick is
to encode the shellcode into instructions of less than or equal to 4 bytes and
adding a short jump instruction.

# Question Text

```
How high and how fast can you go on the skipping rope?

nc ctf.pwn.sg 1501
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
