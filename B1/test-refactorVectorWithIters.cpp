#include <boost/test/unit_test.hpp>
#include <string>
#include <sstream>
#include <iostream>

void refactorVectorWithIters(std::istream &in = std::cin, std::ostream &out = std::cout);

const std::string IN_WITH_1_AT_THE_END("8 34 12 9 -1 -22 52 1 0");
const std::string IN_WITH_2_AT_THE_END("8 34 12 9 -1 -22 52 2 0");
const std::string IN_WITHOUT_1_OR_2_AT_THE_END("8 34 12 9 -1 -22 52 6 0");
const std::string IN_WITH_NOT_NUMBERS("8 34 12 trap -1 -22 52 2 0");
const std::string IN_WITHOUT_0_AT_THE_END("8 34 12 9 -1 -22 52 2");
const std::string IN_EMPTY;

const std::string OUT_WITH_1_AT_THE_END("9 -1 1 ");
const std::string OUT_WITH_2_AT_THE_END("8 34 12 1 1 1 9 1 1 1 -1 -22 52 2 ");
const std::string OUT_WITHOUT_1_OR_2_AT_THE_END("8 34 12 9 -1 -22 52 6 ");

BOOST_AUTO_TEST_SUITE(refactorVectorWithItersTests)

  BOOST_AUTO_TEST_CASE(inputWithNotNumbersTest)
  {
    std::istringstream in(IN_WITH_NOT_NUMBERS);
    BOOST_CHECK_THROW(refactorVectorWithIters(in), std::ios_base::failure);
  }

  BOOST_AUTO_TEST_CASE(inputWithout0AtTheEndTest)
  {
    std::istringstream in(IN_WITHOUT_0_AT_THE_END);
    BOOST_CHECK_THROW(refactorVectorWithIters(in), std::ios_base::failure);
  }

  BOOST_AUTO_TEST_CASE(correctInputNoThrowTest)
  {
    std::istringstream in(IN_WITH_1_AT_THE_END);
    BOOST_CHECK_NO_THROW(refactorVectorWithIters(in));
  }

  BOOST_AUTO_TEST_CASE(emptyInputNoThrowTest)
  {
    std::istringstream in(IN_EMPTY);
    BOOST_CHECK_NO_THROW(refactorVectorWithIters(in));
  }

  BOOST_AUTO_TEST_CASE(inputWith1AtTheEndTest)
  {
    std::istringstream in(IN_WITH_1_AT_THE_END);
    std::ostringstream out;
    refactorVectorWithIters(in, out);
    BOOST_CHECK(out.str() == OUT_WITH_1_AT_THE_END);
  }

  BOOST_AUTO_TEST_CASE(inputWith2AtTheEndTest)
  {
    std::istringstream in(IN_WITH_2_AT_THE_END);
    std::ostringstream out;
    refactorVectorWithIters(in, out);
    BOOST_CHECK(out.str() == OUT_WITH_2_AT_THE_END);
  }

  BOOST_AUTO_TEST_CASE(inputWithout1Or2AtTheEndTest)
  {
    std::istringstream in(IN_WITHOUT_1_OR_2_AT_THE_END);
    std::ostringstream out;
    refactorVectorWithIters(in, out);
    BOOST_CHECK(out.str() == OUT_WITHOUT_1_OR_2_AT_THE_END);
  }

  BOOST_AUTO_TEST_CASE(emptyInputOutputTest)
  {
    std::istringstream in(IN_EMPTY);
    std::ostringstream out;
    refactorVectorWithIters(in, out);
    BOOST_CHECK(out.str().empty());
  }

BOOST_AUTO_TEST_SUITE_END()
