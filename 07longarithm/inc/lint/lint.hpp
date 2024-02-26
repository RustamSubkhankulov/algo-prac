#ifndef LINT_HPP
#define LINT_HPP

#include <cctype>
#include <cinttypes>
#include <cstddef>
#include <deque>
#include <stdexcept>
#include <utility>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>

namespace LONGARITHM {

class Lint {

// conversions
// compare
// arithm

private:

  std::deque<char> digits_;
  bool is_neg_ = false;

public:

  Lint() {}

  template <typename T>
  Lint(T&& arg, bool is_neg = false):
    digits_(std::forward<T>(arg)),
    is_neg_(is_neg) {}

  Lint(const std::string& str);

  Lint& operator=(const std::string& str) {

    Lint temp(str);
    std::swap(*this, temp);
    return *this;
  }

  Lint& operator+=(const Lint& that);
  Lint& operator-=(const Lint& that);

  std::deque<char> get_digits() const {
    return digits_;
  }

  explicit operator std::string() const;

  using size_type = std::size_t;

  char& operator[] (size_type pos) {
    return digits_[pos];
  }

  const char& operator[](size_type pos) const {
    return digits_[pos];
  }

  size_type length() const {
    return digits_.size();
  }

  bool is_neg() const {
    return is_neg_;
  }

private:

  void swap_sign() {
    is_neg_ = !is_neg_;
  }

  void add_digits(const std::deque<char>& that_digits, size_type that_length);
  void sub_digits(const std::deque<char>& that_digits, size_type that_length);
};

Lint operator+(const Lint& lhs, const Lint& rhs);
Lint operator-(const Lint& lhs, const Lint& rhs);

std::istream& operator>>(std::istream& is, Lint& lint);
std::ostream& operator<<(std::ostream& os, const Lint& lint);

}; // namespace LONGARITHM

#endif