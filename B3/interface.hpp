#ifndef B3_INTERFACE_HPP
#define B3_INTERFACE_HPP

#include <functional>
#include <string>
#include <iosfwd>

#include "phoneBook.hpp"
#include "bookmarks.hpp"

std::function<void(Bookmarks &bookmarks, std::ostream &out)> handleCommand(std::istream &in);

std::function<void(Bookmarks &bookmarks, std::ostream &out)> add(std::istream& in);
std::function<void(Bookmarks &bookmarks, std::ostream &out)> store(std::istream& in);
std::function<void(Bookmarks &bookmarks, std::ostream &out)> insert(std::istream& in);
std::function<void(Bookmarks &bookmarks, std::ostream &out)> deleteMark(std::istream& in);
std::function<void(Bookmarks &bookmarks, std::ostream &out)> show(std::istream& in);
std::function<void(Bookmarks &bookmarks, std::ostream &out)> move(std::istream& in);

#endif //B3_INTERFACE_HPP
