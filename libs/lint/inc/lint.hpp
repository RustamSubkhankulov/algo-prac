#ifndef LINT_HPP
#define LINT_HPP

#include <cctype>
#include <cstddef>
#include <deque>
#include <stdexcept>
#include <utility>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>

// namespace LONGARITHM {

class Lint {

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
  isstream.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  char ch;
  isstream >> ch;

  if (!isstream) {
    return; // EOF - empty

  } else if (ch == '-') {
    is_neg_ = true;

  } else if (ch == '+') {
    is_neg_ = false;

  } else if (std::isdigit(ch)) {
    isstream.unget();

  } else {

    isstream.exceptions(prev_exc_mask);
    throw std::invalid_argument("Invalid string in LONGARITHM::Lint ctor: " + str);
  }

  std::copy(std::istream_iterator<char>(isstream), 
            std::istream_iterator<char>(),
            std::front_inserter(digits_));

  isstream.exceptions(prev_exc_mask);
}

template<typename CharT>
Lint::operator std::basic_string<CharT>() {

  std::string str;
  std::ostringstream osstream(str);

  if (length() == 0) {

    osstream << '0';
    return str;
  }

  if (is_neg_) {
    osstream << '-';
  }

  std::copy(std::begin(digits_), std::end(digits_), std::ostream_iterator<char>(osstream));
  return str;
}

template<typename CharT>
std::basic_istream<CharT>& operator>>(std::basic_istream<CharT>& is, Lint& lint) {

  std::basic_string<CharT> str;
  std::getline(is, str);

  lint = str;
  return is;
}

template<typename CharT>
std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, Lint& lint) {

  os << std::basic_string<CharT>(lint);
  return os;
}

// }; // namespace LONGARITHM

#endif