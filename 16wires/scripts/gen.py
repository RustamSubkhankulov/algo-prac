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
    print("Usage: ./gen.py num k mod filename \n")
    sys.exit(1)

  num = int(argv[1])
  k = int(argv[2])
  mod = int(argv[3])
  filename = argv[4]

  if num < 1 or num > 100000:
    print("Domain error: 1 <= num <= 100000 \n")
    sys.exit(1)

  if k < 1 or k > 100000 or k > num:
    print("Domain error: 1 <= k <= 100000; num >= k \n")
    sys.exit(1)

  if mod < 1:
    print("Domain error: 1 <= mod \n")
    sys.exit(1)

  return (num, k, mod, filename)

#------------------

def rand_seq(num: int, mod: int) -> list:
  return [f"{randrange(mod)}\n" for _ in range(num)]

#------------------

def write_seq(seq, out_file):

  for elem in seq:
    out_file.write(f"{elem} ")
  out_file.write("\n")

#==================

num, k, mod, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:
  
  out_file.write(f"{num} {k}\n")
  write_seq(rand_seq(num, mod), out_file)
