#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <fstream>
#include <stdexcept>
#include <utility>
#include <unordered_map>
#include <stack>
#include <cassert>

namespace ALGO {

class DataBase {

  std::hash<std::string> hasher;

  std::fstream data;

  static constexpr uint64_t EmptyEntry = 0xFFFFFFFFFFFFFFFF;

  static constexpr size_t HashSize   = 131072U;
  static constexpr size_t DataOffset = sizeof(EmptyEntry) * HashSize;

  static constexpr size_t KeyFieldSize   = 4096U;
  static constexpr size_t KeyFieldOffs   = 0U;

  static constexpr size_t ValueFieldSize = 4096U;
  static constexpr size_t ValueFieldOffs = KeyFieldOffs + KeyFieldSize;

  static constexpr size_t NextFieldSize  = 1024U;
  static constexpr size_t NextFieldOffs  = ValueFieldOffs + ValueFieldSize;

  static constexpr size_t EntrySize = KeyFieldSize + ValueFieldSize + NextFieldSize;

  std::stack<uint64_t> freedIdxStack;
  uint64_t freeIdx = 0;

public:

  DataBase(const std::string& dataFilename) {
    data.open(dataFilename, std::ios::binary 
      | std::ios::in | std::ios::trunc | std::ios::out);

    for (size_t entryIdx = 0; entryIdx < HashSize; ++entryIdx) {

      data.seekp(entryIdx * sizeof(uint64_t));
      if (!data.write(reinterpret_cast<const char*>(&EmptyEntry), sizeof(EmptyEntry))) {
        throw std::runtime_error{"Failed to create databse in " + dataFilename};
      }
    }

    assert(data.good());
  }

  virtual ~DataBase() {
    data.close();
    assert(data.good());
  }

  DataBase            (const DataBase& that) = delete;
  DataBase& operator= (const DataBase& that) = delete;

  DataBase            (DataBase&& that) = delete;
  DataBase& operator= (DataBase&& that) = delete;

  bool addEntry(const std::string& key, const std::string& value) {
    
    uint64_t entry = getEntryFromKeyHash(key);

    if (entry == EmptyEntry) {
      insertEntryNoCollision(hasher(key) % HashSize, key, value);
      return true;
    }

    return insertEntryWithCollision(entry, key, value);
  }  

  bool deleteEntry(const std::string& key) {
    
    uint64_t entry = findEntry(key);
    if (entry == EmptyEntry) {
      return false;
    }

    // deleteEntryImpl(entry);
    return true;
  }

  bool updateEntry(const std::string& key, const std::string& value) {
    
    uint64_t entry = findEntry(key);
    if (entry == EmptyEntry) {
      return false;
    }

    updateEntryImpl(entry, value);
    return true;
  }

  bool printEntry(const std::string& key, std::ostream& os) {
    
    uint64_t entry = findEntry(key);
    std::cout << "Found entry: " << std::hex << entry << std::endl;
    
    if (entry == EmptyEntry) {
      return false;
    }

    printEntryImpl(entry, os);
    return true;
  }

private:

  void updateEntryImpl(uint64_t entry, const std::string& value) {

    size_t entryOffset = DataOffset + entry * EntrySize;
    dataWriteString(entryOffset + ValueFieldOffs, value);
  }

  void deleteEntryImpl(uint64_t prev, uint64_t entry) {
    
    size_t prevEntryOffset = DataOffset + prev * EntrySize;
    size_t entryOffset     = DataOffset + entry * EntrySize;
  }

  uint64_t findEntry(const std::string& key) {

    uint64_t entry = getEntryFromKeyHash(key);
    if (entry == EmptyEntry) {
      return entry;
    }

    return getEntryWithCollision(entry, key);
  }

  void printEntryImpl(uint64_t entry, std::ostream& os) {

    size_t entryOffset = DataOffset + entry * EntrySize;

    std::string key   = dataReadString(entryOffset + KeyFieldOffs);
    std::string value = dataReadString(entryOffset + ValueFieldOffs);

    os << key << " " << value << std::endl;
  }

  uint64_t getEntryFromKeyHash(const std::string& key) {

    data.flush();

    size_t hash = hasher(key) % HashSize;
    data.seekg(hash * sizeof(uint64_t));
    assert(data.good());

    uint64_t entry;
    data.read(reinterpret_cast<char*>(&entry), sizeof(entry));
    assert(data.good());
    
    std::cout << std::hex << "Entry: " << entry << std::endl;
    return entry;
  }

  uint64_t getEntryWithCollision(uint64_t collisionEntryIdx, 
    const std::string& key) {

    uint64_t next = collisionEntryIdx;

    do {

      size_t entryOffset = DataOffset + next * EntrySize;
      std::string collisionKey = dataReadString(entryOffset + KeyFieldOffs);

      if (collisionKey.substr(0, key.length()) == key) {
        return next;
      }

      size_t nextOffset = entryOffset + NextFieldOffs;

      data.seekg(nextOffset);
      assert(data.good());
      data.read(reinterpret_cast<char*>(next), sizeof(uint64_t));
      assert(data.good());

    } while (next != EmptyEntry);

    return next;
  }

  uint64_t getInsertionIdx() {

    uint64_t insertionIdx;
    if (!freedIdxStack.empty()) {

      insertionIdx = freedIdxStack.top();
      freedIdxStack.pop();
    
    } else insertionIdx = freeIdx++;
    return insertionIdx;
  }

  void insertEntry(uint64_t insertionIdx, 
    const std::string& key, const std::string& value) {

    std::cerr << "insertEntry at " << insertionIdx << std::endl;

    size_t entryOffset = DataOffset + insertionIdx * EntrySize;
    std::cout << "entryOffset: 0x" << std::hex << entryOffset << std::endl;
    
    dataWriteString(entryOffset + KeyFieldOffs, key);
    dataWriteString(entryOffset + ValueFieldOffs, value);

    data.seekp(entryOffset + NextFieldOffs);
    assert(data.good());
    
    data.write(reinterpret_cast<const char*>(&EmptyEntry), sizeof(EmptyEntry));
    assert(data.good());
  }

  bool insertEntryNoCollision(size_t hash, 
    const std::string& key, const std::string& value) {

    uint64_t insertionIdx = getInsertionIdx();

    data.seekp(hash * sizeof(uint64_t));
    assert(data.good());
    
    data.write(reinterpret_cast<const char*>(&insertionIdx), sizeof(uint64_t));
    assert(data.good());

    insertEntry(insertionIdx, key, value);
    std::clog << "Inserted \n";
    return true;
  }

  bool insertEntryWithCollision(uint64_t collisionEntryIdx, 
    const std::string& key, const std::string& value) {

    uint64_t next = collisionEntryIdx;
    size_t nextOffset;

    do {

      size_t keyOffset = next * EntrySize + KeyFieldOffs;
      std::string collisionKey = dataReadString(keyOffset);

      if (collisionKey.substr(0, key.length()) == key) {
        return false;
      }

      nextOffset = next * EntrySize + NextFieldOffs;

      data.flush();

      data.seekg(nextOffset);
      assert(data.good());
      data.read(reinterpret_cast<char*>(next), sizeof(uint64_t));
      assert(data.good());

    } while (next != EmptyEntry);

    uint64_t insertionIdx = getInsertionIdx();

    data.seekp(nextOffset);
    assert(data.good());
    
    data.write(reinterpret_cast<const char*>(&insertionIdx), sizeof(uint64_t));
    assert(data.good());

    insertEntry(insertionIdx, key, value);
    return true;
  }

  std::string dataReadString(size_t offset) {

    std::clog << "dataReadString: ";

    data.flush();
    std::string str;
    
    data.seekg(offset);
    assert(data.good());

    char ch;
    do {

      data.read(&ch, sizeof(char));
      assert(data.good());
      str.append(1, ch);

    } while (ch != '\0');

    std::clog << str << std::endl;
    return str;
  }

  void dataWriteString(size_t offset, const std::string& str) {

    std::clog << "dataWriteString: " << str << std::endl;
    std::clog << "offset: 0x" << std::hex << offset << std::endl;

    data.seekp(offset, std::ios_base::seekdir::beg);
    assert(data.good());
    
    data.write(reinterpret_cast<const char*>(str.c_str()), str.length());
    assert(data.good());

    char ch = '\0';
    data.write(&ch, sizeof(char));
    assert(data.good());
  }

};

}; // namespace ALGO

#endif // DATABASE_HPP