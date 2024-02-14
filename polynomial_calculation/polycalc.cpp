#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>
#include <iterator>
#include <type_traits>
#include <algorithm>
#include <utility>

struct Run_options {

  int degree;
  int val_num;
  int mod;
};

template<typename CharT = char>
Run_options read_run_options(std::basic_istream<CharT>& is);

template<typename OutputIt, typename CharT = char, typename IntType = int>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, int num);

int main() {

  std::vector<int> coeffs, values;

  auto prev_exc_mask = std::cin.exceptions();
  std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  Run_options run_opts = read_run_options(std::cin);

  read_sequence(std::cin, std::back_inserter(coeffs), run_opts.degree + 1);
  read_sequence(std::cin, std::back_inserter(values), run_opts.val_num);

  std::cin.exceptions(prev_exc_mask);
  return 0;
}

template<typename CharT>
Run_options read_run_options(std::basic_istream<CharT>& is){

  int degree, val_num, mod;

  if (!(std::cin >> degree >> val_num >> mod)) {

    std::cerr << "Invalid input format" << std::endl;
    exit(EXIT_FAILURE);
  }

  return {degree, val_num, mod};
}

template<typename OutputIt, typename CharT, typename IntType>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, int num) {

  IntType elem;
  size_t count = 0;

  while (count++ < num && is >> elem) {
    *dest++ = elem;
  }
}
