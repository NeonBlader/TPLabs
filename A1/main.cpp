#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  point_t firstPoint = {10.0, 20.0};
  Rectangle someRectangle(5.0, 15.0, firstPoint);
  std::cout << "We have a rectangle with the following parameters:\n";
  someRectangle.printInfo(std::cout);
  std::cout << "Area of this rectangle is " << someRectangle.getArea() << '\n';
  rectangle_t rectFrameForRect = someRectangle.getFrameRect();
  std::cout << "Frame rectangle for this rectangle has the following parameters:\n";
  std::cout << "Width: " << rectFrameForRect.width << '\n' << "Height: " << rectFrameForRect.height << '\n'
      << "Center coordinates: (" << rectFrameForRect.pos.x << "; " << rectFrameForRect.pos.y << ")\n";
  double xShiftValue = 3.5;
  double yShiftValue = 12.5;
  someRectangle.move(xShiftValue, yShiftValue);
  std::cout << "We shifted the center of this rectangle by 3.5 along the x and 12.5 along the y, new parameters are:\n";
  someRectangle.printInfo(std::cout);
  firstPoint = {33.0, 44.0};
  someRectangle.move(firstPoint);
  std::cout << "We moved the center of this rectangle in point with coordinates (33; 44), new parameters are:\n";
  someRectangle.printInfo(std::cout);

  point_t secondPoint = {8.0, 16.0};
  Circle someCircle(10.0, secondPoint);
  std::cout << "We have a circle with the following parameters:\n";
  someCircle.printInfo(std::cout);
  std::cout << "Area of this circle is " << someCircle.getArea() << '\n';
  rectangle_t frameRectForCircle = someCircle.getFrameRect();
  std::cout << "Frame rectangle for this circle has the following parameters:\n";
  std::cout << "Width: " << frameRectForCircle.width << '\n' << "Height: " << frameRectForCircle.height << '\n'
      << "Center coordinates: (" << frameRectForCircle.pos.x << "; " << frameRectForCircle.pos.y << ")\n";
  xShiftValue = 7.4;
  yShiftValue = 4.5;
  someCircle.move(xShiftValue, yShiftValue);
  std::cout << "We shifted the center of this circle by 7.4 along the x and 4.5 along the y, new parameters are:\n";
  someCircle.printInfo(std::cout);
  secondPoint = {22.0, 55.0};
  someCircle.move(secondPoint);
  std::cout << "We moved the center of this circle in point with coordinates (22; 55), new parameters are:\n";
  someCircle.printInfo(std::cout);

  std::cout << "Perform the same operations, but using polymorphic pointers:\n";
  point_t thirdPoint = {13.4, 11.9};
  Shape *firstShape = nullptr;
  try {
    firstShape = new Rectangle(4.0, 5.7, thirdPoint);
    std::cout << "We have a shape with the following parameters:\n";
    firstShape->printInfo(std::cout);
    std::cout << "Area of this shape is " << firstShape->getArea() << '\n';
    rectangle_t rectFrameForFirstShape = firstShape->getFrameRect();
    std::cout << "Frame rectangle for this shape has the following parameters:\n";
    std::cout << "Width: " << rectFrameForFirstShape.width << '\n' << "Height: " << rectFrameForFirstShape.height << '\n'
        << "Center coordinates: (" << rectFrameForFirstShape.pos.x << "; " << rectFrameForFirstShape.pos.y << ")\n";
    xShiftValue = 9.4;
    yShiftValue = 13.3;
    firstShape->move(xShiftValue, yShiftValue);
    std::cout << "We shifted the center of this shape by 9.4 along the x and 13.3 along the y, new parameters are:\n";
    firstShape->printInfo(std::cout);
    thirdPoint = {18.0, 26.0};
    firstShape->move(thirdPoint);
    std::cout << "We moved the center of this shape in point with coordinates (18; 26), new parameters are:\n";
    firstShape->printInfo(std::cout);
    delete firstShape;
  }
  catch (const std::exception &err) {
    std::cout << err.what() << '\n';
    delete firstShape;
  }

  point_t fourthPoint = {84.6, 1.9};
  Shape *secondShape = nullptr;
  try {
    secondShape = new Circle(4.8, fourthPoint);
    std::cout << "We have a shape with the following parameters:\n";
    secondShape->printInfo(std::cout);
    std::cout << "Area of this shape is " << secondShape->getArea() << '\n';
    rectangle_t rectFrameForSecondShape = secondShape->getFrameRect();
    std::cout << "Frame rectangle for this shape has the following parameters:\n";
    std::cout << "Width: " << rectFrameForSecondShape.width << '\n' << "Height: " << rectFrameForSecondShape.height << '\n'
        << "Center coordinates: (" << rectFrameForSecondShape.pos.x << "; " << rectFrameForSecondShape.pos.y << ")\n";
    xShiftValue = 19.7;
    yShiftValue = 93.3;
    secondShape->move(xShiftValue, yShiftValue);
    std::cout << "We shifted the center of this shape by 19.7 along the x and 93.3 along the y, new parameters are:\n";
    secondShape->printInfo(std::cout);
    fourthPoint = {30.0, 6.0};
    secondShape->move(fourthPoint);
    std::cout << "We moved the center of this shape in point with coordinates (30; 6), new parameters are:\n";
    secondShape->printInfo(std::cout);
    delete secondShape;
  }
  catch (const std::exception &err) {
    std::cout << err.what() << '\n';
    delete secondShape;
  }
  return 0;
}
