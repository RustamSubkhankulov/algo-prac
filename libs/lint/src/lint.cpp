#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <sstream>
#include <utility>

#include "lint.hpp"

namespace LONGARITHM {

Lint& Lint::operator+=(const Lint& that) {

  if ((!is_neg_ && that.is_neg_) || (is_neg_ && !that.is_neg_)) {
    sub_digits(that.digits_, that.length());

  } else {
    add_digits(that.digits_, that.length());
  }

  return *this;
}

Lint& Lint::operator-=(const Lint& that) {

  if ((!is_neg_ && that.is_neg_) || (is_neg_ && !that.is_neg_)) {
    add_digits(that.digits_, that.length());

  } else {
    sub_digits(that.digits_, that.length());    
  }

  return *this;
}

Lint& Lint::operator/=(const Lint& that) {

  if (that.length() == 0) {
    throw std::overflow_error("Division by zero");
  }

  if (abs_cmp(*this, that) == std::strong_ordering::less) {
    throw std::domain_error("Dividend's module must be greater than divisor's one");
  }
  
  is_neg_ = (is_neg_ != that.is_neg_);
  div_digits(that);
  
  return *this;
}

Lint& Lint::operator*=(int mul) {

  is_neg_ = (is_neg_ != (mul < 0));
  mul = std::abs(mul);

  if (mul == 1) {
    return *this;
  }
  
  if (mul == 0) {

    digits_.clear();
    is_neg_ = false;
    return *this;
  }

  Lint res;

  for (int ind = 0; ind < mul; ind++) {
    res += *this;
  }

  digits_ = res.digits_;
  return *this;
}

int Lint::get_cur_quotient(const Lint& dividend, const Lint& divisor, Lint& mul) {

  if (divisor > dividend) {
    return 0;
  }

  int divd = dividend.digits_.back();
  int divs = divisor.digits_.back();

  int qt_high = divd / divs;

  if (qt_high == 0 && dividend.length() == divisor.length()) {  
      return 0;
  }

  if (qt_high <= 1 && (dividend.length() > divisor.length())) {

    divd = 10 * divd + dividend.digits_[dividend.length() - 2];
    qt_high = divd / divs;
  }

  mul = divisor * qt_high;
  if (dividend >= mul) {
    return qt_high;
  }

  int qt_low  = 1;
  int qt_cur = (qt_high + qt_low) / 2;

  while (qt_low != qt_cur) {

    mul = divisor * qt_cur;

    if (mul > dividend) {
      qt_high = (qt_high + qt_low) / 2;
    
    } else if (mul < dividend) {
      qt_low = (qt_high + qt_low) / 2;
    
    } else {
      return qt_cur;
    }

    qt_cur = (qt_high + qt_low) / 2;
  }

  return qt_cur;
}

void Lint::div_digits(const Lint& divisor) {

  std::deque<char> divd_digits;
  std::deque<char> quotient;

  std::copy(std::rbegin(digits_),
            std::next(std::rbegin(digits_), divisor.length()),
            std::front_inserter(divd_digits));

  Lint cur_divd{std::move(divd_digits), false};

  size_type cur_pos = divisor.length() - 1;

  for (;;) {

    Lint mul;
    int qt = get_cur_quotient(cur_divd, divisor, mul);
    quotient.push_front(qt);

    if (qt != 0) {
      cur_divd -= mul;
    }

    cur_pos += 1;  
    if (cur_pos == length()) {
      break;
    }

    cur_divd.digits_.push_front(digits_[length() - cur_pos - 1]);
    cur_divd.shrink_to_fit();
  }

  digits_ = quotient;
  shrink_to_fit();
}

void Lint::add_digits(const std::deque<char>& that_digits, size_type that_length) {

  if (that_length == 0) {
    return;
  }

  if (length() == 0) {
    digits_ = that_digits;
    return;
  }

  int max_len, min_len;
  bool this_longer = (length() > that_length);

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
  } else if (carrier) {

    if (length() == that_length) {
      digits_.push_back(1);
    } else {
      digits_[min_len] += 1;
    }
  }
}

void Lint::sub_digits(const std::deque<char>& that_digits, size_type that_length) {

  int min_len;
  const std::deque<char> *minuend, *subtrahend;
  bool swap = false;

  if (length() > that_length) {
    min_len = that_length;

  } else {

    min_len = length();
    swap = (length() < that_length) || (digits_[min_len-1] < that_digits[min_len-1]);
  }

  if (swap) {

    swap_sign();
    minuend = &that_digits;
    subtrahend = &digits_;

  } else {

    minuend = &digits_;
    subtrahend = &that_digits;
  }

  std::deque<char> res(min_len, 0);

  for (int ind = 0; ind < min_len; ++ind) {

    char digit = res[ind] + (*minuend)[ind] - (*subtrahend)[ind];

    if (digit < 0) {

      int i = ind + 1;
      while (i < min_len && (*minuend)[i] == 0) {
        ++i;
      }

      if (i != min_len) {

        res[i--] -= 1;

        while (i != ind) {
          res[i--] = 9;
        }

        digit += 10;

      } else {
        
        digit = std::abs(digit);
        swap_sign();
      }
    }

    res[ind] = digit;
  }

  std::swap(this->digits_, res);
  shrink_to_fit();
}

void Lint::shrink_to_fit() {

  for (int ind = length() - 1; ind > 0 && digits_[ind] == 0; --ind) {
    digits_.pop_back();
  }

  if (length() == 0) {
    is_neg_ = false;
  }
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

Lint operator/(const Lint& lhs, const Lint& rhs) {

  auto temp{lhs};
  temp /= rhs;
  return temp;
}

Lint operator*(const Lint& lhs, int mul) {

  auto temp{lhs};
  temp *= mul;
  return temp;
}

std::strong_ordering operator<=> (const Lint& lhs, const Lint& rhs) {

  if (lhs.is_neg() && !rhs.is_neg()) {
    return std::strong_ordering::less;
  }

  if (!lhs.is_neg() && rhs.is_neg()) {
    return std::strong_ordering::less;
  }

  bool both_neg = lhs.is_neg() && rhs.is_neg();

  if (lhs.length() < rhs.length()) {
    return (both_neg)? std::strong_ordering::greater : std::strong_ordering::less;
  }

  if (lhs.length() > rhs.length()) {
    return (both_neg)? std::strong_ordering::less: std::strong_ordering::greater;
  }

  auto length = lhs.length();

  if (!length) {
    return std::strong_ordering::equal;
  }

  for (size_t idx = 0; idx < length; ++idx) {

    if (rhs.digits_[length - 1 - idx] != lhs.digits_[length - 1 - idx]) {

      return (both_neg)? rhs.digits_[length - 1 - idx] <=> lhs.digits_[length - 1 - idx]: 
                         lhs.digits_[length - 1 - idx] <=> rhs.digits_[length - 1 - idx];
    }
  }

  return std::strong_ordering::equal;
}

std::strong_ordering abs_cmp(const Lint& lhs, const Lint& rhs) {

  if (lhs.length() < rhs.length()) {
    return std::strong_ordering::less;
  }

  if (lhs.length() > rhs.length()) {
    return std::strong_ordering::greater;
  }

  auto length = lhs.length();

  if (!length) {
    return std::strong_ordering::equal;
  }

  return lhs.digits_[length - 1] <=> rhs.digits_[length - 1];
}

bool operator== (const Lint& lhs, const Lint& rhs) {
  return (lhs <=> rhs) == std::strong_ordering::equal;
}

bool operator!= (const Lint& lhs, const Lint& rhs) {
  return (lhs <=> rhs) != std::strong_ordering::equal;
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
    char sym = ch - '0';

    if (sym) {
      digits_.push_front(ch - '0');
    }
  }

  isstream.exceptions(prev_exc_mask);

  if (!isstream.eof()) {
    throw std::invalid_argument("Invalid string in LONGARITHM::Lint ctor: " + str);
  }

  if (length() == 0) {
    is_neg_ = false;
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