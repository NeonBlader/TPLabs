#include "interface.hpp"

#include <map>
#include <iostream>
#include <cctype>
#include <stdexcept>

#include "streamManipulators.hpp"

const std::string INVALID_COMMAND = "<INVALID COMMAND>";
const std::string INVALID_STEP = "<INVALID STEP>";
const std::string EMPTY = "<EMPTY>";
const std::string INVALID_BOOKMARK = "<INVALID BOOKMARK>";

void invalidCommand(Bookmarks&, std::ostream &out)
{
  out << INVALID_COMMAND << '\n';
}

std::string handleName(std::istream &in)
{
  std::string name;
  getline(in >> skipWsOnly, name);
  if (name.empty()) {
    throw std::invalid_argument("Invalid name");
  }
  if ((name.front() != '\"') || (name.back() != '\"')) {
    throw std::invalid_argument("Invalid name");
  }
  name.erase(name.begin());
  name.erase(std::prev(name.end()));
  auto iter = name.begin();
  while (iter != name.end()) {
    if (*iter == '\\') {
      if (((std::next(iter)) == name.end()) || ((*(std::next(iter)) != '\\') && (*(std::next(iter)) != '\"'))) {
        throw std::invalid_argument("Invalid name");
      }
      auto tempIter = iter;
      tempIter++;
      name.erase(iter);
      iter = tempIter;
    } else {
      iter++;
    }
  }
  return name;
}

std::string handleMarkName(std::istream &in)
{
  std::string markName;
  in >> skipWsOnly >> markName;
  if ((!markName.empty()) && (markName.back() == '\r')) {
    markName.pop_back();
  }
  if (markName.empty()) {
    throw std::invalid_argument("Invalid mark name");
  }
  auto iter = markName.begin();
  while (iter != markName.end()) {
    if ((!isalnum(*iter)) && (*iter != '-')) {
      throw std::invalid_argument("Invalid mark name");
    } else {
      iter++;
    }
  }
  return markName;
}

std::function<void(Bookmarks &bookmarks, std::ostream &out)> handleCommand(std::istream &in)
{
  std::map<std::string, std::function<std::function<void(Bookmarks &bookmarks,
      std::ostream& out)>(std::istream&)>> conformity =
  {
    {"add", add},
    {"store", store},
    {"insert", insert},
    {"delete", deleteMark},
    {"show", show},
    {"move", move}
  };

  std::string command;
  in >> std::ws >> command;

  auto iter = conformity.find(command);

  if (iter == conformity.end()) {
    return invalidCommand;
  }
  return iter->second(in);
}

std::function<void(Bookmarks &bookmarks, std::ostream &out)> add(std::istream &in)
{
  std::string number;
  in >> skipWsOnly >> number;
  std::string name;
  try {
    name = handleName(in);
  } catch (const std::invalid_argument&) {
    return invalidCommand;
  }

  return [number, name](Bookmarks &bookmarks, std::ostream &out)
  {
    try {
      bookmarks.add({number, name});
    } catch (const InvalidNumber&) {
      out << INVALID_COMMAND << '\n';
    }
  };
}

std::function<void(Bookmarks &bookmarks, std::ostream &out)> store(std::istream &in)
{
  std::string markName;
  try {
    markName = handleMarkName(in);
  } catch (const std::invalid_argument&) {
    return invalidCommand;
  }

  std::string newMarkName;
  try {
    newMarkName = handleMarkName(in);
  } catch (const std::invalid_argument&) {
    return invalidCommand;
  }

  return [markName, newMarkName](Bookmarks &bookmarks, std::ostream &out)
  {
    try {
      bookmarks.store(markName, newMarkName);
    } catch (const InvalidBookmarkName&) {
      out << INVALID_BOOKMARK << '\n';
    }
  };
}

std::function<void(Bookmarks &bookmarks, std::ostream &out)> insert(std::istream &in)
{
  std::string direction;
  in >> skipWsOnly >> direction;
  std::string markName;
  in >> skipWsOnly >> markName;
  std::string number;
  in >> skipWsOnly >> number;
  std::string name;
  try {
    name = handleName(in);
  } catch (const std::invalid_argument&) {
    return invalidCommand;
  }

  return [direction, markName, number, name](Bookmarks &bookmarks, std::ostream &out)
  {
    try {
      if (direction == "before") {
        bookmarks.insertBefore(markName, {number, name});
      } else if (direction == "after") {
        bookmarks.insertAfter(markName, {number, name});
      } else {
        out << INVALID_COMMAND << '\n';
      }
    } catch (const InvalidBookmarkName&) {
      out << INVALID_BOOKMARK << '\n';
    } catch (const InvalidNumber&) {
      out << INVALID_COMMAND << '\n';
    }
  };
}

std::function<void(Bookmarks &bookmarks, std::ostream &out)> deleteMark(std::istream &in)
{
  std::string markName;
  try {
    markName = handleMarkName(in);
  } catch (const std::invalid_argument&) {
    return invalidCommand;
  }

  return [markName](Bookmarks &bookmarks, std::ostream &out)
  {
    try {
      bookmarks.deleteNote(markName);
    } catch (const InvalidBookmarkName&) {
      out << INVALID_BOOKMARK << '\n';
    }  catch (const PhoneBookUnderflow&) {
      out << EMPTY << '\n';
    }
  };
}

std::function<void(Bookmarks &bookmarks, std::ostream &out)> show(std::istream &in)
{
  std::string markName;
  try {
    markName = handleMarkName(in);
  } catch (const std::invalid_argument&) {
    return invalidCommand;
  }

  return [markName](Bookmarks &bookmarks, std::ostream &out)
  {
    try {
      bookmarks.show(markName, out);
      out << '\n';
    } catch (const InvalidBookmarkName&) {
      out << INVALID_BOOKMARK << '\n';
    } catch (const PhoneBookUnderflow&) {
      out << EMPTY << '\n';
    }
  };
}

std::function<void(Bookmarks &bookmarks, std::ostream &out)> move(std::istream &in)
{
  std::string markName;
  try {
    markName = handleMarkName(in);
  } catch (const std::invalid_argument&) {
    return invalidCommand;
  }
  std::string moveCharacteristic;
  std::getline(in >> skipWsOnly, moveCharacteristic);

  if (moveCharacteristic.empty()) {
    return invalidCommand;
  }
  return [markName, moveCharacteristic](Bookmarks &bookmarks, std::ostream &out)
  {
    if (moveCharacteristic == "first") {
      bookmarks.move(markName, Bookmarks::MoveBorders::FIRST);
    } else if (moveCharacteristic == "last") {
      bookmarks.move(markName, Bookmarks::MoveBorders::LAST);
    } else {
      for (std::size_t i = 0; i < moveCharacteristic.size(); ++i) {
        if (!isdigit(moveCharacteristic[i]) && (moveCharacteristic[0] != '+') && (moveCharacteristic[0] != '-')) {
          out << INVALID_STEP << '\n';
          return;
        }
      }
      try {
        bookmarks.move(markName, std::stoi(moveCharacteristic));
      } catch (const InvalidBookmarkName&) {
        out << INVALID_BOOKMARK << '\n';
      }
    }
  };
}
