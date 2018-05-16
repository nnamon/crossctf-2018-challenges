#!/usr/bin/python

import pycryptonight
import sys
import os
import flag

original = "0100fb8e8ac805899323371bb790db19218afd8db8e3755d8b90f39b3d5506a9abce4fa912244500000000ee8146d49fa93ee724deb57d12cbc6c6f3b924d946127c7a97418f9348828f0f02"
hashed = "87c4e570653eb4c2b42b7a0d546559452dfab573b82ec52f152b7ff98e79446f"

assert(pycryptonight.cn_slow_hash(original.decode("hex"), 1) == hashed.decode("hex"))

def write(data, endl='\n'):
    sys.stdout.write(data + endl)
    sys.stdout.flush()

def main():
    write("%s -> %s" % (original, hashed))
    randomed = os.urandom(2000)
    result = pycryptonight.cn_slow_hash(randomed, 1).encode("hex")
    write(randomed.encode("hex") + "?")
    answer = sys.stdin.readline().strip()
    if answer == result:
        write("Flag: %s" % flag.flag)
    else:
        write("No.")

if __name__ == "__main__":
    main()
