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

template<typename IntType = int>
int polycalc_horner(const std::vector<IntType>& coeffs, IntType val);

template<typename IntType = int>
int polycalc_horner_stabilized(const std::vector<IntType>& coeffs, IntType val);

template<typename Type>
Type fast_pow(Type value, int degree);

int main() {

  std::vector<int> coeffs, values;

  auto prev_exc_mask = std::cin.exceptions();
  std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  Run_options run_opts = read_run_options(std::cin);

  read_sequence(std::cin, std::back_inserter(coeffs), run_opts.degree + 1);
  read_sequence(std::cin, std::back_inserter(values), run_opts.val_num);

  std::cin.exceptions(prev_exc_mask);

  for (auto val : values) {

    #if !defined(STAB)
      std::cout << polycalc_horner(coeffs, val) << std::endl;
    #else 
      std::cout << polycalc_horner_stabilized(coeffs, val) << std::endl;
    #endif
  }

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

template<typename IntType>
int polycalc_horner(const std::vector<IntType>& coeffs, IntType val) {

  IntType res = coeffs.back();
  auto size = coeffs.size();

  for (int ind = size - 2; ind >= 0; --ind) {
    res = res * val + coeffs[ind];
  }

  return res;
}

template<typename IntType>
int polycalc_horner_stabilized(const std::vector<IntType>& coeffs, IntType val) {

  auto size = coeffs.size();  

  if (std::abs(val) < 1) {
    return polycalc_horner(coeffs, val);
  }

  float res = (float) coeffs.front();
  float val_inv = 1. / float(val);

  for (int ind = 1; ind < size; ++ind) {
    res = res * val_inv + float(coeffs[ind]);
  }

  return fast_pow(val, size - 1) * res;
}

template<typename Type>
Type fast_pow(Type value, int degree) {

  if (degree == 0) {
    return Type(1);
  }

  if (degree & 1) {
    return fast_pow(value, degree - 1);
  }

  Type med = fast_pow(value, degree >> 2);
  return med * med;
}
