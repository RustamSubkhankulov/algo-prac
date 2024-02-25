#ifndef IO_HPP
#define IO_HPP

#include <iostream>

template<typename OutputIt, typename CharT = char, typename IntType = int>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, int num) {

  IntType elem;
  int count = 0;

  while (count++ < num && is >> elem) {
    *dest++ = elem;
  }
}

#endif