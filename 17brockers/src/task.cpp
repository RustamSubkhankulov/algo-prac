#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdint>
#include <stack>

int main() {
  
  int num;
  std::cin >> num;

  std::vector<int> values;
  std::copy_n(std::istream_iterator<int>(std::cin), num,
              std::back_inserter(values));

  std::sort(values.begin(), values.end(), std::greater{});

  uint64_t percent = 0;
  auto size = values.size();

  while (size >= 3) {
    
    int back    = values[size-1];
    int prev    = values[size-2];
    int preprev = values[size-3];

    int summ;

    if (back + prev < prev + preprev) {

      summ = back + prev;
      values[size-2] = summ;

    } else {

      summ = prev + preprev;
      values[size-3] = values[size-1];
      values[size-2] = summ;
    }

    percent += summ;
    --size;
  }

  percent += values[0] + values[1];

  std::cout << std::setprecision(3) << (float) percent / 100 << std::endl;
  return 0;
}
