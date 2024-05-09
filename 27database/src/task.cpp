#include <iostream>

#include "database.hpp"

int main() {

  ALGO::DataBase dbase("data.bin");

  unsigned num;
  std::cin >> num;

  for (unsigned idx = 0; idx < num; ++idx) {

    std::string cmnd, key;
    std::cin >> cmnd >> key;

    if (cmnd == "ADD") {

      std::string value;
      std::cin >> value;

      if (!dbase.addEntry(key, value)) {
        std::cout << "ERROR\n";
      }

    } else if (cmnd == "DELETE") {

      if (!dbase.deleteEntry(key)) {
        std::cout << "ERROR\n";
      }

    } else if (cmnd == "UPDATE") {

      std::string value;
      std::cin >> value;

      if (!dbase.updateEntry(key, value)) {
        std::cout << "ERROR\n";
      }

    } else if (cmnd == "PRINT") {

      if (!dbase.printEntry(key, std::cout)) {
        std::cout << "ERROR\n";
      }
    }
  }

  return 0;
}