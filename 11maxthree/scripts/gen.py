#!/usr/bin/python3

import sys
from random import randrange, randint

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 4:
    print("Usage: ./gen.py num mod filename \n")
    print("where 1. num - numbers amount \n")
    print("      2. mod - maximum value of number's module \n")
    print("      3. filename - output file name. \n")
    sys.exit(1)

  num = int(argv[1])
  mod = int(argv[2])
  filename = argv[3]

  if num < 0 or num > 1000000:
    print("Domain error: 0 <= num <= 1000000 \n")
    sys.exit(1)

  if mod < 0 or mod > 1000000:
    print("Domain error: 0 <= mod <= 1000000 \n")
    sys.exit(1)

  return (num, mod, filename)

#------------------

def gen_rand_seq(num: int, mod: int):
  
  seq = []

  for _ in range(num-1):
    seq.append(f"{randrange(-mod,mod)}\n")

  seq.append("\n")

  return seq

#------------------

def write_to_file(out_file, seq):
  for elem in seq:
    out_file.write(elem)

#==================

num, mod, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:
  out_file.write(f"{num}\n")
  write_to_file(out_file, gen_rand_seq(num, mod))
