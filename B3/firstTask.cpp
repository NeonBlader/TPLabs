#include <iostream>
#include <stdexcept>

#include "bookmarks.hpp"
#include "interface.hpp"

void executeFirstTask(std::istream &in, std::ostream &out)
{
  Bookmarks bookmarks;

  while (in >> std::ws, !in.eof()) {
    handleCommand(in)(bookmarks, out);
  }
  if (!in.eof()) {
    throw std::invalid_argument("Invalid file");
  }
}
