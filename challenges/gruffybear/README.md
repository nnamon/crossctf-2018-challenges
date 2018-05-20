Real Baby Pwnable
---------

The binary is vulnerable to a memory information leak as well as a stack
overflow vulnerability. It is compiled with stack canary and PIE.

The service fills out a buffer with fibonacci numbers and prompts the user
repeatedly for which fibonnaci(n) number to query. There is no bounds checking
on the n to query and memory addresses after the buffer can be retrieved. An
attacker can leverage this to leak the canary as well as the return address
back to main. This allows the attacker to bypass the stack canary during the
overflow and to calculate the address of `babymode` function from the main
leak.

# Question Text

```
This is an actual baby pwn challenge.

nc ctf.pwn.sg 1500
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
