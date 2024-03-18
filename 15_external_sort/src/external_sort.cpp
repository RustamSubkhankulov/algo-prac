#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <cassert>
#include <cstring>

static const size_t Max_string_size = 10000;

void external_sort(std::ifstream& input, std::fstream& output, std::vector<size_t> line_poses);

int main() {

  std::ifstream input("input.txt");
  std::fstream  output("output.txt");

  std::vector<size_t> line_poses;
  size_t cur_line_start_pos = 0;
  
  char ch;
  while (input.get(ch)) {

    if (ch == '\n') {
      line_poses.push_back(cur_line_start_pos);
      cur_line_start_pos = input.tellg();
    }
  }
  input.clear();

  external_sort(input, output, line_poses);
  return 0;  
}

void external_sort(std::ifstream& input, std::fstream& output, std::vector<size_t> line_poses) {

  auto N = line_poses.size();

  char first [Max_string_size] = { 0 };
  char second[Max_string_size] = { 0 };

  for (size_t series_size = 1; series_size < N; series_size *= 2) {

    for (size_t ind = 0; ind < N/series_size && ind + series_size < N; ++ind) {


      input.seekg(line_poses[ind]);
      input.getline(first, Max_string_size);
      auto first_len = input.gcount();

      input.seekg(line_poses[ind+series_size]);
      input.getline(second, Max_string_size);
      auto second_len = input.gcount();

      if (std::strncmp(first, second, Max_string_size) > 0) {
        std::swap(line_poses[ind], line_poses[ind+series_size]);
      }

      std::memset(first,  0,  first_len);
      std::memset(second, 0, second_len);
    }
  }

  std::string temp;

  for (size_t ind = 0; ind < N; ++ind) {

    input.seekg(line_poses[ind]);
    std::getline(input, temp);
    output << temp << std::endl;
  }
}
