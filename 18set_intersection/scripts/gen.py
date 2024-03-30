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
    print("Usage: ./gen.py n m filename \n")
    sys.exit(1)

  n = int(argv[1])
  m = int(argv[2])
  filename = argv[3]

  if n < 2 or n > 1000:
    print("Domain error: 2 <= n <= 1000 \n")
    sys.exit(1)

  if m < 3 or m > 10000:
    print("Domain error: 3 <= m <= 10000 \n")
    sys.exit(1)

  return (n, m, filename)

#------------------

def rand_seq(num: int, mod: int) -> list:
  return [f"{randrange(mod)}" for _ in range(num)]

#------------------

def write_seq(seq, out_file):

  for elem in seq:
    out_file.write(f"{elem} ")
  out_file.write("\n")

#==================

n, m, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:
  
  out_file.write(f"{n} {m} \n")

  for _ in range(n):
    write_seq(rand_seq(m, 2000000000), out_file)
