#include "rectangle.hpp"

#include <ostream>
#include <stdexcept>

kurenkov::Rectangle::Rectangle(double width, double height, const point_t &pos):
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

double kurenkov::Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

kurenkov::rectangle_t kurenkov::Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void kurenkov::Rectangle::move(double xShift, double yShift) noexcept
{
  pos_.x += xShift;
  pos_.y += yShift;
}

void kurenkov::Rectangle::move(const point_t &newCenter)
{
  pos_ = newCenter;
}

void kurenkov::Rectangle::printInfo(std::ostream &out) const
{
  out << "Width: " << width_ << '\n';
  out << "Height: " << height_ << '\n';
  out << "Center coordinates: (" << pos_.x << "; " << pos_.y << ")\n";
}

void kurenkov::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0) {
    throw std::invalid_argument("Non-positive scale coefficient");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

kurenkov::point_t kurenkov::Rectangle::getCenter() const
{
  return pos_;
}

double kurenkov::Rectangle::getWidth() const
{
  return width_;
}

double kurenkov::Rectangle::getHeight() const
{
  return height_;
}
