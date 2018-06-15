GoCoin!
---------

I thought blockchain was cool, so I made my own coin.

# Question Text

```
It is all in the challenge.

http://ctf.pwn.sg:8182
```

*Creator - quanyang (@quanyang)*

# Setup Guide

0. Install docker on the hosting system
1. Replace the flag in distribute/flag
2. Build the docker image with: `sh dockerbuild.sh`
3. Replace the port 1500 with your desired port in dockerrun.sh
4. Start the docker image: `sh dockerrun.sh`
5. Test the connectivity with netcat.

# Exploit Details

Withdraw 0.005 until you get enough to buy flag. http://127.0.0.1:8182/deposit?amount=0.005