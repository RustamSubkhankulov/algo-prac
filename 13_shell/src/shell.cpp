#include <iomanip>
#include <iostream>
#include <vector>

static const float EPS = 1E-6;

struct Point {

public:
  int x, y;

  Point(int x_coord = 0, int y_coord = 0):
  x(x_coord),
  y(y_coord) {}

  float len2() const { 
    return x*x + y*y; 
  }

  float polarAngle() const {
    return atan2(y, x);
  }

  Point& operator+=(const Point& that) {

    x += that.x;
    y += that.y;

    return *this;
  }

  Point& operator-=(const Point& that) {

    x -= that.x;
    y -= that.y;

    return *this;
  }
};

Point operator+(const Point& lhs, const Point& rhs) {
  return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

Point operator-(const Point& lhs, const Point& rhs) {
  return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}

bool angle_less(const Point& lhs, const Point& rhs) {

  auto angle_lhs = lhs.polarAngle();
  auto angle_rhs = rhs.polarAngle();

  if (std::abs(angle_lhs - angle_rhs) < EPS) {
    return lhs.len2() < rhs.len2();
  }

  return angle_lhs < angle_rhs;
}

bool is_left_turn(const Point& a, const Point& b, const Point& c) {

  Point q = b - a;
  Point w = c - b;

  return q.x * w.y - w.x * q.y > EPS;
}

int main() {

  int num;
  std::cin >> num;

  std::vector<Point> vec;
  for (int ind = 0; ind < num; ++ind) {

    int x, y;
    std::cin >> x >> y;

    vec.push_back(Point(x,y));
  }

  int center_idx = 0;
  for (int ind = 1; ind < num; ++ind) {

    if (vec[ind].x < vec[center_idx].x) {
      center_idx = ind;

    }
    if (vec[ind].x == vec[center_idx].x 
     && vec[ind].y < vec[center_idx].y) {
      center_idx = ind;
    }
  }

  if (center_idx != 0) {
    std::swap(vec[0], vec[center_idx]);
  }

  Point center = vec[0];  
  vec[0].x = 0;
  vec[0].y = 0;

  for (int ind = 1; ind < num; ++ind) {
    vec[ind] -= center;
  }

  std::sort(std::next(vec.begin()), vec.end(), angle_less);

  int cur, ind;
  for (cur = 1, ind = 2; ind < num; ++ind) {

    if  (cur > 0 && !is_left_turn(vec[cur-1], vec[cur], vec[ind])) {
      --cur;
    }
      
    vec[++cur] = vec[ind];
  }

  float per = 0;
  for (ind = 0; ind < cur; ++ind) {
    per += std::sqrt((vec[(ind == cur) ? 0 : ind+1] - vec[ind]).len2());
  }
  per += std::sqrt((vec[0] - vec[cur]).len2());

  std::cout << std::setprecision(3) << per;
  return 0;
}