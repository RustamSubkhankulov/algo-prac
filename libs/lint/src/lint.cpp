#include <algorithm>
#include <iostream>
#include <string>

#include "lint.hpp"

namespace LONGARITHM {

Lint& Lint::operator+=(const Lint& that) {

  std::cout << is_neg_ << " " << that.is_neg_ << "\n";

  if ((!is_neg_ && that.is_neg_) || (is_neg_ && !that.is_neg_)) {
    sub_digits(that.digits_, that.length());
  }

  add_digits(that.digits_, that.length());

  std::cout << "res of operation: " << std::string(*this) << std::endl;

  return *this;
}

Lint& Lint::operator-=(const Lint& that) {

  if ((!is_neg_ && that.is_neg_) || (is_neg_ && !that.is_neg_)) {
    add_digits(that.digits_, that.length());
  }

  sub_digits(that.digits_, that.length());
  return *this;
}

void Lint::add_digits(const std::deque<char>& that_digits, size_type that_length) {

  int max_len, min_len;
  bool this_longer = (length() > that_length);

  std::cout << "length: " << length() << " that.length(): " << that_length << "\n";

  if (this_longer) {

    max_len = length();
    min_len = that_length;

  } else {

    max_len = that_length;
    min_len = length();
  }

  bool carrier = false;
  for (int ind = 0; ind < min_len; ++ind) {

    char digit = digits_[ind] + that_digits[ind] + carrier;

    std::cout << "[" << ind << "]: " << char(digits_[ind] + '0') << " + " << char(that_digits[ind] + '0') << " = " << std::to_string(digit) << "\n";

    digits_[ind] = digit % 10;
    carrier = digit / 10;
  }

  if (!this_longer) {

    if (!(length() < that_length) && carrier) {
      digits_.push_back(1);

    } else {

      for (int ind = min_len; ind < max_len; ++ind) {
        digits_.push_back(that_digits[ind]);
      }

      digits_[min_len] += carrier;
    }
  }
}

void Lint::sub_digits(const std::deque<char>& that_digits, size_type that_length) {

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

std::ostream& operator<<(std::ostream& os, const Lint& lint) {

  os << std::string(lint);
  return os;
}

std::istream& operator>>(std::istream& is, Lint& lint) {

  std::string str;
  std::getline(is, str);

  lint = str;
  return is;
}

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
    digits_.push_front(ch - '0');
  }

  isstream.exceptions(prev_exc_mask);

  if (!isstream.eof()) {
    throw std::invalid_argument("Invalid string in LONGARITHM::Lint ctor: " + str);
  }
}

Lint::operator std::string() const {

  std::stringstream buf;

  if (length() == 0) {

    buf << '0';
    return buf.str();
  }

  if (is_neg_) {
    buf << '-';
  }

  auto l = [](const char& ch){ return ch + '0'; };

  std::transform(std::rbegin(digits_), std::rend(digits_), std::ostream_iterator<char>(buf), l);
  return buf.str();
}

}; // namespace LONGARITHM