#include <iostream>
#include <string>
#include <unordered_map>

size_t substr_len_weight(const std::string& string, size_t substr_len);

int main() {

  std::string string;
  std::cin >> string;

  size_t len = string.length();
  size_t max_weight = len;

  for (size_t substr_len = len - 1; substr_len > 0; --substr_len) {

    size_t cur_weight = substr_len_weight(string, substr_len);

    if (cur_weight > max_weight) {
      max_weight = cur_weight;
    }
  }

  std::cout << max_weight << std::endl;

  return 0;
}

size_t substr_len_weight(const std::string& string, size_t substr_len) {

  size_t substr_num = string.length() - substr_len + 1;
  std::unordered_map<std::string, size_t> substr_table;
  size_t max_count = 1;

  for (size_t substr_idx = 0; substr_idx < substr_num; ++substr_idx) {

    const auto& substr = string.substr(substr_idx, substr_len);
    auto hit = substr_table.find(substr);

    if (hit == substr_table.end()) {

      substr_table[substr] = 1;

    } else {

      hit->second += 1;
      if (hit->second > max_count) {
        max_count = hit->second;
      }
    }
  }
  
  return max_count * substr_len;
}