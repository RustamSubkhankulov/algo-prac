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
    print("Usage: ./gen.py n m k filename \n")
    sys.exit(1)

  n = int(argv[1])
  m = int(argv[2])
  k = int(argv[3])
  filename = argv[4]

  if n < 5 or n > 50000:
    print("Domain error: 5 <= n <= 50000 \n")
    sys.exit(1)

  if m < 3 or m > 1000:
    print("Domain error: 3 <= m <= 1000 \n")
    sys.exit(1)

  if k < 5 or k > 50000:
    print("Domain error: 5 <= k <= 50000 \n")
    sys.exit(1)

  return (n, m, k, filename)

#------------------

def gen_rand_elems(n: int, mod: int) -> list:
  return [f"{randrange(mod)}" for _ in range(n)]

#------------------

def write_seq(seq, out_file):

  for elem in seq:
    out_file.write(f"{elem} ")
  out_file.write("\n")

#==================

n, m, k, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:
  
  out_file.write(f"{n} {m} {k} \n")

  for _ in range(n + k):
    write_seq(gen_rand_elems(m, 10**9-1), out_file)
