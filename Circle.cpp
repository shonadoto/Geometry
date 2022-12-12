#include "Circle.h"

Circle::Circle(const Point& point, double radius)
    : Ellipse(point, point, 2 * radius) {}

Circle::Circle(const Point& point1, const Point& point2, const Point& point3)
    : Ellipse(Point(0, 0), Point(0, 0), 0) {
  double x12 = point1.x - point2.x;
  double x23 = point2.x - point3.x;
  double x31 = point3.x - point1.x;
  double y12 = point1.y - point2.y;
  double y23 = point2.y - point3.y;
  double y31 = point3.y - point1.y;
  double z1 = point1.x * point1.x + point1.y * point1.y;
  double z2 = point2.x * point2.x + point2.y * point2.y;
  double z3 = point3.x * point3.x + point3.y * point3.y;
  double zx = y12 * z3 + y23 * z1 + y31 * z2;
  double zy = x12 * z3 + x23 * z1 + x31 * z2;
  double z = x12 * y31 - y12 * x31;
  Point center(-zx / (2 * z), zy / (2 * z));
  focus1_ = center;
  focus2_ = center;
  big_axis_ = 2 * center.dist(point1);
}

double Circle::radius() const { return big_axis_ / 2; }