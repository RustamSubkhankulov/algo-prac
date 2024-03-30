#include <iterator>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

template <typename Type = int>
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

    (void) value;
    ++count_;
    return *this;
  }

  size_t count() { return count_; }
};

int main() {
  
  unsigned n, m;
  std::cin >> n >> m;

  std::vector<std::set<int>> matrix;

  for (unsigned idx = 0; idx < n; ++idx) {

    std::set<int> set;
    std::copy_n(std::istream_iterator<int>(std::cin), m, std::inserter(set, set.end()));

    matrix.push_back(std::move(set));
  }

  size_t max_intersection = 0;
  for (unsigned i = 0; i < n; ++i) {

    for (unsigned j = i+1; j < n; ++j) {

      auto cur_intersection = std::set_intersection(matrix[i].cbegin(), matrix[i].cend(),
                                                    matrix[j].cbegin(), matrix[j].cend(), 
                                                    count_iterator<int>()).count();

      max_intersection = std::max(max_intersection, cur_intersection);
    }
  }

  std::cout << max_intersection;
  return 0;
}

/*

#include <iterator>
#include <vector>
#include <bitset>
#include <iostream>
#include <algorithm>

static const unsigned MOD = 2000000;

int main() {
  
  unsigned n, m;
  std::cin >> n >> m;

  std::vector<std::bitset<2*MOD+1> > sets;

  for (unsigned bitset_idx = 0; bitset_idx < n; ++bitset_idx) {

    std::bitset<2*MOD+1> bitset;

    for (unsigned value_idx = 0; value_idx < m; ++value_idx) {

      int value;
      std::cin >> value;

      bitset.set(value + MOD);
    }

    sets.push_back(std::move(bitset));
  }

  size_t max_intersection = 0;
  for (unsigned i = 0; i < n; ++i) {
    for (unsigned j = i+1; j < n; ++j) {
      max_intersection = std::max(max_intersection, (sets[i] & sets[j]).count());
    }
  }

  std::cout << max_intersection;
  return 0;
}

*/
