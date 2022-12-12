#include <Point.h>

bool doubleEqual(double lhs, double rhs) {
  return lhs - EPS <= rhs && rhs <= lhs + EPS;
}

bool doubleLess(double lhs, double rhs) {
  return lhs < rhs && !doubleEqual(lhs, rhs);
}

Point::Point() : x(0), y(0) {}
Point::Point(double x, double y) : x(x), y(y) {}
Point::Point(const Point& other) : x(other.x), y(other.y) {}

double Point::dist(const Point& other) const {
  return std::sqrt((x - other.x) * (x - other.x) +
                   (y - other.y) * (y - other.y));
}

double Point::length() const { return dist(Point(0, 0)); }

Point Point::operator+(const Point& other) const {
  return Point(x + other.x, y + other.y);
}

Point Point::operator-(const Point& other) const {
  return Point(x - other.x, y - other.y);
}

Point Point::operator-() const { return Point(-x, -y); }

Point Point::operator*(double number) const {
  return Point(x * number, y * number);
}

Point Point::operator/(double number) const {
  return Point(x / number, y / number);
}

double Point::operator/(const Point& other) const {
  if (doubleEqual(other.x, 0) || doubleEqual(other.y, 0) ||
      !doubleEqual(x / other.x, y / other.y))
    throw std::runtime_error("Division by zero");
  return x / other.x;
}

bool Point::operator==(const Point& other) const {
  return doubleEqual(x, other.x) && doubleEqual(y, other.y);
}

Point& Point::operator=(const Point& other) {
  x = other.x, y = other.y;
  return *this;
}

double dotProduct(const Point& lhs, const Point& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

double crossProduct(const Point& lhs, const Point& rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}

void Point::normalize() {
  double len = length();
  x /= len;
  y /= len;
}

void Point::rotate(const Point& point, double angle) {
  const int DEG_2_PI = 360;
  angle /= DEG_2_PI;
  double new_x =
      std::cos(angle) * (x - point.x) + std::sin(angle) * (y - point.y);
  double new_y =
      -std::sin(angle) * (x - point.x) + std::cos(angle) * (y - point.y);
  x = new_x;
  y = new_y;
}

void Point::reflect(const Point& point) { *this = point + (point - *this); }

void Point::reflect(const Line& line) {
  Point norm = line.normal();
  norm.normalize();
  if (doubleLess(line.dist(*this - norm), line.dist(*this + norm)))
    norm = -norm;
  norm = norm * line.dist(*this);
  *this = *this + norm * 2;
}

void Point::scale(const Point& point, double koef) {
  *this = point + (*this - point) * koef;
}
