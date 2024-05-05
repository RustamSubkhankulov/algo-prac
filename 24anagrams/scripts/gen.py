#!/usr/bin/python3

import sys
import string
from random import randrange, choice

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 4:
    print("Usage: ./gen.py N L filename \n")
    sys.exit(1)

  N = int(argv[1])
  L = int(argv[2])
  filename = argv[3]

  if N < 1 or N > 10000:
    print("Domain error: 1 <= N <= 10000 \n")
    sys.exit(1)

  if L < 1 or L > 10000:
    print("Domain error: 1 <= L <= 10000 \n")
    sys.exit(1)

  return (N, L, filename)

#------------------

def gen_rand_string(len: int) -> str:
  return ''.join(choice(string.ascii_uppercase) for _ in range(len))

#==================

N, L, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:
  
  out_file.write(f"{N} \n")

  for _ in range(N):
    out_file.write(f"{gen_rand_string(L)} \n")
