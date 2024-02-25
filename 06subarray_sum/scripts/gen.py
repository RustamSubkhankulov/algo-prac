#!/usr/bin/python3

import sys
from random import randrange

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 3:
    print("Usage: ./gen.py num filename \n")
    print("where 1. num - number of elements in array \n")
    print("      2. filename - output file name. \n")
    sys.exit(1)

  num = int(argv[1])
  filename = argv[2]

  if num < 1 or num > 1E8:
    print("Number of elements should be between 1 and 10^8. \n")
    sys.exit(1)

  return (num, filename)

#------------------

def gen_rand_seq(num: int, mod: int):
  
  seq = []
  for _ in range(num):
    seq.append(f"{randrange(-mod,+mod)}\n")

  return seq

#------------------

def write_to_file(out_file, seq):
  for elem in seq:
    out_file.write(elem)

#------------------

def subarray_maxsum(seq) -> int:

  values = [int(elem) for elem in seq]
  size = len(values)
  max_sum = 0

  for i in range(0, size, 1):
    for j in range(i, size, 1):
      
      subarray = values[i:j]
      cur_sum = sum(subarray)

      if cur_sum > max_sum:
        max_sum = cur_sum

  return max_sum

#==================

num, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:

  out_file.write(f"{num}\n")
  mod = int(2E9)

  seq = gen_rand_seq(num, mod)
  write_to_file(out_file, seq)

  # print(f"Subarray max sum is {subarray_maxsum(seq)}")
