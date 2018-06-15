Fitblips
---------

Number of comparisons is leaked to allow a remote attacker to do a timing
attack on the flag.

# Question Text

```
How many steps does your Fitblip beep?

nc ctf.pwn.sg 4003
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
