#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>
#include <iterator>
#include <type_traits>
#include <algorithm>
#include <utility>

using std::size_t;

template<typename OutputIt, typename CharT = char, typename IntType = int>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, int num);

template<typename BidirIt>
typename BidirIt::value_type partition_diff_greedy(BidirIt begin, BidirIt end);

template<typename BidirIt>
typename BidirIt::value_type partition_diff_pseudopoly(BidirIt begin, BidirIt end);

template<typename BidirIt>
typename BidirIt::value_type partition_diff_karmarkara(BidirIt begin, BidirIt end);

int main() {

  std::vector<int> weights;

  auto prev_exc_mask = std::cin.exceptions();
  std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  int num;
  std::cin >> num;
  read_sequence(std::cin, std::back_inserter(weights), num);

  std::cin.exceptions(prev_exc_mask);

  #if defined(GREEDY)

    std::cout << partition_diff_greedy(std::begin(weights), std::end(weights)) 
              << std::endl;

  #elif defined(PSEUDOPOLY)

    std::cout << partition_diff_pseudopoly(std::begin(weights), std::end(weights)) 
              << std::endl;

  #elif defined(KARMARKARA)

    std::cout << partition_diff_karmarkara(std::begin(weights), std::end(weights)) 
              << std::endl;

  #else 

    std::cerr << "None of the options for algorithm type is selected, terminating."
              << std::endl;
    std::abort();

  #endif  
}

template<typename OutputIt, typename CharT, typename IntType>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, int num) {

  IntType elem;
  size_t count = 0;

  while (count++ < num && is >> elem) {
    *dest++ = elem;
  }
}

template<typename BidirIt>
typename BidirIt::value_type partition_diff_greedy(BidirIt begin, BidirIt end) {

  using value_type = typename BidirIt::value_type;
  value_type sum1, sum2;
  sum1 = sum2 = 0;

  auto divide = [&sum1, &sum2](const value_type& value)
                { if (sum1 < sum2) sum1 += value; else sum2 += value; };

  std::for_each(std::reverse_iterator<BidirIt>(end), 
                std::reverse_iterator<BidirIt>(begin), divide);

  return std::abs(sum1 - sum2);
}

template<typename BidirIt>
typename BidirIt::value_type partition_diff_pseudopoly(BidirIt begin, BidirIt end) {

  return 0;
}

template<typename BidirIt>
typename BidirIt::value_type partition_diff_karmarkara(BidirIt begin, BidirIt end) {

  
}
