#include "Rectangle.h"

Rectangle::Rectangle(const Point& point1, const Point& point2, double relation)
    : Polygon(Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0)) {
  points_[0] = point1, points_[2] = point2;
  Point diagonal = point2 - point1;

  if (doubleLess(relation, 1)) relation = 1 / relation;
  double angle = std::atan(relation);
  Point diagonal = point2 - point1;
  diagonal = diagonal;
  diagonal.rotate(Point(0, 0), angle);
  points_[1] = point1 + diagonal * std::cos(angle);
  diagonal.rotate(Point(0, 0), -M_PI_2f64);
  points_[3] = point1 + diagonal * std::sin(angle);
}

Point Rectangle::center() const { return (points_[0] + points_[2]) / 2; }
std::pair<Line, Line> Rectangle::diagonals() const {
  return {Line(points_[0], points_[2]), Line(points_[1], points_[3])};
}
