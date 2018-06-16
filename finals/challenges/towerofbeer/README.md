Tower Of Beer
---------
Two different beers, two different challenges.

Rochefort 6 entails reversing an -O3 binary and breaking the LCG.

Rochefort 8 entails reversing a binary search tree (where each node is a different type) and keying in relevant data values to substitute in.

# Question Text

# Rochefort 6

```
Nothing like a Rochefort 6 in the hot summer weather...

nc ctf.pwn.sg 16667
```

# Rochefort 8

```
Why have a Rochefort 6 when you can have a Rochefort 8?

nc ctf.pwn.sg 16667
```

*Creator -  waituck (@wongwaituck)*

# Setup Guide

0. Install docker on the hosting system
1. Replace the flag in distribute/flag
2. Build the docker image with: `sh dockerbuild.sh`
3. Replace the port 1500 with your desired port in dockerrun.sh
4. Start the docker image: `sh dockerrun.sh`
5. Test the connectivity with netcat.

# Exploit Details

Annotated working exploit is in src/exploit.sh
