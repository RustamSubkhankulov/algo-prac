#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main() {
  
  int num, k;
  std::cin >> num >> k;

  std::vector<int> wires;
  std::copy_n(std::istream_iterator<int>(std::cin), num, std::back_inserter(wires));

  std::sort(std::begin(wires), std::end(wires), std::greater{});

  
}
