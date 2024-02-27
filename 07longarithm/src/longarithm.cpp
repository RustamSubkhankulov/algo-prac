#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "lint/lint.hpp"
using namespace LONGARITHM;

int main() {

  auto prev_exc_mask = std::cin.exceptions();
  std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  Lint first, second;
  char oper;

  std::cin >> first;
  std::cin >> oper;

  while (std::cin.get() != '\n');

  std::cin >> second;
  std::cin.exceptions(prev_exc_mask);

  if (oper != '+' && oper != '-') {
    throw std::invalid_argument("Operations supported: '+' and '-'");
  }

  Lint res = (oper == '+')? (first + second) : (first - second);

  std::cout << "(" << first << ")" 
            << " " << oper << " " 
            << "(" << second << ")"
            << " = " << res << std::endl;
}
