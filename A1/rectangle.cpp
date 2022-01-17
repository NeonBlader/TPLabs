#include "rectangle.hpp"

#include <ostream>
#include <stdexcept>

Rectangle::Rectangle(double width, double height, const point_t &pos):
  width_(width),
  height_(height),
  pos_(pos)
{
  if (width_ <= 0.0) {
    throw std::invalid_argument("Non-positive rectangle height");
  }
  if (height_ <= 0.0) {
    throw std::invalid_argument("Non-positive rectangle height");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void Rectangle::move(double xShift, double yShift)
{
  pos_.x += xShift;
  pos_.y += yShift;
}

void Rectangle::move(const point_t &newCenter)
{
  pos_ = newCenter;
}

void Rectangle::printInfo(std::ostream &out) const
{
  out << "Width: " << width_ << '\n';
  out << "Height: " << height_ << '\n';
  out << "Center coordinates: (" << pos_.x << "; " << pos_.y << ")\n";
}
