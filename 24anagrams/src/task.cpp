#include <unordered_map>
#include <string>
#include <iostream>

int main() {

  unsigned N;
  std::cin >> N;

  std::unordered_map<std::string, unsigned> map;

  for (unsigned idx = 0; idx < N; ++idx) {

    std::string str;
    std::cin >> str;
    std::sort(str.begin(), str.end());

    auto hit = map.find(str);
    
    if (hit == map.end()) {
      map[str] = 1;

    } else {
      hit->second += 1;
    }
  }

  std::cout << map.size() << std::endl;
  return 0;
}