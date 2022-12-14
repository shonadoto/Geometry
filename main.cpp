#include "geometry.h"

int main() {
  const int ax = -2, ay = 2, bx = 1, by = 2, cx = 3, cy = -1, dx = -1, dy = -2,
            ex = 1, ey = -1, fx = 6, fy = 1;

  Point a(ax, ay);
  Point b(bx, by);
  Point c(cx, cy);
  Point d(dx, dy);
  Point e(ex, ey);

  Triangle tr(d, b, a);
  Circle nine = tr.ninePointsCircle();
  nine.scale(tr.orthocenter(), 2);
  std::cout << (nine == tr.circumscribedCircle());
}