#!/usr/bin/python3

import sys
from random import randrange

#==================

def parse_args(argv):
  """
  Parse sys.argv for arguments of prog.
  """
  if len(argv) != 5:
    print("Usage: ./gen.py max_num num1 num2 filename \n")
    print("where 1. max_num - maximum number that can be generated \n")
    print("      2. num1 and 3. num2 - numbers of elements in each sequence. \n")
    print("      4. filename - output file name. \n")
    sys.exit(1)

  max_num = int(argv[1])
  num1 = int(argv[2])
  num2 = int(argv[3])
  filename = argv[4]

  if max_num < 0:
    print("Maximum number should be positive. \n")
    sys.exit(1)

  if num1 < 0 or num2 < 0:
    print("Numbers of elements should be positive. \n")
    sys.exit(1)

  return (max_num, num1, num2, filename)

#------------------

def gen_seq(max_num: int, num: int, delim: int):
  
  elems = set()
  for _ in range(num):
    elems.add(randrange(max_num) + 1)

  seq = []
  for elem in elems:
    seq.append(f"{elem} ")

  seq.append("0 ")

  return seq

#------------------

def write_to_file(out_file, seq):
  for elem in seq:
    out_file.write(elem)

#==================

max_num, num1, num2, filename = parse_args(sys.argv)

with open(filename, mode = 'w') as out_file:

  delim = 0

  seq = gen_seq(max_num, num1, delim)
  write_to_file(out_file, seq)

  seq = gen_seq(max_num, num2, delim)
  write_to_file(out_file, seq)
