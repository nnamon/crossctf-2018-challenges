#!/usr/bin/python

import pycryptonight
import sys
import os
import flag

original = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
hashed = "b5a7f63abb94d07d1a6445c36c07c7e8327fe61b1647e391b4c7edae5de57a3d"

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
