#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iterator>

#include "shape.hpp"

void executeSecondTask(std::istream &in, std::ostream &out)
{
  std::vector<Shape> shapes{std::istream_iterator<Shape>(in), std::istream_iterator<Shape>()};
  if ((in.fail()) && (!in.eof())) {
    throw std::ios_base::failure("Error while input reading");
  }

  std::size_t verticesCount = 0;
  std::size_t trianglesCount = 0;
  std::size_t squaresCount = 0;
  std::size_t rectanglesCount = 0;
  std::for_each(shapes.begin(), shapes.end(), [&](const Shape &shape)
  {
    if (shape.size() == COUNT_OF_VERTICES_OF_TRIANGLE) {
      trianglesCount++;
    } else if (isRectangle(shape)) {
      if (isSquare(shape)) {
        squaresCount++;
      }
      rectanglesCount++;
    }
    verticesCount += shape.size();
  });

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), isPentagon), shapes.end());

  Shape points;
  std::transform(shapes.begin(), shapes.end(), std::back_inserter(points), [](const Shape &shape)
  {
    return shape.front();
  });

  std::sort(shapes.begin(), shapes.end());

  out << "Vertices: " << verticesCount << '\n';
  out << "Triangles: " << trianglesCount << '\n';
  out << "Squares: " << squaresCount << '\n';
  out << "Rectangles: " << rectanglesCount << '\n';
  out << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(out, " "));
  out << '\n';
  out << "Shapes: \n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(out, "\n"));
}
