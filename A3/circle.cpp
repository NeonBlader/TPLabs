#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <ostream>
#include <cmath>
#include <stdexcept>

kurenkov::Circle::Circle(double radius, const point_t &center):
  radius_(radius),
  pos_(center)
{
  if (radius_ <= 0.0) {
    throw std::invalid_argument("Non-positive circle radius");
  }
}

double kurenkov::Circle::getArea() const noexcept
{
  return M_PI * std::pow(radius_, 2.0);
}

kurenkov::rectangle_t kurenkov::Circle::getFrameRect() const
{
  return {radius_ * 2.0, radius_ * 2.0, pos_};
}

void kurenkov::Circle::move(double xShift, double yShift) noexcept
{
  pos_.x += xShift;
  pos_.y += yShift;
}

void kurenkov::Circle::move(const point_t &newCenter)
{
  pos_ = newCenter;
}

void kurenkov::Circle::printInfo(std::ostream &out) const
{
  out << "Radius: " << radius_ << '\n';
  out << "Center coordinates: (" << pos_.x << "; " << pos_.y << ")\n";
}

void kurenkov::Circle::scale(double coefficient)
{
  if (coefficient <= 0) {
    throw std::invalid_argument("Non-positive scale coefficient");
  }
  radius_ *= coefficient;
}

kurenkov::point_t kurenkov::Circle::getCenter() const
{
  return pos_;
}

double kurenkov::Circle::getRadius() const
{
  return radius_;
}
