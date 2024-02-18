#!/usr/bin/python3

import sys
from random import randrange

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 3:
    print("Usage: ./gen.py num filename \n")
    print("where 1. num - number of elements \n")
    print("      2. filename - output file name. \n")
    sys.exit(1)

  num = int(argv[1])
  filename = argv[2]

  if num < 2 or num > 23:
    print("Number of elements should be between 2 and 23. \n")
    sys.exit(1)

  return (num, filename)

#------------------

def gen_rand_seq(num: int):
  
  seq = []
  for _ in range(num):
    seq.append(f"{randrange(num) + 1} ")

  return seq

#------------------

def write_to_file(out_file, seq):
  for elem in seq:
    out_file.write(elem)

#==================

num, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:

  out_file.write(f"{num}\n")

  seq = gen_rand_seq(num)
  write_to_file(out_file, seq)
