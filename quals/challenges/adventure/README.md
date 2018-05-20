Choose Your Own Adventure
---------

This is a misc challenge inspired by 2009's MIT Mystery Hunt's Galactic. Each room
has a description that talks about a specific chemical. The coordinates and the
given score represents the compound's chemical formula, it is summarised in the
table below. The entire list of compounds can be seen in [map.txt][map].

| x | y | z | Score |
|---|---|---|-------|
| C | O | N |   H   |

Some rooms have numbers scribbled on the walls, that is an indicator the common name
of the compound is to be used in the clue. The red numbers represents the index of
the character meant to be taken.

[map]: ./src/map.txt

# Question Text

```
Maybe your question was too long. You reduced the length of your question and asked
the oracle again: "Where's the flag?"

As expected, she had no reaction again. You sigh... maybe the solution really was
in there after all. You close your eyes and started willing yourself back into
the enemy's base...

Non-standard flag format: `[A-Z0-9]+`

nc ctf.pwn.sg 1400
```

*Creator -  prokarius (@prokarius)*

# Setup Guide

0. Install docker on the hosting system
1. Replace the flag in distribute/flag
2. Build the docker image with: `sh dockerbuild.sh`
3. Replace the port 1500 with your desired port in dockerrun.sh
4. Start the docker image: `sh dockerrun.sh`
5. Test the connectivity with netcat.

# Solution Details
Identify each chemical, and piece together the clues as written on the wall. The
final clue should read "capsaicin in formula" to which the correct answer:
C18H27NO3
