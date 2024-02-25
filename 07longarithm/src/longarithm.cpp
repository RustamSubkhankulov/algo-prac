#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <utility>

#include "lint/lint.hpp"
// using namespace LONGARITHM;

int main() {

  std::vector<int> values;

  auto prev_exc_mask = std::cin.exceptions();
  std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  Lint first, second;
  char oper;

  std::cin >> first >> oper >> second;
  if (oper != '+' && oper != '-') {
    throw std::invalid_argument("Operations supported: '+' and '-'");
  }

  std::cin.exceptions(prev_exc_mask);

  // Lint res = first + second;
  std::cout << "First: "  << first  << std::endl;
  std::cout << "Second: " << second << std::endl;
  // std::cout << res;
}
