#include "dataStruct.hpp"

#include <utility>
#include <iostream>
#include <cstdlib>

#include "streamManipulators.hpp"

const int MAX_KEYS_ABS_VALUE = 5;

std::istream &operator>>(std::istream &in, DataStruct &dataStruct)
{
  std::pair<int, int> keys({0, 0});
  std::pair<char, char> commas({'\0', '\0'});
  std::noskipws(in);
  in >> skipWsOnly >> keys.first >> skipWsOnly >> commas.first >> skipWsOnly >> keys.second >> skipWsOnly >> commas.second;
  if ((std::abs(keys.first) > MAX_KEYS_ABS_VALUE) || (std::abs(keys.second) > MAX_KEYS_ABS_VALUE)
      || (commas.first != ',') || (commas.second != ',')) {
    in.setstate(std::ios_base::failbit);
  }
  if (in.fail()) {
    return in;
  }
  std::string str;
  std::getline(in >> skipWsOnly, str);
  if (str.empty()) {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  dataStruct = {keys.first, keys.second, str};
  return in;
}

std::ostream &operator<<(std::ostream &out, const DataStruct &dataStruct)
{
  out << dataStruct.key1 << ',' << dataStruct.key2 << ',' << dataStruct.str;
  return out;
}

bool operator<(const DataStruct &first, const DataStruct &second)
{
  if (first.key1 != second.key1) {
    return first.key1 < second.key1;
  }
  if (first.key2 != second.key2) {
    return first.key2 < second.key2;
  }
  return first.str.size() < second.str.size();
}
