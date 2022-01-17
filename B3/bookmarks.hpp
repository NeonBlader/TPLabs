#ifndef B3_BOOKMARKS_HPP
#define B3_BOOKMARKS_HPP

#include <string>
#include <map>

#include "phoneBook.hpp"

class Bookmarks {
public:
  enum MoveBorders
  {
    FIRST,
    LAST
  };

  Bookmarks();

  void add(const PhoneBook::BookNote &note);
  void store(const std::string &markName, const std::string &newMarkName);
  void insertAfter(const std::string &markName, const PhoneBook::BookNote &note);
  void insertBefore(const std::string &markName, const PhoneBook::BookNote &note);
  void deleteNote(const std::string &markName);
  void show(const std::string &bookmark, std::ostream &out) const;
  void move(const std::string &bookmark, int stepsCount);
  void move(const std::string &bookmark, const MoveBorders &border);
  std::map<std::string, std::list<PhoneBook::BookNote>::iterator>::iterator findBookmark(const std::string &markName);
  void addMark(const std::string &markName, const std::list<PhoneBook::BookNote>::iterator iter);
  std::list<PhoneBook::BookNote>::iterator getPhoneBookBegin();
  std::list<PhoneBook::BookNote>::iterator getPhoneBookEnd();

private:
  PhoneBook phoneBook_;
  std::map<std::string, std::list<PhoneBook::BookNote>::iterator> bookmarks_;
};


#endif //B3_BOOKMARKS_HPP
