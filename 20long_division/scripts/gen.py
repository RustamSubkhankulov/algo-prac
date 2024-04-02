#!/usr/bin/python3

import sys
from random import randrange, randint

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 4:
    print("Usage: ./gen.py len1 len2 filename \n")
    print("where 1. len1 - len of the first num \n")
    print("      2. len2 - len of the second num \n")
    print("      3. filename - output file name. \n")
    sys.exit(1)

  len1 = int(argv[1])
  len2 = int(argv[2])
  filename = argv[3]

  if len1 < 1 or len1 > 1000 or len2 < 1 or len2 > 1000:
    print("Length of the number should be between 1 and 1000. \n")
    sys.exit(1)

  return (len1, len2, filename)

#------------------

def gen_rand_longnum(len: int):
  
  seq = []

  seq.append(f"{randrange(1,10)}")
  for _ in range(len):
    seq.append(f"{randrange(0,10)}")

  seq.append("\n")

  return seq

#------------------

def write_to_file(out_file, seq):
  for elem in seq:
    out_file.write(elem)

#==================

len1, len2, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:

  write_to_file(out_file, gen_rand_longnum(len1))
  out_file.write("/\n")
  write_to_file(out_file, gen_rand_longnum(len2))
