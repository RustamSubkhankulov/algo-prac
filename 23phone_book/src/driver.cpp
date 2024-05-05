#include <cstdlib>
#include <iostream>

#include "phone_book.hpp"
using namespace PHONE_BOOK;

const static std::string ErrorMsg = "ERROR";

int main() {

  unsigned N;
  std::cin >> N;

  std::string name;
  unsigned number = 0;
  PhoneBook pbook;

  for (unsigned idx = 0; idx < N; ++idx) {

    std::string cmnd;
    std::cin >> cmnd;

    if (cmnd == "ADD") {

      std::cin >> name >> number;

      if (!pbook.addUser(PhoneBook::UserInfo{name, number})) {
        std::cout << ErrorMsg << std::endl;
      }

    } else if (cmnd == "DELETE") {

      std::cin >> name;

      if (!pbook.deleteUser(name)) {
        std::cout << ErrorMsg << std::endl;
      }

    } else if (cmnd == "EDITPHONE") {

      std::cin >> name >> number;

      if (!pbook.editPhoneNumber(PhoneBook::UserInfo{name, number})) {
        std::cout << ErrorMsg << std::endl;
      }

    } else if (cmnd == "PRINT") {

      std::cin >> name;

      if (!pbook.printUser(name, std::cout)) {
        std::cout << ErrorMsg << std::endl;
      }

    } else {

      std::cerr << "Invalid command in input: " << cmnd << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
 
  return 0;
}