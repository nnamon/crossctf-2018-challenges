GoCoin! Plus
---------

I thought blockchain was cool, so I made my own coin.

GoCoin! Plus is the forked and improved version of GoCoin!.

Update: I've improved it! More secures and with real cryptos, it's a true cryptocoin now!

# Question Text

```
It is all in the challenge.

http://ctf.pwn.sg:2053
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

Change JWT algorithm to HS256, sign it with public key and change claim values!