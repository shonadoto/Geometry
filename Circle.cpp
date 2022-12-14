#include "Circle.h"

Circle::Circle(const Point& point, double radius)
    : Ellipse(point, point, 2 * radius) {}

Circle::Circle(const Point& point1, const Point& point2, const Point& point3)
    : Ellipse(Point(0, 0), Point(0, 0), 0) {
  Point A = point1, B = point2, C = point3;
  double D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
  Point center(((A.x * A.x + A.y * A.y) * (B.y - C.y) +
                (B.x * B.x + B.y * B.y) * (C.y - A.y) +
                (C.x * C.x + C.y * C.y) * (A.y - B.y)) /
                   D,
               (-(A.x * A.x + A.y * A.y) * (B.x - C.x) -
                (B.x * B.x + B.y * B.y) * (C.x - A.x) -
                (C.x * C.x + C.y * C.y) * (A.x - B.x)) /
                   D);
  focus1_ = center;
  focus2_ = center;
  big_axis_ = 2 * center.dist(point1);
}

double Circle::radius() const { return big_axis_ / 2; }