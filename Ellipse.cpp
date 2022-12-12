#include "Ellipse.h"

Ellipse::Ellipse(const Point& focus1, const Point& focus2,
                 double focus_dist_sum)
    : focus1_(focus1_), focus2_(focus2_), big_axis_(focus_dist_sum) {}

std::pair<Point, Point> Ellipse::focuses() const { return {focus1_, focus2_}; }

Point Ellipse::center() const { return (focus1_ + focus2_) / 2; }

double Ellipse::halfBigAxis() const { return big_axis_ / 2; }

double Ellipse::halfSmallAxis() const {
  return std::sqrt((big_axis_ / 2) * (big_axis_ / 2) -
                   focus1_.dist(center()) * focus1_.dist(center()));
}

double Ellipse::eccentricity() const {
  return std::sqrt(halfBigAxis() * halfBigAxis() -
                   halfSmallAxis() * halfSmallAxis()) /
         halfBigAxis();
}

std::pair<Line, Line> Ellipse::directrices() const {
  Point vec = focus1_ - center();
  vec.normalize();
  vec = vec * halfBigAxis() / eccentricity();
  Point norm(-vec.y, vec.x);
  Line dir1(center() + vec, center() + vec + norm);
  Line dir2(center() - vec, center() - vec + norm);
  return {dir1, dir2};
}

double Ellipse::perimeter() const {
  double a = halfBigAxis(), b = halfSmallAxis();
  double h = (a - b) * (a - b) / (a + b) / (a + b);
  return M_PI_2f64 * 2 * (a + b) * (1 + 3 * h / (10 + std::sqrt(4 - 3 * h)));
}

double Ellipse::area() const {
  return M_PI_2f64 * 2 * halfBigAxis() * halfSmallAxis();
}

bool Ellipse::isSameType(const Shape& other) const {
  return dynamic_cast<const Ellipse*>(&other) != nullptr;
}

bool Ellipse::isEqual(const Shape& other) const {
  if (!isSameType(other)) return false;
  const Ellipse& other_e = dynamic_cast<const Ellipse&>(other);
  return (big_axis_ == other_e.big_axis_ &&
          ((focus1_ == other_e.focus1_ && focus2_ == other_e.focus2_) ||
           (focus1_ == other_e.focus2_ && focus2_ == other_e.focus1_)));
}

bool Ellipse::isCongruentTo(const Shape& other) const {
  return isSimilarTo(other) && doubleEqual(area() / other.area(), 1);
}

bool Ellipse::isSimilarTo(const Shape& other) const {
  if (!isSameType(other)) return false;
  const Ellipse& other_el = dynamic_cast<const Ellipse&>(other);

  return eccentricity() == other_el.eccentricity();
}

bool Ellipse::containsPoint(const Point& point) const {
  return doubleLess(focus1_.dist(point) + focus2_.dist(point), big_axis_);
}

void Ellipse::rotate(const Point& point, double angle) {
  focus1_.rotate(point, angle);
  focus2_.rotate(point, angle);
}

void Ellipse::reflect(const Point& point) {
  focus1_ = point + (point - focus1_);
  focus2_ = point + (point - focus2_);
}

void Ellipse::reflect(const Line& line) {
  focus1_.reflect(line);
  focus2_.reflect(line);
}

void Ellipse::scale(const Point& point, double koef) {
  focus1_.scale(point, koef);
  focus2_.scale(point, koef);
}