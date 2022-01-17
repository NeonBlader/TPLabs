#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>

void executeFirstTask(std::istream &in, std::ostream &out)
{
  std::set<std::string> words{std::istream_iterator<std::string>(in), std::istream_iterator<std::string>()};
  if (!in.eof()) {
    throw std::ios_base::failure("Error while file's reading");
  }
  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(out, "\n"));
}
