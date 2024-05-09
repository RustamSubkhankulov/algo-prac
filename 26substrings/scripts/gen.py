#!/usr/bin/python3

import sys
import string
from random import randrange, choice

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 3:
    print("Usage: ./gen.py N filename \n")
    sys.exit(1)

  N = int(argv[1])
  filename = argv[2]

  if N < 1 or N > 10000:
    print("Domain error: 1 <= N <= 10000 \n")
    sys.exit(1)

  return (N, filename)

#------------------

def gen_rand_string(len: int) -> str:
  return ''.join(choice(string.ascii_lowercase) for _ in range(len))

#==================

N, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:
  out_file.write(f"{gen_rand_string(N)} \n")
