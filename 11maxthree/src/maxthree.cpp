#include <iostream>
#include <vector>
#include <iterator>
#include <utility>
#include <algorithm>

int maxthree1();
int maxthree2(int N);

int main() {

  int N;
  std::cin >> N;

  #ifdef ALGO1
    std::cout << maxthree1();
  #endif

  #ifdef ALGO2
    std::cout << maxthree2(N);
  #endif

  return 0;
}

int maxthree2(int N) {

  std::vector<int> max_heap;
  std::vector<int> min_heap;

  for (int ind = 0; ind < N; ++ind) {

    int temp;
    std::cin >> temp;

    max_heap.push_back(temp);
    std::push_heap(max_heap.begin(), max_heap.end());

    min_heap.push_back(temp);
    std::push_heap(min_heap.begin(), min_heap.end(), std::greater());
  }

  int res1, res2;
  res1 = res2 = max_heap[0];
  std::pop_heap(max_heap.begin(), max_heap.end());

  for (int ind = 0; ind < 2; ++ind) {
    res1 *= max_heap[0];
    std::pop_heap(max_heap.begin(), max_heap.end());
  }

  for (int ind = 0; ind < 2; ++ind) {
    res2 *= min_heap[0];
    std::pop_heap(min_heap.begin(), min_heap.end());
  }

  return std::max(res1, res2);
}

int maxthree1() {

  std::vector<int> vec;
  std::copy(std::istream_iterator<int>(std::cin),
            std::istream_iterator<int>(),
            std::back_inserter(vec));

  std::sort(vec.begin(), vec.end());
  auto size = vec.size();

  return std::max(vec[size-1] * vec[0] * vec[1], 
                  vec[size-1] * vec[size-2] * vec[size-3]);
}
