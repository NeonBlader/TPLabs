#include "bookmarks.hpp"

Bookmarks::Bookmarks()
{
  bookmarks_.emplace("current", phoneBook_.begin());
}

void Bookmarks::add(const PhoneBook::BookNote &note)
{
  phoneBook_.pushBack(note);
  if (phoneBook_.size() == 1) {
    for (auto iter = bookmarks_.begin();  iter != bookmarks_.end(); iter++) {
      iter->second = phoneBook_.begin();
    }
  }
}

void Bookmarks::store(const std::string &markName, const std::string &newMarkName)
{
  auto iter = findBookmark(markName);
  bookmarks_.emplace(newMarkName, iter->second);
}

void Bookmarks::insertAfter(const std::string &markName, const PhoneBook::BookNote &note)
{
  auto iter = findBookmark(markName);
  if (phoneBook_.size() == 0) {
    add(note);
  } else {
    phoneBook_.insertAfter(iter->second, note);
  }
}

void Bookmarks::insertBefore(const std::string &markName, const PhoneBook::BookNote &note)
{
  auto iter = findBookmark(markName);
  if (phoneBook_.size() == 0) {
    add(note);
  } else {
    phoneBook_.insertBefore(iter->second, note);
  }
}

void Bookmarks::deleteNote(const std::string &markName)
{
  auto iter = findBookmark(markName);
  if (iter == bookmarks_.end()) {
    throw InvalidBookmarkName();
  }
  if (phoneBook_.size() == 0) {
    throw PhoneBookUnderflow();
  }
  auto noteIter = iter->second;
  for (auto current = bookmarks_.begin(); current != bookmarks_.end(); current++) {
    if (current->second == noteIter) {
      if (std::next(current->second) != phoneBook_.end()) {
        current->second = std::next(noteIter);
      } else {
        current->second = std::prev(noteIter);
      }
    }
  }
  phoneBook_.erase(noteIter);
}

void Bookmarks::show(const std::string &markName, std::ostream &out) const
{
  const auto iter = bookmarks_.find(markName);
  if (iter == bookmarks_.cend()) {
    throw InvalidBookmarkName();
  }
  if (phoneBook_.size() == 0) {
    throw PhoneBookUnderflow();
  }
  if (iter->second != phoneBook_.cend()) {
    out << (iter->second);
  }
}

void Bookmarks::move(const std::string &bookmark, int stepsCount)
{
  auto iter = findBookmark(bookmark);
  iter->second = phoneBook_.move(iter->second, stepsCount);
}

void Bookmarks::move(const std::string &bookmark, const Bookmarks::MoveBorders &border)
{
  auto iter = findBookmark(bookmark);
  if (border == MoveBorders::FIRST) {
    iter->second = phoneBook_.begin();
  } else {
    iter->second = std::prev(phoneBook_.end());
  }
}

std::map<std::string, std::list<PhoneBook::BookNote>::iterator>::iterator Bookmarks::findBookmark(const std::string &markName)
{
  auto iter = bookmarks_.find(markName);
  if (iter == bookmarks_.end()) {
    throw InvalidBookmarkName();
  }
  return iter;
}

void Bookmarks::addMark(const std::string &markName, const std::list<PhoneBook::BookNote>::iterator iter)
{
  bookmarks_.emplace(markName, iter);
}

std::list<PhoneBook::BookNote>::iterator Bookmarks::getPhoneBookBegin()
{
  return phoneBook_.begin();
}

std::list<PhoneBook::BookNote>::iterator Bookmarks::getPhoneBookEnd()
{
  return phoneBook_.end();
}
