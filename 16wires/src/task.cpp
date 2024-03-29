#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main() {
  
  int num, k;
  std::cin >> num >> k;

  std::vector<int> wires;

  int sum = 0;
  for (int n = 0; n < num; ++n) {

    int temp;
    std::cin >> temp;

    sum += temp;
    wires.push_back(temp);
  }

  std::sort(std::begin(wires), std::end(wires), std::greater{});

  int m = 0, right = sum, left = 0;
  int med = ((right - left) >> 1) + left;

  while (med != left) {

    int count = 0;
    for (int ind = 0; ind < num && wires[ind] >= med; ++ind) {
      count += wires[ind]/med;
    }

    if (count >= k) {

      m = (med > m)? med : m;
      left = med;

    } else {

      right = med;
    }

    med = ((right - left) >> 1) + left;
  }

  std::cout << m;
  return 0;
}
