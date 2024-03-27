#!/usr/bin/python3

import sys
import string
from random import randrange

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 4:
    print("Usage: ./gen.py num mod filename \n")
    sys.exit(1)

  num = int(argv[1])
  mod = int(argv[2])
  filename = argv[3]

  if num < 5 or num > 500000:
    print("Domain error: 5 <= num <= 500000 \n")
    sys.exit(1)

  if mod < -10000 or mod > 10000:
    print("Domain error: -10000 <= mod <= 10000 \n")
    sys.exit(1)

  return (num, mod, filename)

#------------------

def rand_num(mod: int) -> int:
  return randrange(-mod,mod)

#==================

num, mod, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:
  
  out_file.write(f"{num}\n")
  
  for _ in range(num):
    out_file.write(f"{rand_num(mod)} {rand_num(mod)}\n")
