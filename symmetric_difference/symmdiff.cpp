#include <exception>
#include <iostream>
#include <set>
#include <iterator>
#include <type_traits>
#include <algorithm>

template<typename OutputIt, typename IntType = int, typename CharT = char>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, IntType delim);

template<typename InputIt1, typename InputIt2, typename OutputIt>
void symmdiff(InputIt1 first1, InputIt1 last1, 
              InputIt2 first2, InputIt2 last2, OutputIt dest);

int main() {

  std::set<int> first, second;
  read_sequence(std::cin, std::inserter(first, first.begin()), 0);
  read_sequence(std::cin, std::inserter(second, second.begin()), 0);

  #if defined(STD)

    std::set_symmetric_difference(
      first.cbegin(), first.cend(),
      second.cbegin(), second.cend(), 
      std::ostream_iterator<int>(std::cout, " "));

  #else 

    symmdiff(
      first.cbegin(), first.cend(),
      second.cbegin(), second.cend(), 
      std::ostream_iterator<int>(std::cout, " "));
  
  #endif 

  return 0;
}

template<typename OutputIt, typename IntType, typename CharT>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, IntType delim) {

  auto prev_exc_mask = is.exceptions();
  is.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  IntType sym;
  while (is >> sym) {

    if (sym == delim) {
      break;
    }

    *dest++ = sym;
  }

  is.exceptions(prev_exc_mask);
}

template<typename InputIt1, typename InputIt2, typename OutputIt>
void symmdiff(InputIt1 first1, InputIt1 last1, 
              InputIt2 first2, InputIt2 last2, OutputIt dest) {

  if (std::distance(first1, last1) == 0) {

    std::copy(first2, last2, dest);
    return;

  } else if (std::distance(first2, last2) == 0) {

    std::copy(first1, last1, dest);
    return;
  } 

  while (first1 != last1 && first2 != last2) {

    auto elem1 = *first1;
    auto elem2 = *first2;

    if (elem1 < elem2) {

      *dest++ = elem1;
      ++first1;

    } else if (elem2 < elem1) {

      *dest++ = elem2;
      ++first2;
    
    } else {

      ++first1;
      ++first2;
    }
  }
}