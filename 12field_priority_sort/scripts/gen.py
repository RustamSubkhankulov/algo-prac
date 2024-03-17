#!/usr/bin/python3

import sys
import string
from random import randrange, randint, shuffle, choice

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 4:
    print("Usage: ./gen.py num k filename \n")
    sys.exit(1)

  num = int(argv[1])
  k = int(argv[2])
  filename = argv[3]

  if num < 0 or num > 1000:
    print("Domain error: 0 <= num <= 1000 \n")
    sys.exit(1)

  if k < 1 or k > 10:
    print("Domain error: 1 <= k <= 10 \n")
    sys.exit(1)

  return (num, k, filename)

#------------------

def rand_str(len: int) -> str:
  return ''.join(choice(string.ascii_uppercase + string.digits) for _ in range(len))

#------------------

def shuffled_seq(k: int) -> list:

  seq = [i for i in range(1, k+1)]
  shuffle(seq)
  return seq

#------------------

def write_seq(seq, out_file):

  for elem in seq:
    out_file.write(f"{elem} ")
  out_file.write("\n")

#==================

num, k, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:
  
  out_file.write(f"{num}\n")
  out_file.write(f"{k}\n")
  
  write_seq(shuffled_seq(k), out_file)

  for _ in range(num):
    out_file.write(f"{rand_str(10)} ")
    write_seq(shuffled_seq(k), out_file)
