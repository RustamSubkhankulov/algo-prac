#include <iostream>

#include "database.hpp"

int main() {

  ALGO::DataBase dbase("data.bin");

  dbase.addEntry("ASDF", "FUCK");
  dbase.printEntry("ASDF", std::cout);

  return 0;
}