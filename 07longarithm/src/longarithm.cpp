#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>
#include <iterator>
#include <utility>

#include "io.hpp"
#include "lint/lint.hpp"

int main() {

  std::vector<int> values;

  auto prev_exc_mask = std::cin.exceptions();
  std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  int num;
  std::cin >> num;
  read_sequence(std::cin, std::back_inserter(values), num);

  std::cin.exceptions(prev_exc_mask);

  foo();
}
