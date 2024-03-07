#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

std::string fraction_to_str(int dividend, int divisor);

int main(const int argc, const char** argv) {
  
  // auto prev_exc_mask = std::cin.exceptions();
  // std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

  // int dividend, divisor;
  // std::cin >> dividend >> divisor;

  // std::cin.exceptions(prev_exc_mask);

  assert(argc >= 3 && "Invalid arguments number.");
  
  int dividend = std::stoi(argv[1]);
  int divisor = std::stoi(argv[2]);
  
  assert(divisor && "Divisor must be non-zero.");
  assert(dividend < divisor && "Dividend should be less than divisor.");

  assert(dividend >= 1 && "Dividend >= 1.");
  assert(dividend < 150000000 && "Dividend < 150000000.");
  
  assert(divisor >= 1 && "Divisor >= 1.");
  assert(divisor < 150000000 && "Divisor < 150000000.");

  std::cout << fraction_to_str(dividend, divisor) << std::endl;
  return 0;
}

std::string fraction_to_str(int dividend, int divisor) {
  
  std::unordered_map<int, int> remainders_pos;  

  std::string res;
  int pos = 0;

  int remainder = dividend;

  while (remainder != 0 
      && remainders_pos.find(remainder) == remainders_pos.end()) {

    remainders_pos[remainder] = pos++;

    int tmp = (remainder << 1);
    remainder = (tmp << 2) + tmp;

    res.push_back('0' + remainder / divisor);
    remainder %= divisor;
  }

  if (remainder != 0) {

    res.insert(remainders_pos[remainder], 1, '(');
    res.push_back(')');
  }

  return "0." + res;
}

