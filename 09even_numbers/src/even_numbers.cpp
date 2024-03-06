#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

static const int Max_starting = 20000000;

int find_min_starting(int num_of_even, int num_total);

int main(const int argc, const char** argv) {
  
  // auto prev_exc_mask = std::cin.exceptions();
  // std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  // int num_of_even, num_total;
  // std::cin >> num_of_even >> num_total;

  // std::cin.exceptions(prev_exc_mask);

  assert(argc >= 3 && "Invalid arguments number.");
  
  int num_of_even = std::stoi(argv[1]);
  int num_total = std::stoi(argv[2]);
  
  assert(num_of_even < num_total && "Even numbers' amound cannot be more than total numbers' amount.");

  std::cout << find_min_starting(num_of_even, num_total);
  return 0;
}

void eval_even_numbers(std::vector<bool>& numbers, std::vector<int>& cache, int n) {

  int ind = 0;
  for (int i = 2; i <= std::round(std::sqrt(n)); ++i) {

    if (numbers[i]) {

      bool is_in_cache = (int)cache.size() > ind;
      int j = std::max((is_in_cache)? cache[ind] : 0, i * i);

      while (j <= n) {
        numbers[j] = false;
        j += i;
      }

      if (!is_in_cache) {
        cache.push_back(j);
      } else {
        cache[ind] = j;
      }

      ind++;
    }
  }
}

int find_min_starting(int num_of_even, int num_total) {

  int starting = 1;
  
  std::vector<bool> numbers(num_total+1, true);
  numbers[0] = false;

  std::vector<int> cache;

  // From zero to num_total
  eval_even_numbers(numbers, cache, num_total);

  int got_num_of_even = 0;
  for (const auto& number : numbers) {
    if (number) {
      got_num_of_even += 1;
    }
  }

  while (starting <= Max_starting) {

    if (got_num_of_even == num_of_even) {
      return starting;
    }

    numbers.push_back(true);
    eval_even_numbers(numbers, cache, ++num_total);

    if (numbers[num_total]) {
      ++got_num_of_even;
    }

    if (numbers[starting++]) {
      --got_num_of_even;
    }
  }

  return -1;
}
