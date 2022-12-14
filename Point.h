#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

const double EPS = 1e-10;

bool doubleLess(double, double);
bool doubleEqual(double, double);

class Line;

class Point {
 public:
  double x, y;
  Point();
  Point(double, double);
  Point(const Point&);
  double dist(const Point&) const;
  double length() const;
  Point operator+(const Point&) const;
  Point operator-(const Point&) const;
  Point operator-() const;
  Point operator*(double) const;
  Point operator/(double) const;
  double operator/(const Point&) const;
  bool operator==(const Point&) const;
  bool operator!=(const Point&) const;
  Point& operator=(const Point&);
  void normalize();
  void rotate(const Point&, double angle);
  void reflect(const Point&);
  void reflect(const Line&);
  void scale(const Point&, double koef);
};

class Line {
 private:
  double x_coef_, y_coef_, free_coef_;

 public:
  Line(const Point&, const Point&);
  Line(const Point&, double);
  Line(double, double);
  double dist(const Point&) const;
  double signedDist(const Point&) const;
  Point normal() const;
  Point intersect(const Line&) const;
  bool isParallel(const Line&) const;
  bool operator==(const Line&) const;
};

double dotProduct(const Point&, const Point&);
double crossProduct(const Point&, const Point&);

void swap(Point& lhs, Point& rhs) {
  std::swap(lhs.x, rhs.x);
  std::swap(lhs.y, rhs.y);
}