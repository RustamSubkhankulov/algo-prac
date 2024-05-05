#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <cstdint>
#include <iterator>

std::size_t vec_u32_hash(const std::vector<uint32_t>& vec) {
  
  std::size_t hash = vec.size();
  
  for(auto x : vec) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    hash ^= x + 0x9e3779b9 + (hash << 6) + (hash >> 2);
  }
  
  return hash;
}

int main() {

  unsigned N, M, K;
  std::cin >> N >> M >> K;

  std::vector<std::vector<uint32_t>> reference;
  std::unordered_map<size_t, size_t> reference_table;

  for (unsigned i = 0; i < N; ++i) {

    std::vector<uint32_t> set;
    std::copy_n(std::istream_iterator<uint32_t>(std::cin), M, std::back_inserter(set));
    std::sort(set.begin(), set.end());

    reference_table[vec_u32_hash(set)] = reference.size();
    reference.emplace_back(std::move(set));
  }

  for (unsigned i = 0; i < K; ++i) {

    std::vector<uint32_t> set;
    std::copy_n(std::istream_iterator<uint32_t>(std::cin), M, std::back_inserter(set));
    std::sort(set.begin(), set.end());

    auto hit = reference_table.find(vec_u32_hash(set));

    if (hit != reference_table.end()) {

      const std::vector<uint32_t>& reference_set = reference[hit->second];
      std::cout << std::equal(set.begin(), set.end(), reference_set.begin()) << std::endl;
    
    } else {
      std::cout << 0 << std::endl;
    }
  }

  return 0;
}