#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

#include "cyclichash.h"
#include "rabinkarphash.h"

enum PatternEntryType {
  LITERAL,   // any word, e.g. 'FOOBAR'
  WCARD_SYM, // '?'
  WCARD_LIT  // '*'
};

struct PatternEntry {
  PatternEntryType type;
  size_t pos = 0;
  size_t len = 0;
};

size_t findWcard(const std::string& pattern, size_t pos = 0) {

  for (size_t idx = pos; idx < pattern.length(); ++idx) {
    if (pattern[idx] == '?' || pattern[idx] == '*') {
      return idx;
    }
  }
  return std::string::npos;
}

void litOccurInsert(std::unordered_map<size_t, std::vector<size_t>>& litOccur,
  size_t entryIdx, size_t pos) {

  auto hit = litOccur.find(entryIdx);

  if (hit == litOccur.end()) {

    litOccur[entryIdx] = std::vector<size_t>(1, pos);

  } else {
    hit->second.push_back(pos);
  }
}

void fillLitOccur(const std::string& sample, const std::string_view& pattern,
  std::unordered_map<size_t, std::vector<size_t>>& litOccur, 
  const std::vector<PatternEntry>& patternEntries,
  const std::vector<size_t>& entryIdxVec) {

  size_t substrLen = patternEntries[entryIdxVec.front()].len;
  CyclicHash<uint32_t> hf(substrLen);

  /* [hash of literal pattern entry] -> [its index in patternEntries] */
  std::unordered_map<uint32_t, size_t> substr_hash_map;

  for (size_t idx = 0; idx < entryIdxVec.size(); ++idx) {

    const PatternEntry& entry = patternEntries[entryIdxVec[idx]];
    std::string_view lit = pattern.substr(entry.pos, entry.len);

    substr_hash_map[hf.hash(lit)] = entryIdxVec[idx];
  }

  for (size_t sym_idx = 0; sym_idx < substrLen; ++sym_idx) {
    hf.eat(sample[sym_idx]);
  }

  size_t curPos = 0;
  while (curPos != sample.length() - substrLen) {

    auto hit = substr_hash_map.find(hf.hashvalue);
    if (hit != substr_hash_map.end()) {
      litOccurInsert(litOccur, hit->second, curPos);
    }

    hf.update(sample[curPos], sample[curPos + substrLen]);
    ++curPos;
  }
}

void litByLenInsert(std::unordered_map<size_t, std::vector<size_t>>& litByLen,
  size_t entryIdx, size_t litLen) {

  auto hit = litByLen.find(litLen);

  if (hit == litByLen.end()) {

    litByLen[litLen] = std::vector<size_t>(1, entryIdx);

  } else {
    hit->second.push_back(entryIdx);
  }
}

void parsePattern(std::vector<PatternEntry>& patternEntries, 
  std::unordered_map<size_t, std::vector<size_t>>& litByLen,
  const std::string& pattern, size_t pos) {

  size_t curPos = 0;
  size_t patternLen = pattern.length();

  while (curPos != patternLen) {

    if (pos != curPos) {

      size_t litLen;
      bool needABreak = false;

      if (pos == std::string::npos) {

        litLen = patternLen - curPos;
        needABreak = true;
      }

      litLen = pos - curPos;

      patternEntries.push_back({LITERAL, curPos, litLen});
      litByLenInsert(litByLen, patternEntries.size() - 1, litLen);

      if (needABreak) {
        break;
      }
    }

    PatternEntryType type = (pattern[pos] == '?')? WCARD_SYM : WCARD_LIT;
    patternEntries.push_back({type, pos, 1LLU});
  
    curPos = pos + 1;
    pos = findWcard(pattern, curPos);
  }
}

bool matchPattern(const std::string& sample, const std::string& pattern) {

  size_t pos = findWcard(pattern);
  
  if (pos == std::string::npos) {
    return (sample == pattern);
  }

  std::vector<PatternEntry> patternEntries;
  std::unordered_map<size_t, std::vector<size_t>> litByLen;

  /* 
   * Parse pattern into pattern entries 
   * and add literal entries into map litByLen
   * litByLen: [literal pattern entry lenght] -> [vector of such entry indexes]
   */
  parsePattern(patternEntries, litByLen, pattern, pos);

  /* Map [Literal pattern entry index] -> [occurense poisitions vector] */
  std::unordered_map<size_t, std::vector<size_t>> litOccur;

  for (const auto& elem : litByLen) {
    fillLitOccur(sample, pattern, litOccur, patternEntries, elem.second);
  }

  

  return false;
}

int main() {

  std::string sample;
  std::cin >> sample;

  std::string pattern;
  std::cin >> pattern;

  std::cout << ((matchPattern(sample, pattern))? "YES" : "NO") << std::endl;
}