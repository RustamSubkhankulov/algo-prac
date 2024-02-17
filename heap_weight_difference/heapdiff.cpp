#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>
#include <iterator>
#include <type_traits>
#include <algorithm>
#include <utility>

using std::size_t;

template<typename OutputIt, typename CharT = char, typename IntType = int>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, size_t num);

template<typename InputIt, typename IntType = int>
IntType heapdiff(InputIt begin, InputIt end);

int main() {

  std::vector<int> weights;

  auto prev_exc_mask = std::cin.exceptions();
  std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  int num;
  std::cin >> num;
  read_sequence(std::cin, std::back_inserter(weights), num);

  std::cin.exceptions(prev_exc_mask);

  std::cout << heapdiff(std::begin(weights), std::end(weights)) << std::endl;
}

template<typename OutputIt, typename CharT, typename IntType>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, size_t num) {

  IntType elem, prev;
  size_t count = 0;

  if (count++ < num && is >> prev) {
    *dest++ = prev;
  }

  while (count++ < num && is >> elem) {
    
    if (elem != prev) {
      *dest = prev = elem;
    }

    ++dest;
  }
}

template<typename InputIt, typename IntType>
IntType heapdiff(InputIt begin, InputIt end) {

  return 0;
}
