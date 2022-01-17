#include <sstream>
#include <string>
#include <cstddef>

#include <boost/test/unit_test.hpp>

void executeFirstTask(std::istream &in, std::ostream &out);

const std::string IN1 = "Hm so\nmany\twords   I \n have \t to \n\t insert";
const std::string IN2;

const std::string EMPTY_OUT;

BOOST_AUTO_TEST_SUITE(firstTaskTests)

  BOOST_AUTO_TEST_CASE(firstTaskNoThrowTest)
  {
    std::istringstream in(IN1);
    std::ostringstream out;
    BOOST_CHECK_NO_THROW(executeFirstTask(in, out));
  }

  BOOST_AUTO_TEST_CASE(firstTaskEmptyInputNoThrowTest)
  {
    std::istringstream in(IN2);
    std::ostringstream out;
    BOOST_CHECK_NO_THROW(executeFirstTask(in, out));
  }

  BOOST_AUTO_TEST_CASE(correctnessOfEmtyInputResultsTest)
  {
    std::istringstream in(IN2);
    std::ostringstream out;
    executeFirstTask(in, out);
    BOOST_CHECK(out.str() == EMPTY_OUT);
  }

BOOST_AUTO_TEST_SUITE_END()
