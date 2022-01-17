#include "streamManipulators.hpp"

#include <iostream>
#include <cctype>

std::istream& skipWsOnly(std::istream &in)
{
  while (true) {
    char symbol = in.get();
    if ((!isspace(symbol)) || (symbol == '\n')) {
      break;
    }
  }
  if (!in.eof()) {
    in.unget();
  }
  return in;
}
