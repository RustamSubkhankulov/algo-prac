#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <unordered_map>
#include <string>
#include <iostream>

namespace PHONE_BOOK {

class PhoneBook {

  std::unordered_map<std::string, unsigned> table_;

public: 

  struct UserInfo {
    std::string name;
    unsigned number;
  };

  PhoneBook() {}

  virtual ~PhoneBook() {}

  bool addUser(const UserInfo& userInfo) {

    auto hit = table_.find(userInfo.name);
    if (hit != table_.end())
      return false;

    table_[userInfo.name] = userInfo.number;
    return true;
  }

  bool deleteUser(const std::string& userName) {

    auto hit = table_.find(userName);
    if (hit == table_.end())
      return false;

    table_.erase(hit);
    return true;
  }

  bool editPhoneNumber(const UserInfo& userInfo) {

    auto hit = table_.find(userInfo.name);
    if (hit == table_.end())
      return false;

    table_[userInfo.name] = userInfo.number;
    return true;
  }

  bool printUser(const std::string& userName, std::ostream& os) {

    auto hit = table_.find(userName);
    if (hit == table_.end())
      return false;

    os << hit->first << " " << hit->second << std::endl;
    return true;
  }
};

}; // namespace PHONE_BOOK

#endif // PHONE_BOOK_HPP