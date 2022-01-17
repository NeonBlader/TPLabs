#define _USE_MATH_DEFINES

#include <stdexcept>
#include <cmath>
#include <memory>
#include <boost/test/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

const double X = 6.0;
const double Y = 4.5;
const double WIDTH = 6.0;
const double HEIGHT = 2.0;
const double RADIUS = 2.0;
const double CIRCLE_AREA = M_PI * std::pow(RADIUS, 2);
const double RECTANGLE_AREA = WIDTH * HEIGHT;
const double X_FOR_MOVING = 11.0;
const double Y_FOR_MOVING = 14.5;
const double COEFFICIENT = 2.0;
const double PRECISION = 1e-8;

BOOST_AUTO_TEST_SUITE(compositeShapeTests)

  BOOST_AUTO_TEST_CASE(constructorTest)
  {
    BOOST_CHECK_NO_THROW(kurenkov::CompositeShape compositeShape);
  }

  BOOST_AUTO_TEST_CASE(copyConsturctorTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    BOOST_CHECK_NO_THROW(kurenkov::CompositeShape secondCompositeShape(compositeShape));
    kurenkov::CompositeShape secondCompositeShape(compositeShape);

    BOOST_CHECK_EQUAL(2, secondCompositeShape.getCount());

    kurenkov::rectangle_t frameRect = secondCompositeShape.getFrameRect();
    BOOST_CHECK_CLOSE(X, frameRect.pos.x, PRECISION);
    BOOST_CHECK_CLOSE(Y, frameRect.pos.y, PRECISION);
    BOOST_CHECK_CLOSE(WIDTH, frameRect.width, PRECISION);
    BOOST_CHECK_CLOSE(RADIUS * 2, frameRect.height, PRECISION);

    BOOST_CHECK_CLOSE(CIRCLE_AREA + RECTANGLE_AREA, secondCompositeShape.getArea(), PRECISION);

    BOOST_CHECK(secondCompositeShape[0] == compositeShape[0]);
    BOOST_CHECK(secondCompositeShape[1] == compositeShape[1]);
  }

  BOOST_AUTO_TEST_CASE(copyOperatorTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    kurenkov::CompositeShape secondCompositeShape;
    BOOST_CHECK_NO_THROW(secondCompositeShape = compositeShape);

    BOOST_CHECK_EQUAL(2, secondCompositeShape.getCount());

    kurenkov::rectangle_t frameRect = secondCompositeShape.getFrameRect();
    BOOST_CHECK_CLOSE(X, frameRect.pos.x, PRECISION);
    BOOST_CHECK_CLOSE(Y, frameRect.pos.y, PRECISION);
    BOOST_CHECK_CLOSE(WIDTH, frameRect.width, PRECISION);
    BOOST_CHECK_CLOSE(RADIUS * 2, frameRect.height, PRECISION);

    BOOST_CHECK_CLOSE(CIRCLE_AREA + RECTANGLE_AREA, secondCompositeShape.getArea(), PRECISION);

    BOOST_CHECK(secondCompositeShape[0] == compositeShape[0]);
    BOOST_CHECK(secondCompositeShape[1] == compositeShape[1]);
  }

  BOOST_AUTO_TEST_CASE(correctArgumentIndexOperatorTest)
  {
    kurenkov::CompositeShape compositeShape;
    std::shared_ptr<kurenkov::Shape> circle =  std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y});
    std::shared_ptr<kurenkov::Shape> rectangle = std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y});
    compositeShape.pushBack(circle);
    compositeShape.pushBack(rectangle);

    BOOST_CHECK_NO_THROW(compositeShape[0]);
    BOOST_CHECK_NO_THROW(compositeShape[1]);

    BOOST_CHECK_CLOSE(X, compositeShape[0]->getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y, compositeShape[0]->getCenter().y, PRECISION);
    BOOST_CHECK_CLOSE(RADIUS * 2, compositeShape[0]->getFrameRect().width, PRECISION);
    BOOST_CHECK_CLOSE(RADIUS * 2, compositeShape[0]->getFrameRect().height, PRECISION);

    BOOST_CHECK_CLOSE(X, compositeShape[1]->getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y, compositeShape[1]->getCenter().y, PRECISION);
    BOOST_CHECK_CLOSE(WIDTH, compositeShape[1]->getFrameRect().width, PRECISION);
    BOOST_CHECK_CLOSE(HEIGHT, compositeShape[1]->getFrameRect().height, PRECISION);

    BOOST_CHECK_CLOSE(RECTANGLE_AREA, compositeShape[1]->getArea(), PRECISION);

    BOOST_CHECK(compositeShape[0] == circle);
    BOOST_CHECK(compositeShape[1] == rectangle);
  }

  BOOST_AUTO_TEST_CASE(invalidArgumentIndexOperatorTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    BOOST_CHECK_THROW(compositeShape[-1], std::invalid_argument);
    BOOST_CHECK_THROW(compositeShape[2], std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(getZeroCountTest)
  {
    kurenkov::CompositeShape compositeShape;
    BOOST_CHECK_EQUAL(0, compositeShape.getCount());
  }

  BOOST_AUTO_TEST_CASE(getOneCountTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    BOOST_CHECK_EQUAL(1, compositeShape.getCount());
  }

  BOOST_AUTO_TEST_CASE(getTwoCountTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));
    BOOST_CHECK_EQUAL(2, compositeShape.getCount());
  }

  BOOST_AUTO_TEST_CASE(getCenterTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    BOOST_CHECK_CLOSE(X, compositeShape.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y, compositeShape.getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(getAreaTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));
    BOOST_CHECK_CLOSE(RECTANGLE_AREA + CIRCLE_AREA, compositeShape.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(emptyCompositeShapeGetAreaTest)
  {
    kurenkov::CompositeShape compositeShape;
    BOOST_CHECK_CLOSE(0.0, compositeShape.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    BOOST_CHECK_NO_THROW(compositeShape.getFrameRect());

    kurenkov::rectangle_t frameRect = compositeShape.getFrameRect();
    BOOST_CHECK_CLOSE(WIDTH, frameRect.width, PRECISION);
    BOOST_CHECK_CLOSE(RADIUS * 2, frameRect.height, PRECISION);
    BOOST_CHECK_CLOSE(X, frameRect.pos.x, PRECISION);
    BOOST_CHECK_CLOSE(Y, frameRect.pos.y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(emptyCompositeShapeGetFrameRectTest)
  {
    kurenkov::CompositeShape compositeShape;
    BOOST_CHECK_THROW(compositeShape.getFrameRect(), std::underflow_error);
  }

  BOOST_AUTO_TEST_CASE(relativeMoveNoThrowTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));
    BOOST_CHECK_NO_THROW(compositeShape.move(X_FOR_MOVING, Y_FOR_MOVING));
  }


  BOOST_AUTO_TEST_CASE(relativeMoveCenterChangeTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    compositeShape.move(X_FOR_MOVING, Y_FOR_MOVING);
    BOOST_CHECK_CLOSE(X + X_FOR_MOVING, compositeShape.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y + Y_FOR_MOVING, compositeShape.getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(relativeMoveCharacteristicsPermanenceTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    compositeShape.move(X_FOR_MOVING, Y_FOR_MOVING);
    BOOST_CHECK_CLOSE(CIRCLE_AREA + RECTANGLE_AREA, compositeShape.getArea(), PRECISION);

    kurenkov::rectangle_t frameRect = compositeShape.getFrameRect();
    BOOST_CHECK_CLOSE(WIDTH, frameRect.width, PRECISION);
    BOOST_CHECK_CLOSE(RADIUS * 2, frameRect.height, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(absoluteMoveNoThrowTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));
    BOOST_CHECK_NO_THROW(compositeShape.move({X_FOR_MOVING, Y_FOR_MOVING}));
  }

  BOOST_AUTO_TEST_CASE(absoluteMoveCenterChangeTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    compositeShape.move({X_FOR_MOVING, Y_FOR_MOVING});
    BOOST_CHECK_CLOSE(X_FOR_MOVING, compositeShape.getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y_FOR_MOVING, compositeShape.getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(absoluteMoveCharacteristicsPermanenceTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    compositeShape.move({X_FOR_MOVING, Y_FOR_MOVING});
    BOOST_CHECK_CLOSE(CIRCLE_AREA + RECTANGLE_AREA, compositeShape.getArea(), PRECISION);

    kurenkov::rectangle_t frameRect = compositeShape.getFrameRect();
    BOOST_CHECK_CLOSE(WIDTH, frameRect.width, PRECISION);
    BOOST_CHECK_CLOSE(RADIUS * 2, frameRect.height, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(scaleNoThrowTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));
    BOOST_CHECK_NO_THROW(compositeShape.scale(COEFFICIENT));
  }

  BOOST_AUTO_TEST_CASE(nonPositiveScaleCoefficientTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    BOOST_CHECK_THROW(compositeShape.scale(-COEFFICIENT), std::invalid_argument);
    BOOST_CHECK_THROW(compositeShape.scale(0.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(characteristicsChangeAfterScaleTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    compositeShape.scale(COEFFICIENT);
    kurenkov::rectangle_t frameRect = compositeShape.getFrameRect();
    BOOST_CHECK_CLOSE(WIDTH * COEFFICIENT, frameRect.width, PRECISION);
    BOOST_CHECK_CLOSE(RADIUS * 2 * COEFFICIENT, frameRect.height, PRECISION);
    BOOST_CHECK_CLOSE((CIRCLE_AREA + RECTANGLE_AREA) * std::pow(COEFFICIENT, 2), compositeShape.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(pushFirstItemByPushItemTest)
  {
    kurenkov::CompositeShape compositeShape;
    BOOST_CHECK_NO_THROW(compositeShape.pushItem(0, std::make_shared<kurenkov::Circle>(kurenkov::Circle(RADIUS, {X, Y}))));
    BOOST_CHECK_EQUAL(1, compositeShape.getCount());
  }

  BOOST_AUTO_TEST_CASE(pushNotFirstItemByPushItemTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushItem(0, std::make_shared<kurenkov::Circle>(kurenkov::Circle(RADIUS, {X, Y})));

    BOOST_CHECK_NO_THROW(compositeShape.pushItem(0, std::make_shared<kurenkov::Rectangle>(kurenkov::Rectangle(WIDTH, HEIGHT, {X, Y}))));
    BOOST_CHECK_EQUAL(2, compositeShape.getCount());
  }

  BOOST_AUTO_TEST_CASE(invalidIndexPushItemTest)
  {
    kurenkov::CompositeShape compositeShape;
    std::shared_ptr<kurenkov::Shape> shape = std::make_shared<kurenkov::Circle>(kurenkov::Circle(RADIUS, {X, Y}));

    BOOST_CHECK_THROW(compositeShape.pushItem(-1, shape), std::invalid_argument);
    BOOST_CHECK_THROW(compositeShape.pushItem(1, shape), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(emptyPointerPushItemTest)
  {
    kurenkov::CompositeShape compositeShape;
    BOOST_CHECK_THROW(compositeShape.pushItem(0, nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(pushItselfPushItemTest)
  {
    std::shared_ptr<kurenkov::CompositeShape> compositeShape = std::make_shared<kurenkov::CompositeShape>();
    BOOST_CHECK_THROW(compositeShape->pushItem(0, compositeShape), std::logic_error);
  }

  BOOST_AUTO_TEST_CASE(pushBackFirstElementTest)
  {
    kurenkov::CompositeShape compositeShape;

    BOOST_CHECK_NO_THROW(compositeShape.pushBack(std::make_shared<kurenkov::Circle>(kurenkov::Circle(RADIUS, {X, Y}))));
    BOOST_CHECK_EQUAL(1, compositeShape.getCount());
    BOOST_CHECK_CLOSE(CIRCLE_AREA, compositeShape[0]->getArea(), PRECISION);
    BOOST_CHECK_CLOSE(X, compositeShape[0]->getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y, compositeShape[0]->getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(pushBackNotFirstElementTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(kurenkov::Circle(RADIUS, {X, Y})));

    BOOST_CHECK_NO_THROW(compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(kurenkov::Rectangle(WIDTH, HEIGHT, {X, Y}))));
    BOOST_CHECK_EQUAL(2, compositeShape.getCount());
    BOOST_CHECK_CLOSE(RECTANGLE_AREA, compositeShape[1]->getArea(), PRECISION);
    BOOST_CHECK_CLOSE(X, compositeShape[1]->getCenter().x, PRECISION);
    BOOST_CHECK_CLOSE(Y, compositeShape[1]->getCenter().y, PRECISION);
  }

  BOOST_AUTO_TEST_CASE(emptyPointerPushBackTest)
  {
    kurenkov::CompositeShape compositeShape;
    BOOST_CHECK_THROW(compositeShape.pushBack(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(deleteNotLastElementByDeleteItemTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    BOOST_CHECK_NO_THROW(compositeShape.deleteItem(0));

    kurenkov::rectangle_t frameRect = compositeShape.getFrameRect();
    BOOST_CHECK_CLOSE(WIDTH, frameRect.width, PRECISION);
    BOOST_CHECK_CLOSE(HEIGHT, frameRect.height, PRECISION);

    BOOST_CHECK_CLOSE(RECTANGLE_AREA, compositeShape.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(deleteLastElementByDeleteItemTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));

    BOOST_CHECK_NO_THROW(compositeShape.deleteItem(0));
    BOOST_CHECK_THROW(compositeShape.getFrameRect(), std::underflow_error);
    BOOST_CHECK_CLOSE(0.0, compositeShape.getArea(), PRECISION);
    BOOST_CHECK_EQUAL(0, compositeShape.getCount());
  }

  BOOST_AUTO_TEST_CASE(invalidIndexDeleteItemTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    BOOST_CHECK_THROW(compositeShape.deleteItem(-1), std::invalid_argument);
    BOOST_CHECK_THROW(compositeShape.deleteItem(compositeShape.getCount()), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(deleteNotLastElementByDeleteBackTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));
    compositeShape.pushBack(std::make_shared<kurenkov::Rectangle>(WIDTH, HEIGHT, kurenkov::point_t{X, Y}));

    BOOST_CHECK_NO_THROW(compositeShape.deleteBack());

    kurenkov::rectangle_t frameRect = compositeShape.getFrameRect();
    BOOST_CHECK_CLOSE(RADIUS * 2, frameRect.width, PRECISION);
    BOOST_CHECK_CLOSE(RADIUS * 2, frameRect.height, PRECISION);

    BOOST_CHECK_CLOSE(CIRCLE_AREA, compositeShape.getArea(), PRECISION);
  }

  BOOST_AUTO_TEST_CASE(deleteLastElementByDeleteBackTest)
  {
    kurenkov::CompositeShape compositeShape;
    compositeShape.pushBack(std::make_shared<kurenkov::Circle>(RADIUS, kurenkov::point_t{X, Y}));

    BOOST_CHECK_NO_THROW(compositeShape.deleteBack());
    BOOST_CHECK_THROW(compositeShape.getFrameRect(), std::underflow_error);
    BOOST_CHECK_CLOSE(0.0, compositeShape.getArea(), PRECISION);
    BOOST_CHECK_EQUAL(0, compositeShape.getCount());
  }

  BOOST_AUTO_TEST_CASE(emptyArrayDeleteBackTest)
  {
    kurenkov::CompositeShape compositeShape;
    BOOST_CHECK_THROW(compositeShape.deleteBack(), std::underflow_error);
  }

BOOST_AUTO_TEST_SUITE_END()
