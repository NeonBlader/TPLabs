#include <string>
#include <sstream>

#include <boost/test/unit_test.hpp>
#include "bookmarks.hpp"

const PhoneBook::BookNote CORRECT_NOTE = {"88005553535", "Mark Wolff"};
const PhoneBook::BookNote CORRECT_NOTE2 = {"7760342748", "Van Dark Home"};
const PhoneBook::BookNote CORRECT_NOTE3 = {"72159384512", "Billy Herrington"};
const PhoneBook::BookNote CORRECT_NOTE4 = {"73204295941", "Ricardo Milos"};
const PhoneBook::BookNote CORRECT_NOTE5 = {"733664235236", "Do u know de way"};
const PhoneBook::BookNote NOTE_WITH_INVALID_NUMBER = {"88005trap553535", "Ivanenko Inan"};

const std::string DEFAULT_FIRST_BOOKMARK = {"current"};
const std::string BOOKMARK_NAME = {"First bookmark"};
const std::string BOOKMARK_NAME2 = {"Second bookmark"};
const std::string BOOKMARK_NAME3 = {"Third bookmark"};
const std::string NOT_EXISTING_BOOKMARK = {"This bookmark don't exist"};

const int MAX_STEPS_COUNT = 4;
const int EXTRA_MOVE_FORWARD_STEP = 6;
const int EXTRA_MOVE_BACKWARD_STEP = -6;
const int MAX_COUNT_OF_NOTES = 5;

BOOST_AUTO_TEST_SUITE(bookmarksTests)

  BOOST_AUTO_TEST_CASE(constructorCorrectCurrentBookmarkTest)
  {
    Bookmarks bookmarks;
    auto iter = bookmarks.findBookmark(DEFAULT_FIRST_BOOKMARK);
    BOOST_CHECK(bookmarks.getPhoneBookBegin() == iter->second);
  }

  BOOST_AUTO_TEST_CASE(checkDefaultFirstBookmarkAfterAdd)
  {
    Bookmarks bookmarks;

    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.findBookmark(DEFAULT_FIRST_BOOKMARK);
    BOOST_CHECK(bookmarks.getPhoneBookBegin() == iter->second);

    bookmarks.add(CORRECT_NOTE2);
    iter = bookmarks.findBookmark(DEFAULT_FIRST_BOOKMARK);
    BOOST_CHECK(bookmarks.getPhoneBookBegin() == iter->second);

    bookmarks.add(CORRECT_NOTE3);
    iter = bookmarks.findBookmark(DEFAULT_FIRST_BOOKMARK);
    BOOST_CHECK(bookmarks.getPhoneBookBegin() == iter->second);
  }

  BOOST_AUTO_TEST_CASE(findDefaultBookmarkInEmptyPhonebookNoThrowTest)
  {
    Bookmarks bookmarks;
    BOOST_CHECK_NO_THROW(bookmarks.findBookmark(DEFAULT_FIRST_BOOKMARK));
  }

  BOOST_AUTO_TEST_CASE(findBookmarkNoThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.add(CORRECT_NOTE2);
    bookmarks.add(CORRECT_NOTE3);

    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    iter++;
    bookmarks.addMark(BOOKMARK_NAME2, iter);
    iter++;
    bookmarks.addMark(BOOKMARK_NAME3, iter);

    BOOST_CHECK_NO_THROW(bookmarks.findBookmark(BOOKMARK_NAME));
    BOOST_CHECK_NO_THROW(bookmarks.findBookmark(BOOKMARK_NAME2));
    BOOST_CHECK_NO_THROW(bookmarks.findBookmark(BOOKMARK_NAME3));
  }

  BOOST_AUTO_TEST_CASE(findBookmarkThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.add(CORRECT_NOTE2);
    bookmarks.add(CORRECT_NOTE3);
    BOOST_CHECK_THROW(bookmarks.findBookmark(NOT_EXISTING_BOOKMARK), InvalidBookmarkName);
  }

  BOOST_AUTO_TEST_CASE(addMarkNoThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    BOOST_CHECK_NO_THROW(bookmarks.addMark(BOOKMARK_NAME, iter));
  }

  BOOST_AUTO_TEST_CASE(storeMarkNoThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    BOOST_CHECK_NO_THROW(bookmarks.store(BOOKMARK_NAME, BOOKMARK_NAME2));
  }

  BOOST_AUTO_TEST_CASE(storeMarkThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    BOOST_CHECK_THROW(bookmarks.store(NOT_EXISTING_BOOKMARK, BOOKMARK_NAME2), InvalidBookmarkName);
  }

  BOOST_AUTO_TEST_CASE(storeMarkIsMarkAddedTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    bookmarks.store(BOOKMARK_NAME, BOOKMARK_NAME2);
    BOOST_CHECK_NO_THROW(bookmarks.findBookmark(BOOKMARK_NAME2));
  }

  BOOST_AUTO_TEST_CASE(storeMarkIsMarkAssociatedWithCorrectNoteTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    bookmarks.store(BOOKMARK_NAME, BOOKMARK_NAME2);
    auto firstBookmarkIter = bookmarks.findBookmark(BOOKMARK_NAME);
    auto secondBookmarkIter = bookmarks.findBookmark(BOOKMARK_NAME2);
    BOOST_CHECK(firstBookmarkIter->second == secondBookmarkIter->second);
  }

  BOOST_AUTO_TEST_CASE(insertAfterMarkNoThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    BOOST_CHECK_NO_THROW(bookmarks.insertAfter(BOOKMARK_NAME, CORRECT_NOTE2));
  }

  BOOST_AUTO_TEST_CASE(insertAfterMarkThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    BOOST_CHECK_THROW(bookmarks.insertAfter(NOT_EXISTING_BOOKMARK, CORRECT_NOTE2), InvalidBookmarkName);
  }

  BOOST_AUTO_TEST_CASE(insertAfterMarkIsCorrectNoteAddedTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    bookmarks.insertAfter(BOOKMARK_NAME, CORRECT_NOTE2);
    BOOST_CHECK((std::next(iter)->number_ == CORRECT_NOTE2.number_) && (std::next(iter)->name_ == CORRECT_NOTE2.name_));
  }

  BOOST_AUTO_TEST_CASE(insertBeforeMarkNoThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    BOOST_CHECK_NO_THROW(bookmarks.insertBefore(BOOKMARK_NAME, CORRECT_NOTE2));
  }

  BOOST_AUTO_TEST_CASE(insertBeforeMarkThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    BOOST_CHECK_THROW(bookmarks.insertBefore(NOT_EXISTING_BOOKMARK, CORRECT_NOTE2), InvalidBookmarkName);
  }

  BOOST_AUTO_TEST_CASE(insertBeforeMarkIsCorrectNoteAddedTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    bookmarks.insertBefore(BOOKMARK_NAME, CORRECT_NOTE2);
    BOOST_CHECK((std::prev(iter)->number_ == CORRECT_NOTE2.number_) && (std::prev(iter)->name_ == CORRECT_NOTE2.name_));
  }

  BOOST_AUTO_TEST_CASE(deleteNoteNoThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.add(CORRECT_NOTE2);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    iter++;
    bookmarks.addMark(BOOKMARK_NAME2, iter);

    BOOST_CHECK_NO_THROW(bookmarks.deleteNote(BOOKMARK_NAME));
    BOOST_CHECK_NO_THROW(bookmarks.deleteNote(BOOKMARK_NAME2));
  }

  BOOST_AUTO_TEST_CASE(deleteNoteThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    BOOST_CHECK_THROW(bookmarks.deleteNote(NOT_EXISTING_BOOKMARK), InvalidBookmarkName);
  }

  BOOST_AUTO_TEST_CASE(deleteNoteCorrectMoveToNextNoteTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.add(CORRECT_NOTE2);
    bookmarks.add(CORRECT_NOTE3);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    iter++;
    bookmarks.addMark(BOOKMARK_NAME2, iter);
    iter++;
    bookmarks.addMark(BOOKMARK_NAME3, iter);

    bookmarks.deleteNote(BOOKMARK_NAME);
    auto bookmarkIter = bookmarks.findBookmark(BOOKMARK_NAME);
    BOOST_CHECK((bookmarkIter->second->name_ == CORRECT_NOTE2.name_) && (bookmarkIter->second->number_ == CORRECT_NOTE2.number_));

    bookmarks.deleteNote(BOOKMARK_NAME2);
    bookmarkIter = bookmarks.findBookmark(BOOKMARK_NAME2);
    BOOST_CHECK((bookmarkIter->second->name_ == CORRECT_NOTE3.name_) && (bookmarkIter->second->number_ == CORRECT_NOTE3.number_));
  }

  BOOST_AUTO_TEST_CASE(deleteNoteCorrectMoveToPrevNoteTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.add(CORRECT_NOTE2);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    iter++;
    bookmarks.addMark(BOOKMARK_NAME2, iter);

    bookmarks.deleteNote(BOOKMARK_NAME2);
    auto bookmarkIter = bookmarks.findBookmark(BOOKMARK_NAME2);
    BOOST_CHECK((bookmarkIter->second->name_ == CORRECT_NOTE.name_) && (bookmarkIter->second->number_ == CORRECT_NOTE.number_));
  }

  BOOST_AUTO_TEST_CASE(showMarkNoThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    std::ostringstream out;
    BOOST_CHECK_NO_THROW(bookmarks.show(BOOKMARK_NAME, out));
  }

  BOOST_AUTO_TEST_CASE(showMarkThrowWhenEmptyBookmarksTest)
  {
    Bookmarks bookmarks;
    std::ostringstream out;
    BOOST_CHECK_THROW(bookmarks.show(DEFAULT_FIRST_BOOKMARK, out), PhoneBookUnderflow);
  }

  BOOST_AUTO_TEST_CASE(showMarkThrowWhenInvalidBookmarkNameTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    std::ostringstream out;
    BOOST_CHECK_THROW(bookmarks.show(NOT_EXISTING_BOOKMARK, out), InvalidBookmarkName);
  }

  BOOST_AUTO_TEST_CASE(moveMarkByStepsNoThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.add(CORRECT_NOTE2);
    bookmarks.add(CORRECT_NOTE3);
    bookmarks.add(CORRECT_NOTE4);
    bookmarks.add(CORRECT_NOTE5);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    for (int i = 0; i <= MAX_STEPS_COUNT; ++i) {
      BOOST_CHECK_NO_THROW(bookmarks.move(BOOKMARK_NAME, i));
      BOOST_CHECK_NO_THROW(bookmarks.move(BOOKMARK_NAME, i * -1));
    }
  }

  BOOST_AUTO_TEST_CASE(moveMarkByStepsExtraStepsThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.add(CORRECT_NOTE2);
    bookmarks.add(CORRECT_NOTE3);
    bookmarks.add(CORRECT_NOTE4);
    bookmarks.add(CORRECT_NOTE5);
    bookmarks.addMark(BOOKMARK_NAME, bookmarks.getPhoneBookBegin());
    bookmarks.addMark(BOOKMARK_NAME2, bookmarks.getPhoneBookEnd());
    BOOST_CHECK_THROW(bookmarks.move(BOOKMARK_NAME, EXTRA_MOVE_FORWARD_STEP), std::invalid_argument);
    BOOST_CHECK_THROW(bookmarks.move(BOOKMARK_NAME2, EXTRA_MOVE_BACKWARD_STEP), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(moveMarkByStepsInvalidBookmarkThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.addMark(BOOKMARK_NAME, bookmarks.getPhoneBookBegin());
    BOOST_CHECK_THROW(bookmarks.move(NOT_EXISTING_BOOKMARK, MAX_STEPS_COUNT), InvalidBookmarkName);
  }

  BOOST_AUTO_TEST_CASE(moveMarkByStepsMoveToCorrectNoteTest)
  {
    Bookmarks bookmarks;;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.add(CORRECT_NOTE2);
    bookmarks.add(CORRECT_NOTE3);
    bookmarks.add(CORRECT_NOTE4);
    bookmarks.add(CORRECT_NOTE5);
    bookmarks.addMark(BOOKMARK_NAME, bookmarks.getPhoneBookBegin());

    auto iter = bookmarks.getPhoneBookBegin();
    for (int i = 0; i <= MAX_STEPS_COUNT; ++i) {
      bookmarks.move(BOOKMARK_NAME, i);
      BOOST_CHECK(bookmarks.findBookmark(BOOKMARK_NAME)->second == iter);
      iter++;
      bookmarks.move(BOOKMARK_NAME, i * -1);
      BOOST_CHECK(bookmarks.findBookmark(BOOKMARK_NAME)->second == bookmarks.getPhoneBookBegin());
    }
  }

  BOOST_AUTO_TEST_CASE(moveMarkByBorderNoThrowOneBookmarkTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.addMark(BOOKMARK_NAME, bookmarks.getPhoneBookBegin());
    BOOST_CHECK_NO_THROW(bookmarks.move(BOOKMARK_NAME, Bookmarks::MoveBorders::LAST));
    BOOST_CHECK_NO_THROW(bookmarks.move(BOOKMARK_NAME, Bookmarks::MoveBorders::FIRST));
  }

  BOOST_AUTO_TEST_CASE(moveMarkByBorderNoThrowTest)
  {
    Bookmarks bookmarks;;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.add(CORRECT_NOTE2);
    bookmarks.add(CORRECT_NOTE3);
    auto iter = bookmarks.getPhoneBookBegin();
    bookmarks.addMark(BOOKMARK_NAME, iter);
    iter++;
    bookmarks.addMark(BOOKMARK_NAME2, iter);
    iter++;
    bookmarks.addMark(BOOKMARK_NAME3, iter);

    BOOST_CHECK_NO_THROW(bookmarks.move(BOOKMARK_NAME, Bookmarks::MoveBorders::LAST));
    BOOST_CHECK_NO_THROW(bookmarks.move(BOOKMARK_NAME, Bookmarks::MoveBorders::FIRST));
    BOOST_CHECK_NO_THROW(bookmarks.move(BOOKMARK_NAME2, Bookmarks::MoveBorders::LAST));
    BOOST_CHECK_NO_THROW(bookmarks.move(BOOKMARK_NAME2, Bookmarks::MoveBorders::FIRST));
    BOOST_CHECK_NO_THROW(bookmarks.move(BOOKMARK_NAME3, Bookmarks::MoveBorders::LAST));
    BOOST_CHECK_NO_THROW(bookmarks.move(BOOKMARK_NAME3, Bookmarks::MoveBorders::FIRST));
  }

  BOOST_AUTO_TEST_CASE(moveMarkByBorderInvalidBookmarkThrowTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.addMark(BOOKMARK_NAME, bookmarks.getPhoneBookBegin());
    BOOST_CHECK_THROW(bookmarks.move(NOT_EXISTING_BOOKMARK, Bookmarks::MoveBorders::LAST), InvalidBookmarkName);
  }

  BOOST_AUTO_TEST_CASE(moveMarkByBorderCorrectMoveTest)
  {
    Bookmarks bookmarks;
    bookmarks.add(CORRECT_NOTE);
    bookmarks.add(CORRECT_NOTE2);
    bookmarks.add(CORRECT_NOTE3);
    auto iter = std::next(bookmarks.getPhoneBookBegin());
    bookmarks.addMark(BOOKMARK_NAME, iter);

    bookmarks.move(BOOKMARK_NAME, Bookmarks::MoveBorders::LAST);
    BOOST_CHECK(bookmarks.findBookmark(BOOKMARK_NAME)->second == std::prev(bookmarks.getPhoneBookEnd()));

    bookmarks.move(BOOKMARK_NAME, Bookmarks::MoveBorders::FIRST);
    BOOST_CHECK(bookmarks.findBookmark(BOOKMARK_NAME)->second == bookmarks.getPhoneBookBegin());
  }

BOOST_AUTO_TEST_SUITE_END()
