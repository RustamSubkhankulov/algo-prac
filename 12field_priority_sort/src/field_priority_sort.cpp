#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

struct Elem_t {

  std::string name;
  std::vector<int> values;
};

void read_elems(int N, int k, std::vector<Elem_t>& elems);
void read_priorities(int k, std::vector<std::pair<int, int>>& priorities);

int main() {

  int N, k;
  std::cin >> N >> k;

  std::vector<std::pair<int, int>> priorities;
  read_priorities(k, priorities);
  std::sort(priorities.begin(), priorities.end(), 
    [](const std::pair<int,int>& lhs, const std::pair<int,int>& rhs)
    { return lhs.first < rhs.first; });

  std::vector<Elem_t> elems;
  read_elems(N, k, elems);

  std::sort(elems.begin(), elems.end(),
    [k, &priorities](const Elem_t& lhs, const Elem_t& rhs) {

      int ind = 0;
      int prior_ind = 0;

      while (ind < k) {
        
        prior_ind = priorities[ind].second;
        if (lhs.values[prior_ind] != rhs.values[prior_ind]) {
          break;
        }

        ++ind;
      }

      return lhs.values[prior_ind] > rhs.values[prior_ind];
    });
  
  for (int ind = 0; ind < N; ++ind) {
    std::cout << elems[ind].name << std::endl;
  }

  return 0;
}

void read_priorities(int k, std::vector<std::pair<int, int>>& priorities) {

  for (int ind = 0; ind < k; ++ind) {

    int temp;
    std::cin >> temp;
    priorities.push_back(std::make_pair(temp, ind));
  }

  return;
}

void read_elems(int N, int k, std::vector<Elem_t>& elems) {

  for (int ind = 0; ind < N; ++ind) {

    std::string name;
    std::cin >> name;

    std::vector<int> values;
    for (int ind = 0; ind < k; ++ind) {

      int temp;
      std::cin >> temp;
      values.push_back(temp);
    }

    elems.push_back({name, values});
  }

  return;
}
