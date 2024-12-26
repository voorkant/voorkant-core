#!/usr/bin/env python3

# taken and modified from https://github.com/user-none/Bin-Headers/blob/aaebde3891957b39e4cc4c7844e1ecdecabeaaa2/bin2header.py, with gratitude
# that repo is licensed under MIT

import argparse
import sys

def bin2header(data, var_name='var'):
    out = []
    out.append('unsigned char {var_name}[] = {{'.format(var_name=var_name))
    l = [ data[i:i+12] for i in range(0, len(data), 12) ]
    for i, x in enumerate(l):
        line = ', '.join([ '0x{val:02x}'.format(val=c) for c in x ])
        out.append('  {line}{end_comma}'.format(line=line, end_comma=',' if i<len(l)-1 else ''))
    out.append('};')
    out.append('unsigned int {var_name}_len = {data_len};'.format(var_name=var_name, data_len=len(data)))
    return '\n'.join(out).encode('ascii')

def main():
    parser = argparse.ArgumentParser(description='Generate binary header output')
    parser.add_argument('-i', '--input', required=True , help='Input file')
    parser.add_argument('-o', '--out', required=True , help='Output file')
    parser.add_argument('-v', '--var', required=True , help='Variable name to use in file')

    args = parser.parse_args()
    if not args:
        return 1

    with open(args.input, 'rb') as f:
        data = f.read()

    out = bin2header(data, args.var)
    with open(args.out, 'wb') as f:
        f.write(out)

    return 0

if __name__ == '__main__':
    sys.exit(main())