#include <iostream>

#include "lint.hpp"

namespace LONGARITHM {

Lint& Lint::operator+=(const Lint& that) {

  return *this;
}

Lint& Lint::operator-=(const Lint& that) {

  return *this;
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