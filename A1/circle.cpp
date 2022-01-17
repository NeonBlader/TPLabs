#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <ostream>
#include <cmath>
#include <stdexcept>

Circle::Circle(double radius, const point_t &center):
  radius_(radius),
  pos_(center)
{
  if (radius_ <= 0.0) {
    throw std::invalid_argument("Non-positive circle radius");
  }
}

double Circle::getArea() const
{
  return M_PI * std::pow(radius_, 2.0);
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2.0, radius_ * 2.0, pos_};
}

void Circle::move(double xShift, double yShift)
{
  pos_.x += xShift;
  pos_.y += yShift;
}

void Circle::move(const point_t &newCenter)
{
  pos_ = newCenter;
}

void Circle::printInfo(std::ostream &out) const
{
  out << "Radius: " << radius_ << '\n';
  out << "Center coordinates: (" << pos_.x << "; " << pos_.y << ")\n";
}
