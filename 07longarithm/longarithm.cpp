#include <cstdlib>
#include <exception>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>
#include <iterator>
#include <type_traits>
#include <algorithm>
#include <utility>

template<typename OutputIt, typename CharT = char, typename IntType = int>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, int num);

template<typename InputIt, typename IntType = typename InputIt::value_type>
IntType subarray_maxsum_dumb(InputIt begin, InputIt end);

template<typename InputIt, typename IntType = typename InputIt::value_type>
IntType subarray_maxsum_kadane(InputIt begin, InputIt end);

template<typename IntType>
IntType subarray_maxsum_tab(std::vector<IntType>& values);

int main() {

  std::vector<int> values;

  auto prev_exc_mask = std::cin.exceptions();
  std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  int num;
  std::cin >> num;
  read_sequence(std::cin, std::back_inserter(values), num);

  std::cin.exceptions(prev_exc_mask);

  #if defined(DUMB)
    std::cout << subarray_maxsum_dumb(std::cbegin(values), std::cend(values)) 
              << std::endl;
  
  #elif defined(KADANE)
  std::cout << subarray_maxsum_kadane(std::cbegin(values), std::cend(values)) 
            << std::endl;

  #else
  std::cout << subarray_maxsum_tab(values) 
            << std::endl;

  #endif
}

template<typename OutputIt, typename CharT, typename IntType>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, int num) {

  IntType elem;
  int count = 0;

  while (count++ < num && is >> elem) {
    *dest++ = elem;
  }
}

template<typename InputIt, typename IntType>
IntType subarray_maxsum_dumb(InputIt begin, InputIt end) {

  IntType max_sum = 0;

  for (auto first = begin; first != end; ++first) {

    for (auto last = std::next(first); last != end; ++last) {

      auto cur_sum = std::accumulate(first, last, IntType{});

      if (cur_sum > max_sum) {
        max_sum = cur_sum;
      }
    }
  }

  return max_sum;
}

template<typename InputIt, typename IntType>
IntType subarray_maxsum_kadane(InputIt begin, InputIt end) {

  IntType max_so_far = std::numeric_limits<IntType>::min();
  IntType max_ending_here = 0;

  for (auto first = begin; first != end; ++first) {

    max_ending_here += *first;

    if (max_so_far < max_ending_here) {
      max_so_far = max_ending_here;
    }

    if (max_ending_here < 0) {
      max_ending_here = 0;
    }      
  }

  return max_so_far;
}

template<typename IntType>
IntType subarray_maxsum_tab(std::vector<IntType>& values) {

  std::vector<std::vector<IntType>> tab{2, std::vector<IntType>(values.size())};

  tab[0][0] = tab[0][1] = values[0];

  for (int ind = 1; ind < (int) values.size(); ++ind) {
    tab[1][ind] = std::max(values[ind], values[ind] + tab[1][ind-1]);
    tab[0][ind] = std::max(tab[0][ind-1], tab[1][ind]);
  }

  return tab[0].back();
}
