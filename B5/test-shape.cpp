#include <sstream>
#include <cstddef>
#include <string>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "shape.hpp"

const Point POINT1 = {5, 16};
const Point POINT2 = {5, 10};
const Point POINT3 = {0, 0};
const Point POINT4 = {4, -2};

const std::size_t SQUARE_DISTANCE_BETWEEN_POINT1_AND_POINT2 = 36;
const std::size_t SQUARE_DISTANCE_BETWEEN_POINT1_AND_POINT3 = 281;
const std::size_t SQUARE_DISTANCE_BETWEEN_POINT1_AND_POINT4 = 325;

const Shape TRIANGLE = {{0, 3}, {5, 3}, {0, 8}};

const Shape INCORRECT_RECTANGLE1 = {{0, 3}, {4, 2}, {4, 5}, {0, 5}};
const Shape INCORRECT_RECTANGLE2 = {{-4, 3}, {4, 2}, {4, 5}, {0, 5}};
const Shape PARALLELOGRAM = {{0, 0}, {2, 3}, {7, 3}, {5, 0}};
const Shape ISOSCELES_TRAPEZOID = {{0, 0}, {1, 3}, {3, 3}, {4, 0}};

const Shape CORRECT_RECTANGLE1 = {{0, 0}, {0, 4}, {6, 4}, {6, 0}};
const Shape CORRECT_RECTANGLE2 = {{2, 0}, {2, 5}, {4, 5}, {4, 0}};
const Shape CORRECT_RECTANGLE3 = {{2, 1}, {0, 3}, {1, 4}, {3, 2}};

const Shape INCORRECT_SQUARE1 = {{2, 1}, {2, 5}, {4, 5}, {5, 1}};
const Shape RHOMBUS = {{3, 1}, {2, 3}, {3, 5}, {4, 3}};
const Shape RECTANGLE = {{0, 0}, {0, 4}, {6, 4}, {6, 0}};

const Shape CORRECT_SQUARE1 = {{2, 1}, {2, 4}, {5, 4}, {5, 1}};
const Shape CORRECT_SQUARE2 = {{-1, -1}, {-1, 0}, {0, 0}, {0, -1}};

BOOST_AUTO_TEST_SUITE(shapeTests)

  BOOST_AUTO_TEST_CASE(getDistanceSquareCorrectnessOfResultsTest)
  {
    BOOST_CHECK(getDistanceSquare(POINT1, POINT1) == 0);
    BOOST_CHECK(getDistanceSquare(POINT1, POINT2) == SQUARE_DISTANCE_BETWEEN_POINT1_AND_POINT2);
    BOOST_CHECK(getDistanceSquare(POINT1, POINT3) == SQUARE_DISTANCE_BETWEEN_POINT1_AND_POINT3);
    BOOST_CHECK(getDistanceSquare(POINT1, POINT4) == SQUARE_DISTANCE_BETWEEN_POINT1_AND_POINT4);
  }

  BOOST_AUTO_TEST_CASE(isRecntagleIncorrectVerticesCountTest)
  {
    BOOST_CHECK(!isRectangle(TRIANGLE));
  }

  BOOST_AUTO_TEST_CASE(isRectangleIncorrectRectanglesTest)
  {
    BOOST_CHECK(!isRectangle(INCORRECT_RECTANGLE1));
    BOOST_CHECK(!isRectangle(INCORRECT_RECTANGLE2));
    BOOST_CHECK(!isRectangle(PARALLELOGRAM));
    BOOST_CHECK(!isRectangle(ISOSCELES_TRAPEZOID));
  }

  BOOST_AUTO_TEST_CASE(isRectangleCorrectRectanglesTest)
  {
    BOOST_CHECK(isRectangle(CORRECT_RECTANGLE1));
    BOOST_CHECK(isRectangle(CORRECT_RECTANGLE2));
    BOOST_CHECK(isRectangle(CORRECT_RECTANGLE3));
  }

  BOOST_AUTO_TEST_CASE(isSquareIncorrectVerticesCountTest)
  {
    BOOST_CHECK(!isSquare(TRIANGLE));
  }

  BOOST_AUTO_TEST_CASE(isSquareIncorrectSquaresTest)
  {
    BOOST_CHECK(!isSquare(INCORRECT_SQUARE1));
    BOOST_CHECK(!isSquare(RHOMBUS));
    BOOST_CHECK(!isSquare(RECTANGLE));
  }

  BOOST_AUTO_TEST_CASE(isSquareCorrectSquaresTest)
  {
    BOOST_CHECK(isSquare(CORRECT_SQUARE1));
    BOOST_CHECK(isSquare(CORRECT_SQUARE2));
  }

  BOOST_AUTO_TEST_CASE(operatorLessCompareWithTriangleTest)
  {
    BOOST_CHECK(TRIANGLE < CORRECT_SQUARE1);
    BOOST_CHECK(TRIANGLE < CORRECT_SQUARE2);

    BOOST_CHECK(TRIANGLE < CORRECT_RECTANGLE1);
    BOOST_CHECK(TRIANGLE < CORRECT_RECTANGLE2);
    BOOST_CHECK(TRIANGLE < CORRECT_RECTANGLE3);
  }

  BOOST_AUTO_TEST_CASE(operatorLessCompareWithSquareTest)
  {
    BOOST_CHECK(CORRECT_SQUARE1 < CORRECT_RECTANGLE1);
    BOOST_CHECK(CORRECT_SQUARE1 < CORRECT_RECTANGLE2);
    BOOST_CHECK(CORRECT_SQUARE1 < CORRECT_RECTANGLE3);

    BOOST_CHECK(!(CORRECT_SQUARE1 < TRIANGLE));
    BOOST_CHECK(!(CORRECT_SQUARE2 < TRIANGLE));
  }

  BOOST_AUTO_TEST_CASE(operatorLessCompareWithRectangleTest)
  {
    BOOST_CHECK(!(CORRECT_RECTANGLE1 < TRIANGLE));
    BOOST_CHECK(!(CORRECT_RECTANGLE2 < TRIANGLE));
    BOOST_CHECK(!(CORRECT_RECTANGLE3 < TRIANGLE));

    BOOST_CHECK(!(CORRECT_RECTANGLE1 < CORRECT_SQUARE1));
    BOOST_CHECK(!(CORRECT_RECTANGLE1 < CORRECT_SQUARE2));
  }

  BOOST_AUTO_TEST_CASE(operatorLessCompareRectangleWithOtherQuadranqlesTest)
  {
    BOOST_CHECK(CORRECT_RECTANGLE1 < RHOMBUS);
    BOOST_CHECK(CORRECT_RECTANGLE2 < RHOMBUS);
    BOOST_CHECK(CORRECT_RECTANGLE3 < RHOMBUS);

    BOOST_CHECK(CORRECT_RECTANGLE1 < ISOSCELES_TRAPEZOID);
    BOOST_CHECK(CORRECT_RECTANGLE2 < ISOSCELES_TRAPEZOID);
    BOOST_CHECK(CORRECT_RECTANGLE3 < ISOSCELES_TRAPEZOID);

    BOOST_CHECK(CORRECT_RECTANGLE1 < PARALLELOGRAM);
    BOOST_CHECK(CORRECT_RECTANGLE2 < PARALLELOGRAM);
    BOOST_CHECK(CORRECT_RECTANGLE3 < PARALLELOGRAM);
  }

  BOOST_AUTO_TEST_CASE(operatorLessCompareSquareWithOtherQuadranqlesTest)
  {
    BOOST_CHECK(CORRECT_SQUARE1 < RHOMBUS);
    BOOST_CHECK(CORRECT_SQUARE2 < RHOMBUS);

    BOOST_CHECK(CORRECT_SQUARE1 < ISOSCELES_TRAPEZOID);
    BOOST_CHECK(CORRECT_SQUARE2 < ISOSCELES_TRAPEZOID);

    BOOST_CHECK(CORRECT_SQUARE1 < PARALLELOGRAM);
    BOOST_CHECK(CORRECT_SQUARE2 < PARALLELOGRAM);
  }

BOOST_AUTO_TEST_SUITE_END()
