#include <iostream>
#include <vector>

int main() {

  unsigned N, K, M, L;
  std::cin >> N >> K >> M >> L;

  std::vector<unsigned> vec;
  vec.push_back(K);

  for (unsigned i = 0; i < N-1; ++i) {
    vec.push_back((unsigned)((vec[i]*(unsigned long long)M)&0xFFFFFFFFU)%L);
  }

  std::sort(vec.begin(), vec.end());

  unsigned sum = 0;
  for (unsigned ind = 0; ind < N; ++ind) {

    if ((ind % 2) == 0) {
      sum = (sum + vec[ind]) % L;
    }
  }

  std::cout << sum;
  return 0;
}