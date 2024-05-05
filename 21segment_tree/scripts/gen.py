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

  if n < 10 or n > 500000:
    print("Domain error: 10 <= n <= 500000 \n")
    sys.exit(1)

  if m < 1 or m > 500000:
    print("Domain error: 1 <= m <= 500000 \n")
    sys.exit(1)

  return (n, m, filename)

#------------------

def gen_rand_elems(n: int, mod: int) -> list:
  return [f"{randrange(mod)}" for _ in range(n)]

#------------------

def gen_rand_queries(n: int, m: int, mod: int) -> list:

  queries = []
    
  for _ in range(m):

    query_type = randrange(2) + 1
    if query_type ==  1:
      idx1 = randrange(n)
      idx2 = randrange(n)

      queries.append(f"1 {min(idx1, idx2)} {max(idx1, idx2)}")

    elif query_type == 2:
      idx = randrange(n)
      new_value = randrange(mod)

      queries.append(f"2 {idx} {new_value}")

  return queries

#------------------

def write_seq(seq, out_file):

  for elem in seq:
    out_file.write(f"{elem} \n")
  out_file.write("\n")

#==================

n, m, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:
  
  out_file.write(f"{n} {m} \n")

  write_seq(gen_rand_elems(n, 2**32-1), out_file)
  write_seq(gen_rand_queries(n, m, 2**32-1), out_file)
