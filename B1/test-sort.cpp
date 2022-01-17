#include <boost/test/unit_test.hpp>
#include <memory>
#include <forward_list>

#include "sort.hpp"
#include "BracketAppeal.hpp"
#include "AtAppeal.hpp"
#include "IterAppeal.hpp"

const std::vector<int> VECTOR{11, 16, 0, -4, 6, 3, 6, -3, 66, -21};
const std::vector<int> ASCENDING_VECTOR{-21, -4, -3, 0, 3, 6, 6, 11, 16, 66};
const std::vector<int> DESCENDING_VECTOR{66, 16, 11, 6, 6, 3, 0, -3, -4, -21};

const std::forward_list<int> LIST{11, 16, 0, -4, 6, 3, 6, -3, 66, -21};
const std::forward_list<int> ASCENDING_LIST{-21, -4, -3, 0, 3, 6, 6, 11, 16, 66};
const std::forward_list<int> DESCENDING_LIST{66, 16, 11, 6, 6, 3, 0, -3, -4, -21};

void callForCorrectParametersForBracketAppealNoThrowTest(std::vector<int> &vector)
{
  sort<BracketAppeal, std::vector<int>>(vector, SortDirection::ASCENDING);
}

void callForCorrectParametersForAtAppealNoThrowTest(std::vector<int> &vector)
{
  sort<AtAppeal, std::vector<int>>(vector, SortDirection::ASCENDING);
}

void callForCorrectParametersForIterAppealNoThrowTest(std::forward_list<int> &list)
{
  sort<IterAppeal, std::forward_list<int>>(list, SortDirection::ASCENDING);
}

BOOST_AUTO_TEST_SUITE(sortTests)

  BOOST_AUTO_TEST_CASE(correctParametersForBracketAppealNoThrowTest)
  {
    std::vector<int> vector(VECTOR);
    BOOST_CHECK_NO_THROW(callForCorrectParametersForBracketAppealNoThrowTest(vector));
  }

  BOOST_AUTO_TEST_CASE(correctParametersForAtAppealNoThrowTest)
  {
    std::vector<int> vector(VECTOR);
    BOOST_CHECK_NO_THROW(callForCorrectParametersForAtAppealNoThrowTest(vector));
  }

  BOOST_AUTO_TEST_CASE(correctParametersForIterAppealNoThrowTest)
  {
    std::forward_list<int> list(LIST);
    BOOST_CHECK_NO_THROW(callForCorrectParametersForIterAppealNoThrowTest(list));
  }

  BOOST_AUTO_TEST_CASE(correctAscendingBracketAccessSorting)
  {
    std::vector<int> vector(VECTOR);
    sort<BracketAppeal, std::vector<int>>(vector, SortDirection::ASCENDING);
    BOOST_CHECK(vector == ASCENDING_VECTOR);
  }

  BOOST_AUTO_TEST_CASE(correctDescendingBracketAccessSorting)
  {
    std::vector<int> vector(VECTOR);
    sort<BracketAppeal, std::vector<int>>(vector, SortDirection::DESCENDING);
    BOOST_CHECK(vector == DESCENDING_VECTOR);
  }

  BOOST_AUTO_TEST_CASE(correctAscendingAtAccessSorting)
  {
    std::vector<int> vector(VECTOR);
    sort<AtAppeal, std::vector<int>>(vector, SortDirection::ASCENDING);
    BOOST_CHECK(vector == ASCENDING_VECTOR);
  }

  BOOST_AUTO_TEST_CASE(correctDescendingAtAccessSorting)
  {
    std::vector<int> vector(VECTOR);
    sort<AtAppeal, std::vector<int>>(vector, SortDirection::DESCENDING);
    BOOST_CHECK(vector == DESCENDING_VECTOR);
  }

  BOOST_AUTO_TEST_CASE(correctAscendingIterAccessSorting)
  {
    std::forward_list<int> list(LIST);
    sort<IterAppeal, std::forward_list<int>>(list, SortDirection::ASCENDING);
    BOOST_CHECK(list == ASCENDING_LIST);
  }

  BOOST_AUTO_TEST_CASE(correctDescendingIterAccessSorting)
  {
    std::forward_list<int> list(LIST);
    sort<IterAppeal, std::forward_list<int>>(list, SortDirection::DESCENDING);
    BOOST_CHECK(list == DESCENDING_LIST);
  }

BOOST_AUTO_TEST_SUITE_END()
