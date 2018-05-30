#!/usr/bin/python

import argparse

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("infile")
    parser.add_argument("outfile")
    args = parser.parse_args()

    data = open(args.infile).read() + "\x00"
    template = "char art[] = {%s};"
    values = ", ".join(hex(ord(i)) for i in data)
    open(args.outfile, 'w').write(template % values)

if __name__ == "__main__":
    main()
