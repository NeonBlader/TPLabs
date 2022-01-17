#ifndef B4_DATASTRUCT_HPP
#define B4_DATASTRUCT_HPP

#include <string>
#include <iosfwd>

struct DataStruct {
  int key1;
  int key2;
  std::string str;
};

std::istream &operator>>(std::istream &in, DataStruct &dataStruct);
std::ostream &operator<<(std::ostream &out, const DataStruct &dataStruct);
bool operator<(const DataStruct &first, const DataStruct &second);

#endif //B4_DATASTRUCT_HPP
