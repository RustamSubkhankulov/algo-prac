#!/usr/bin/python3

import sys
import string
from random import randrange

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 5:
    print("Usage: ./gen.py num mod filename \n")
    sys.exit(1)

  num = int(argv[1])
  mod = int(argv[2])
  filename = argv[3]

  if num < 2 or num > 100000:
    print("Domain error: 2 <= num <= 1000000 \n")
    sys.exit(1)

  if mod < 1 or mod > 1000000:
    print("Domain error: 1 <= mod <= 1000000 \n")
    sys.exit(1)

  return (num, mod, filename)

#------------------

def rand_seq(num: int, mod: int) -> list:
  return [f"{randrange(mod)}\n" for _ in range(num)]

#------------------

def write_seq(seq, out_file):

  for elem in seq:
    out_file.write(f"{elem} ")
  out_file.write("\n")

#==================

num, mod, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:
  
  out_file.write(f"{num} \n")
  write_seq(rand_seq(num, mod), out_file)
