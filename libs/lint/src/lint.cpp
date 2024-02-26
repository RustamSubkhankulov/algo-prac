#include <iostream>

#include "lint.hpp"

namespace LONGARITHM {

Lint& Lint::operator+=(const Lint& that) {

  auto max_len = std::max(length(), that.length());
  auto min_len = std::min(length(), that.length());

  bool carrier = false;
  for (int ind = 0; ind < min_len; ++ind) {


  }

  return *this;
}

Lint& Lint::operator-=(const Lint& that) {

  return *this;
}

Lint& Lint::add_digits(const std::deque<char>& that) {

}

Lint& Lint::sub_digits(const std::deque<char>& that) {
  
}

Lint operator+(const Lint& lhs, const Lint& rhs) {

  auto temp{lhs};
  temp += rhs;
  return temp;
}

Lint operator-(const Lint& lhs, const Lint& rhs) {
  
  auto temp{lhs};
  temp -= rhs;
  return temp;
}

}; // namespace LONGARITHM