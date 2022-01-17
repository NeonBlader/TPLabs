#include <stdexcept>
#include <cmath>
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>

#include "rectangle.hpp"

const double X = 2.4;
const double Y = 5.5;
const double HEIGHT = 10.0;
const double WIDTH = 6.0;
const double COEFFICIENT = 15.0;
const double X_FOR_MOVING = 7.8;
const double Y_FOR_MOVING = 11.0;
const double AREA = HEIGHT * WIDTH;
const double PRECISION = 1e-8;

BOOST_AUTO_TEST_SUITE(rectangleTests)

  BOOST_AUTO_TEST_CASE(noThrowConstructorTest)
  {
    BOOST_CHECK_NO_THROW(kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y}));
  }

  BOOST_AUTO_TEST_CASE(invalidWidthConstructorTest)
  {
    BOOST_CHECK_THROW(kurenkov::Rectangle rectangle(-WIDTH, HEIGHT, {X, Y}), std::invalid_argument);
    BOOST_CHECK_THROW(kurenkov::Rectangle rectangle(0.0, HEIGHT, {X, Y}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(invalidHeightConstructorTest)
  {
    BOOST_CHECK_THROW(kurenkov::Rectangle rectangle(WIDTH, -HEIGHT, {X, Y}), std::invalid_argument);
    BOOST_CHECK_THROW(kurenkov::Rectangle rectangle(WIDTH, 0.0, {X, Y}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(getWidthTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    BOOST_CHECK_CLOSE(WIDTH, rectangle.getWidth(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(getHeightTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    BOOST_CHECK_CLOSE(HEIGHT, rectangle.getHeight(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(getCenterTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    BOOST_CHECK_CLOSE(X, rectangle.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y, rectangle.getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(getAreaTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    BOOST_CHECK_CLOSE(AREA, rectangle.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    BOOST_CHECK_CLOSE(WIDTH, rectangle.getFrameRect().width, PRECISION);
    BOOST_CHECK_CLOSE(HEIGHT, rectangle.getFrameRect().height, PRECISION);
    BOOST_CHECK_CLOSE(X, rectangle.getFrameRect().pos.x, PRECISION);
    BOOST_CHECK_CLOSE(Y, rectangle.getFrameRect().pos.y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(relativeMoveCenterChangeTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    rectangle.move(X_FOR_MOVING, Y_FOR_MOVING);
    BOOST_CHECK_CLOSE(X + X_FOR_MOVING, rectangle.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y + Y_FOR_MOVING, rectangle.getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(relativeMoveCharacteristicsPermanenceTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    rectangle.move(X_FOR_MOVING, Y_FOR_MOVING);
    BOOST_CHECK_CLOSE(WIDTH, rectangle.getWidth(), PRECISION);
    BOOST_CHECK_CLOSE(HEIGHT, rectangle.getHeight(), PRECISION);
    BOOST_CHECK_CLOSE(AREA, rectangle.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(absoluteMoveCenterChangeTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    rectangle.move({X_FOR_MOVING, Y_FOR_MOVING});
    BOOST_CHECK_CLOSE(X_FOR_MOVING, rectangle.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y_FOR_MOVING, rectangle.getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(absoluteMoveCharacteristicsPermanenceTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    rectangle.move({X_FOR_MOVING, Y_FOR_MOVING});
    BOOST_CHECK_CLOSE(WIDTH, rectangle.getWidth(), PRECISION);
    BOOST_CHECK_CLOSE(HEIGHT, rectangle.getHeight(), PRECISION);
    BOOST_CHECK_CLOSE(AREA, rectangle.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(correctScaleCoefficientNoThrowTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    BOOST_CHECK_NO_THROW(rectangle.scale(COEFFICIENT));
  }

  BOOST_AUTO_TEST_CASE(invalidScaleCoefficientTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    BOOST_CHECK_THROW(rectangle.scale(-COEFFICIENT), std::invalid_argument);
    BOOST_CHECK_THROW(rectangle.scale(0.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(changingOfCharacteristicsAfterScaleTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    rectangle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(WIDTH * COEFFICIENT, rectangle.getWidth(), PRECISION);
    BOOST_CHECK_CLOSE(HEIGHT * COEFFICIENT, rectangle.getHeight(), PRECISION);
    BOOST_CHECK_CLOSE(AREA * std::pow(COEFFICIENT, 2), rectangle.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(permanenceOfCenterAfterScaleTest)
  {
    kurenkov::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    rectangle.scale(COEFFICIENT);
    BOOST_CHECK_CLOSE(X, rectangle.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y, rectangle.getCenter().y, PRECISION);
  }

BOOST_AUTO_TEST_SUITE_END()
