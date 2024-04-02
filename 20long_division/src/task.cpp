#include <iostream>
#include <algorithm>

#include "lib/lint.h"
using namespace LONGARITHM;

int main() {

  auto prev_exc_mask = std::cin.exceptions();
  std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  Lint first, second;
  char oper;

  std::cin >> first;
  while (std::cin.get() != '\n');
  std::cin >> second;

  std::cin.exceptions(prev_exc_mask);

  std::cout << first << std::endl 
            << "/ \n"
            << second << std::endl
            << first / second << std::endl;
  
  return 0;
}
