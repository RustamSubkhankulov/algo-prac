#!/usr/bin/python3

import sys
from random import randrange

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 5:
    print("Usage: ./gen.py degree val_num mod filename \n")
    print("where 1. degree - polynomial degree \n")
    print("      2. val_num - number of values, in which poly will be calculated. \n")
    print("      3. mod - module for calculating values. \n")
    print("      4. filename - output file name. \n")
    sys.exit(1)

  degree = int(argv[1])
  val_num = int(argv[2])
  mod = int(argv[3])
  filename = argv[4]

  if degree < 2 or degree > 100000:
    print("Polynomial degree should be between 2 and 100000. \n")
    sys.exit(1)

  if val_num < 1 or val_num > 100000:
    print("Number of values should be between 1 and 100000. \n")
    sys.exit(1)

  if mod < 10 or mod > 1E9:
    print("Mod should be between 10 and 1E10. \n")
    sys.exit(1)

  return (degree, val_num, mod, filename)

#------------------

def gen_rand_seq(max_val: int, count: int):
  
  seq = []
  for _ in range(count):
    seq.append(f"{randrange(max_val)}\n")

  return seq

#------------------

def write_to_file(out_file, seq):
  for elem in seq:
    out_file.write(elem)

#==================

degree, val_num, mod, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:

  out_file.write(f"{degree} {val_num} {mod}\n")

  max_coeff = max_val = int(1E9)

  seq = gen_rand_seq(max_coeff, degree + 1)
  write_to_file(out_file, seq)

  seq = gen_rand_seq(max_val, val_num)
  write_to_file(out_file, seq)
