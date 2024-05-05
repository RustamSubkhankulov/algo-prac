#include <iostream>
#include <stdexcept>
#include <vector>
#include <exception>
#include <string>

#include "sum_segtree.hpp"
using namespace ALGO;

int main() {

  unsigned N, M;

  std::cin >> N >> M;

  std::vector<unsigned> data;
  for (unsigned idx = 0; idx < N; ++idx) {

    unsigned val;
    std::cin >> val;

    data.push_back(val);
  } 

  sum_segtree<unsigned> tree(std::move(data));

  for (unsigned idx = 0; idx < M; ++idx) {

    unsigned type;
    
    std::cin >> type;

    switch(type) {

      case 1U: {

        size_t left, right;
        std::cin >> left >> right;

        std::cout << tree.query(left, right) << std::endl;
        break;
      }

      case 2U: {

        size_t index;
        unsigned value;

        std::cin >> index >> value;

        tree.update(index, value);
        break;
      }

      default: throw std::invalid_argument("Invalid query type: " + std::to_string(type));
    }
  }

  return 0;
}