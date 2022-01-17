#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace kurenkov;

void printDemonstrativeTests(std::shared_ptr<Shape> &shape, std::ostream &out)
{
  double xShiftValue = 9.4;
  double yShiftValue = 13.3;
  point_t point = {18.0, 14.5};
  double scaleCoefficient = 5.0;

  out << "We have a shape with the following parameters:\n";
  shape->printInfo(out);
  out << "Area of this shape is " << shape->getArea() << '\n';
  rectangle_t rectFrameForFirstShape = shape->getFrameRect();
  out << "Frame rectangle for this shape has the following parameters:\n";
  out << "Width: " << rectFrameForFirstShape.width << '\n' << "Height: " << rectFrameForFirstShape.height << '\n'
      << "Center coordinates: (" << rectFrameForFirstShape.pos.x << "; " << rectFrameForFirstShape.pos.y << ")\n";
  shape->move(xShiftValue, yShiftValue);
  out << "We shifted the center of this shape by 9.4 along the x and 13.3 along the y, new parameters are:\n";
  shape->printInfo(out);
  shape->move(point);
  out << "We moved the center of this shape in point with coordinates (18; 14.5), new parameters are:\n";
  shape->printInfo(out);
  shape->scale(scaleCoefficient);
  out << "We have enlarged this shape five times relative to its center, new parameters are:\n";
  shape->printInfo(out);
}

int main()
{
  std::cout << "Let's test rectangle at first\n";
  point_t firstPoint = {13.4, 11.9};
  std::shared_ptr<Shape> firstShape = std::make_shared<Rectangle>(5.0, 10.0, firstPoint);
  printDemonstrativeTests(firstShape, std::cout);
  std::cout << "\n \n";

  std::cout << "Let's test shape\n";
  point_t secondPoint = {84.6, 1.9};
  std::shared_ptr<Shape> secondShape = std::make_shared<Rectangle>(5.0, 10.0, secondPoint);
  printDemonstrativeTests(secondShape, std::cout);
  std::cout << "\n \n";

  std::cout << "After that let's test composite shape\n";
  std::shared_ptr<Shape> firstSmartPtrShape = std::make_shared<Rectangle>(5.0, 10.0, point_t{1.0, 1.0});
  std::shared_ptr<Shape> secondSmartPtrShape = std::make_shared<Circle>(6.0, point_t{2.0, 4.0});
  CompositeShape compositeShape;
  compositeShape.pushBack(firstSmartPtrShape);
  compositeShape.pushBack(secondSmartPtrShape);
  std::shared_ptr<Shape> compositeShapePtr = std::make_shared<CompositeShape>(compositeShape);
  std::cout << "Before tests composite shape have such detailed information:\n";
  compositeShape.printDetailedInfo(std::cout);
  printDemonstrativeTests(compositeShapePtr, std::cout);
  std::cout << "After tests composite shape have such detailed information:\n";
  compositeShape.printDetailedInfo(std::cout);
  return 0;
}
