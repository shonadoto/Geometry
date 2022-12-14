#include "Line.h"

Line::Line(const Point& point, double coef)
    : x_coef_(coef), y_coef_(-1), free_coef_(point.y - coef * point.x) {}

Line::Line(const Point& point1, const Point& point2) {
  if (doubleEqual(point1.x, point2.x)) {
    x_coef_ = 1;
    y_coef_ = 0;
    free_coef_ = -point1.x;
    return;
  }
  if (doubleEqual(point1.y, point2.y)) {
    x_coef_ = 0;
    y_coef_ = 1;
    free_coef_ = -point1.y;
    return;
  }
  x_coef_ = 1;
  y_coef_ = (point2.x - point1.x) / (point1.y - point2.y);
  free_coef_ = -point1.x - y_coef_ * point1.y;
}

Line::Line(double coef, double shift)
    : x_coef_(coef), y_coef_(-1), free_coef_(shift) {}

double Line::dist(const Point& point) const {
  return std::abs(x_coef_ * point.x + y_coef_ * point.y + free_coef_) /
         std::sqrt(x_coef_ * x_coef_ + y_coef_ * y_coef_);
}

Point Line::normal() const { return Point(x_coef_, y_coef_); }

bool Line::isParallel(const Line& other) const {
  return doubleEqual(x_coef_ / y_coef_, other.x_coef_ / other.y_coef_);
}

Point Line::intersect(const Line& other) const {
  if (isParallel(other)) throw std::runtime_error("Lines are parallel");
  if (doubleEqual(x_coef_, 0) && doubleEqual(y_coef_, 0))
    throw std::runtime_error("Not a line");
  if (doubleEqual(x_coef_, 0)) {
    return Point((-other.free_coef_ + free_coef_ * other.y_coef_ / y_coef_) /
                     other.x_coef_,
                 -free_coef_ / y_coef_);
  }
  if (doubleEqual(y_coef_, 0)) {
    return Point(-free_coef_ / x_coef_,
                 (-other.free_coef_ + free_coef_ * other.x_coef_ / x_coef_) /
                     other.y_coef_);
  }
  if (doubleEqual(other.x_coef_, 0) || doubleEqual(other.y_coef_, 0))
    return other.intersect(*this);
  double x = (free_coef_ * other.y_coef_ - other.free_coef_ * y_coef_) /
             (y_coef_ * other.x_coef_ - other.y_coef_ * x_coef_);
  return Point(x, (-free_coef_ - x_coef_ * x) / y_coef_);
}

bool Line::operator==(const Line& other) const {
  if (doubleEqual(other.x_coef_, 0) && doubleEqual(other.y_coef_, 0))
    throw std::runtime_error("Not a line WTF");
  double coef = 0;
  if (doubleEqual(other.x_coef_, 0)) {
    coef = y_coef_ / other.y_coef_;
  } else {
    coef = x_coef_ / other.x_coef_;
  }
  return doubleEqual(x_coef_, other.x_coef_ * coef) &&
         doubleEqual(y_coef_, other.y_coef_ * coef) &&
         doubleEqual(free_coef_, other.free_coef_ * coef);
}

double Line::signedDist(const Point& point) const {
  return (point.x * x_coef_ + point.y * y_coef_ + free_coef_) /
         std::sqrt(x_coef_ * x_coef_ + y_coef_ * y_coef_);
}