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

template<typename CharT = char>
std::pair<size_t, size_t> read_sizes(std::basic_istream<CharT>& is);

template<typename OutputIt, typename CharT = char, typename IntType = int>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, size_t num);

template<typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt multiset_intersection(InputIt1 first1, InputIt1 last1, 
                               InputIt2 first2, InputIt2 last2, OutputIt dest);

template <typename Type>
class count_iterator {

private:

  size_t count_;

public:

  using iterator_category = std::output_iterator_tag;
  using difference_type   = std::ptrdiff_t;
  using value_type        = void; 
  using pointer           = void; 
  using reference         = void; 

  count_iterator(size_t initial = 0):
    count_(initial) {}

  ~count_iterator() {}

  count_iterator& operator*()     { return *this; }
  count_iterator& operator++()    { return *this; }
  count_iterator& operator++(int) { return *this; }

  count_iterator& operator=(const Type& value) {

    ++count_;
    return *this;
  }

  size_t count() { return count_; }
};

int main() {

  std::vector<int> first, second;

  auto prev_exc_mask = std::cin.exceptions();
  std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  std::pair<size_t, size_t> sizes = read_sizes(std::cin);

  read_sequence(std::cin, std::back_inserter(first), sizes.first);
  read_sequence(std::cin, std::back_inserter(second), sizes.second);

  std::cin.exceptions(prev_exc_mask);

  #if defined(STD)

    std::cout << std::set_intersection(
      first.cbegin(), first.cend(),
      second.cbegin(), second.cend(), 
      count_iterator<int>()).count() << std::endl;

  #else 

    std::cout << multiset_intersection(
      first.cbegin(), first.cend(),
      second.cbegin(), second.cend(), 
      count_iterator<int>()).count() << std::endl;
  
  #endif 

  return 0;
}

template<typename CharT>
std::pair<size_t, size_t> read_sizes(std::basic_istream<CharT>& is) {

  std::pair<size_t, size_t> sizes;

  if (!(std::cin >> sizes.first >> sizes.second)) {

    std::cerr << "Invalid input format" << std::endl;
    exit(EXIT_FAILURE);
  }

  return sizes;
}

template<typename OutputIt, typename CharT, typename IntType>
void read_sequence(std::basic_istream<CharT>& is, OutputIt dest, size_t num) {

  IntType elem, prev;
  size_t count = 0;

  if (count++ < num && is >> prev) {
    *dest++ = prev;
  }

  while (count++ < num && is >> elem) {
    
    if (elem != prev) {
      *dest = prev = elem;
    }

    ++dest;
  }
}

template<typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt multiset_intersection(InputIt1 first1, InputIt1 last1, 
                               InputIt2 first2, InputIt2 last2, OutputIt dest) {

  if (first1 == last1) {
    return dest;
  } else if (first2 == last2) {
    return dest;
  }

  while (first1 != last1 && first2 != last2) {

    auto elem1 = *first1;
    auto elem2 = *first2;

    if (elem1 < elem2) {
      ++first1;
    } else if (elem2 < elem1) {
      ++first2;
    } else {
      
      *dest++ = elem1;
      ++first1;
      ++first2;
    }
  }

  return dest;
}
