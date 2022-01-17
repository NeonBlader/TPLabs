#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <memory>

void readTextAndOut(const char *fileName)
{
  if (fileName == nullptr) {
    throw std::invalid_argument("File name is nullptr");
  }
  std::ifstream in(fileName);
  if (!in.is_open()) {
    throw std::ios_base::failure("Error while opening file");
  }
  const std::size_t RESERVE = 1024;
  std::size_t capacity = RESERVE;
  std::size_t count = 0;
  std::unique_ptr<char[], decltype(free) *> info(static_cast<char *>(malloc(capacity)), &free);
  while (in) {
    in.read(&info[count], RESERVE);
    count += in.gcount();
    if (in.gcount() == RESERVE) {
      capacity += RESERVE;
      std::unique_ptr<char[], decltype(free) *> tmp(static_cast<char *>(realloc(info.get(), capacity)), &free);
      if (tmp == nullptr) {
        in.close();
        throw std::bad_alloc();
      }
      info.release();
      std::swap(info, tmp);
    }
  }
  in.close();
  if (in.is_open()) {
    throw std::ios_base::failure("Error while closing file");
  }
  std::vector<char> vectorInfo(&info[0], &info[count]);
  std::cout.write(&vectorInfo[0], vectorInfo.size());
}
