#include "Line.h"

double Line::dist(const Point& point) const {
  return std::abs(x_coef_ * point.x + y_coef_ * point.y + free_coef_) /
         std::sqrt(x_coef_ * x_coef_ + y_coef_ * y_coef_);
}

Point Line::normal() const { return Point(-y_coef_, x_coef_); }

bool Line::isParallel(const Line& other) const {
  try {
    Point(x_coef_, y_coef_) / Point(other.x_coef_, other.y_coef_);
  } catch (...) {
    return true;
  }
  return false;
}

Point Line::intersect(const Line& other) const {
  if (isParallel(other)) throw std::runtime_error("Lines are parallel");
  if (doubleEqual(x_coef_, 0) && doubleEqual(y_coef_, 0))
    throw std::runtime_error("Not a line");
  if (doubleEqual(x_coef_, 0)) {
    return Point(
        (-other.free_coef_ + free_coef_ * other.y_coef_ / y_coef_) / other.x_coef_,
        -free_coef_ / y_coef_);
  }
  if (doubleEqual(y_coef_, 0)) {
    return Point(
        -free_coef_ / x_coef_,
        (-other.free_coef_ + free_coef_ * other.x_coef_ / x_coef_) / other.y_coef_);
  }
  if (doubleEqual(other.x_coef_, 0) || doubleEqual(other.y_coef_, 0))
    return other.intersect(*this);
    double x = (free_coef_ * other.y_coef_ - other.free_coef_ * y_coef_) / (y_coef_ * other.x_coef_ - other.y_coef_ * x_coef_);
    return Point(x, (-free_coef_ - x_coef_ * x) / y_coef_);
}

