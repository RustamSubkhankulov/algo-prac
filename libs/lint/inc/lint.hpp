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

  Lint& add_digits(const std::deque<char>& that);
  Lint& sub_digits(const std::deque<char>& that);

  std::deque<char> get_digits() const {
    return digits_;
  }

  template<typename CharT>
  operator std::basic_string<CharT>();

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
};

Lint::Lint(const std::string& str) {

  std::istringstream isstream(str);

  auto prev_exc_mask = isstream.exceptions();
  isstream.exceptions(std::ios_base::badbit);

  char ch;
  isstream >> ch;

  if (isstream.eof()) {
    return; // EOF - empty

  } else if (ch == '-' || ch == '+') {
    is_neg_ = (ch == '-');

  } else if (std::isdigit(ch)) {
    isstream.unget();

  } else {

    isstream.exceptions(prev_exc_mask);
    throw std::invalid_argument("Invalid string in LONGARITHM::Lint ctor: " + str);
  }

  while (isstream.get(ch)) {
    digits_.push_front(ch);
  }

  isstream.exceptions(prev_exc_mask);

  if (!isstream.eof()) {
    throw std::invalid_argument("Invalid string in LONGARITHM::Lint ctor: " + str);
  }
}

template<typename CharT>
Lint::operator std::basic_string<CharT>() {

  std::stringstream buf;

  if (length() == 0) {

    buf << '0';
    return buf.str();
  }

  if (is_neg_) {
    buf << '-';
  }

  std::copy(std::rbegin(digits_), std::rend(digits_), std::ostream_iterator<char>(buf));
  return buf.str();
}

template<typename CharT>
std::basic_istream<CharT>& operator>>(std::basic_istream<CharT>& is, Lint& lint) {

  std::basic_string<CharT> str;
  std::getline(is, str);

  std::cout << "string read: " << str << std::endl;

  lint = str;
  return is;
}

template<typename CharT>
std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, Lint& lint) {

  os << std::basic_string<CharT>(lint);
  return os;
}

Lint operator+(const Lint& lhs, const Lint& rhs);
Lint operator-(const Lint& lhs, const Lint& rhs);

}; // namespace LONGARITHM

#endif