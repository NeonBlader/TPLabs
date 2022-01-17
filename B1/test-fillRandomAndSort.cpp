#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <vector>

void fillRandomAndSort(const char *direction, std::size_t vectorSize, std::ostream &out = std::cout);

const std::size_t VECTOR_SIZE = 10;

BOOST_AUTO_TEST_SUITE(fillRandomAndSortTests)

  BOOST_AUTO_TEST_CASE(nullptrDirectionTest)
  {
    BOOST_CHECK_THROW(fillRandomAndSort(nullptr, VECTOR_SIZE), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(correctParametersNoThrowTest)
  {
    BOOST_CHECK_NO_THROW(fillRandomAndSort("ascending", VECTOR_SIZE));
  }

  BOOST_AUTO_TEST_CASE(correctAscendingSortTest)
  {
    std::ostringstream out;
    fillRandomAndSort("ascending", VECTOR_SIZE, out);
    std::vector<double> outputData;
    std::istringstream in;
    in.str(out.str());
    in.ignore(1000, '\n');
    double outputValue;
    while (!in.eof()) {
      in >> outputValue;
      outputData.push_back(outputValue);
    }
    for (std::size_t i = 1; i < VECTOR_SIZE; ++i) {
      BOOST_CHECK(outputData[i] > outputData[i - 1]);
    }
  }

    BOOST_AUTO_TEST_CASE(correctDescendingSortTest)
    {
      std::ostringstream out;
      fillRandomAndSort("descending", VECTOR_SIZE, out);
      std::vector<double> outputData;
      std::istringstream in;
      in.str(out.str());
      in.ignore(1000, '\n');
      double outputValue;
      while (!in.eof()) {
        in >> outputValue;
        outputData.push_back(outputValue);
      }
      for (std::size_t i = 1; i < VECTOR_SIZE; ++i) {
        BOOST_CHECK(outputData[i] < outputData[i - 1]);
      }
    }

BOOST_AUTO_TEST_SUITE_END()
