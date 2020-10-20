#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

double PI = std::acos(-1);
double EPS = 1e-6;

class Point {

public:
  double x;
  double y;

  Point() : x(0.0), y(0.0) {}

  Point(double x_, double y_) : x(x_), y(y_) {}

  bool operator==(Point const &pnt) const {
    if ((x - pnt.x) < EPS && (y - pnt.y) < EPS)
      return true;
    return false;
  }

  bool operator!=(Point const &pnt) const { !(*this == pnt); }

  double distance(const Point &pnt) {
    return sqrt(pow(x - pnt.x, 2) + pow(y - pnt.y, 2));
  }

  Point midpoint(const Point &pnt) {
    double midX, midY;
    midX = (x + pnt.x) / 2;
    midY = (y + pnt.y) / 2;

    return Point(midX, midY);
  }

  // shift a point
  void shiftPoint(double shiftX, double shiftY) {
    double newX = x + shiftX;
    double newY = y + shiftY;
    x = newX;
    y = newY;
  }

  // rotate point relative to origin
  void rotateHelper(double angle) {
    double sine = std::sin(angle);
    double cosine = std::cos(angle);

    double newX = x * cosine - y * sine;
    double newY = x * sine + y * cosine;

    x = newX;
    y = newY;
  }

  void rotate(Point &p, double angle) {
    shiftPoint(-p.x, -p.y);
    rotateHelper(angle);
    shiftPoint(p.x, p.y);
  }

  void scale(Point &center, double coefficient) {
    double newX = coefficient * (x - center.x) + center.x;
    double newY = coefficient * (y - center.y) + center.y;
    x = newX;
    y = newY;
  }
};

class Line {

public:
  double slope;
  double shift;

  Line(double slope_, double shift_) : slope(slope_), shift(shift_) {}

  Line(Point p1, Point p2) {
    slope = (p2.y - p1.y) / (p2.x - p1.x);
    shift = slope * (-p2.x) + p2.y; //(x3*y2-x2*y3)/(x3-x2)
  }

  Line(Point p, double slope_) {
    slope = slope_;
    shift = slope * (-p.x) + p.y;
  }

  Point intersect(Line ln) {
    double x = (ln.shift - shift) / (slope - ln.slope);
    double y = slope * x + shift;

    return Point(x, y);
  }

  void reflexPoint(Point &p) {
    double d = (p.x + (p.y - shift) * slope) / (1 + pow(slope, 2));
    double newX = 2 * d - p.x;
    double newY = 2 * d * slope - p.y + 2 * shift;
    p.x = newX;
    p.y = newY;
  }

  bool operator==(Line const &ln) const {
    if (slope == ln.slope && shift == ln.shift)
      return true;
    return false;
  }

  bool operator!=(Line const &ln) const { return !(*this == ln); }
};

// Helper function to find line perpendicular to two points
Line perpend(Point &a, Point &b) {
  Line abLine = Line(a, b);
  Point abMid = a.midpoint(b);
  return Line(abMid, -1 / abLine.slope);
}

// helper function for rectangle construction
std::pair<Point, Point> getRectBD(Point a, Point c, double ratio) {
  double diag = a.distance(c);
  double w = diag / sqrt(ratio * ratio + 1);
  double l = w * ratio;
  double deltaXW = (c.x - a.x) * (w / diag);
  double deltaYW = (c.y - a.y) * (w / diag);
  double deltaXL = (c.x - a.x) * (l / diag);
  double deltaYL = (c.y - a.y) * (l / diag);
  double theta = std::atan(l / w);
  double theta2 = std::atan(w / l);

  Point b = Point(a.x + deltaXW, a.y + deltaYW);
  if (deltaXW > 0)
    b.rotate(a, theta);
  else
    b.rotate(a, -theta);

  Point d = Point(a.x + deltaXL, a.y + deltaYL);
  if (deltaXL > 0)
    d.rotate(a, -theta);
  else
    d.rotate(a, theta);

  return std::pair<Point, Point>(b, d);
}

class Shape {

public:
  virtual double perimeter() = 0;

  virtual double area() = 0;

  virtual bool operator==(const Shape &another) const = 0;

  virtual void rotate(Point center, double angle) = 0;

  virtual void reflex(Line axis) = 0;

  virtual void reflex(Point center) = 0;

  virtual void scale(Point center, double coefficient) = 0;
};

class Ellipse : public Shape {

public:
  Point foc1;
  Point foc2;
  double mjor;

  Ellipse(Point foc1_, Point foc2_, double mjor_)
      : foc1(foc1_), foc2(foc2_), mjor(mjor_) {}

  Point center() {
    Point mid = foc1.midpoint(foc2);
    return mid;
  }

  std::pair<Point, Point> focuses() {
    return std::pair<Point, Point>(foc1, foc2);
  }

  double eccentricity() {
    double semiMajor = mjor / 2;
    double centToFoc = center().distance(foc1);
    return centToFoc / semiMajor;
  }

  // https://www.mathsisfun.com/geometry/ellipse-perimeter.html
  double perimeter() override {
    double a = mjor / 2;
    double b = sqrt(pow(mjor, 2) - pow(foc1.distance(foc2), 2)) / 2;
    double h = pow(a - b, 2) / pow(a + b, 2);
    double kern = 1 + 3 * h / (10 + sqrt(4 - 3 * h));
    return PI * (a + b) * kern;
  }

  double area() override {
    double a = mjor / 2;
    double b = sqrt(pow(mjor, 2) - pow(foc1.distance(foc2), 2)) / 2;
    return PI * a * b;
  }

  bool operator==(const Shape &another) const override {

    const Ellipse *ell = dynamic_cast<const Ellipse *>(&another);

    if (foc1 == ell->foc1 && foc2 == ell->foc2 && mjor == ell->mjor)
      return true;

    return false;
  }

  void rotate(Point center, double angle) override {
    foc1.rotate(center, angle);
    foc2.rotate(center, angle);
  }

  void reflex(Point center) override {
    foc1.rotate(center, 180);
    foc2.rotate(center, 180);
  }

  void reflex(Line axis) override {
    axis.reflexPoint(foc1);
    axis.reflexPoint(foc2);
  }

  void scale(Point center, double coefficient) override {
    foc1.scale(center, coefficient);
    foc2.scale(center, coefficient);
    mjor = mjor * coefficient;
  }
};

class Circle : public Ellipse {

public:
  Circle(Point center_, double radius_) : Ellipse(center_, center_, radius_) {}

  double radius() { return mjor; }
};

class Polygon : public Shape {

protected:
  std::vector<Point> vertices;

public:
  Polygon(std::vector<Point> v) : vertices(v) {}

  int verticesCount() const { return vertices.size(); }

  std::vector<Point> getVertices() const { return vertices; }

  Polygon &operator=(const Polygon &poly) {
    if (poly == *this)
      return *this;

    vertices = poly.vertices;

    return *this;
  }

  bool operator==(const Shape &another) const override {
    const Polygon *poly = dynamic_cast<const Polygon *>(&another);
    if (verticesCount() != poly->verticesCount())
      return false;

    std::vector<Point> shapeV = poly->getVertices();
    for (Point p : shapeV) {
      if (std::find(vertices.begin(), vertices.end(), p) == vertices.end())
        return false;
    }
    return true;
  }

  bool operator!=(const Shape &another) { return !(*this == another); }

  Point centroid() {
    double sumX = 0;
    double sumY = 0;

    for (Point p : vertices) {
      sumX += p.x;
      sumY += p.y;
    }

    return Point(sumX / vertices.size(), sumY / vertices.size());
  }

  void rotate(Point center, double angle) override {
    for (Point &p : vertices)
      p.rotate(center, angle);
  }

  void reflex(Point center) override {
    for (Point &p : vertices)
      p.rotate(center, 180);
  }

  void reflex(Line axis) override {
    for (Point &p : vertices)
      axis.reflexPoint(p);
  }

  void scale(Point center, double coefficient) override {
    for (Point &p : vertices) {
      p.scale(center, coefficient);
    }
  }

  double perimeter() override {
    Point prev = vertices.back();
    double perim = 0;

    for (Point p : vertices) {
      perim += prev.distance(p);
      prev = p;
    }

    return perim;
  }

  double area() override {
    double area = 0.0;

    for (int i = 0; i < verticesCount(); ++i) {
      Point p1 = i ? vertices[i - 1] : vertices.back();
      Point p2 = vertices[i];
      area += (p1.x - p2.x) * (p1.y + p2.y);
    }
    return area / 2;
  }
};

class Triangle : public Polygon {

public:
  Triangle(Point a, Point b, Point c) : Polygon({a, b, c}) {}
  //https://www.ross.ws/?_writing/articles/Euler%20Line%27s%20Cartesian%20Formula -> all ugly formulas
  double circumRadius() {
    Point A = vertices[0];
    Point B = vertices[1];
    Point C = vertices[2];

    double a = B.distance(C);
    double b = A.distance(C);
    double c = A.distance(B);

    double s = 0.5 * (a + b + c);
    double radius = (a * b * c) / (4 * sqrt(s * (s - a) * (s - b) * (s - c)));

    return radius;
  }

  Circle circumscribedCircle() {
    Point A = vertices[0];
    Point B = vertices[1];
    Point C = vertices[2];

    double a = B.distance(C);
    double b = A.distance(C);
    double c = A.distance(B);

    double x =
        ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
         (B.x * B.x + B.y * B.y) * (C.y - A.y) +
         (C.x * C.x + C.y * C.y) * (A.y - B.y)) /
        (2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)));

    double y =
        ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
         (B.x * B.x + B.y * B.y) * (A.x - C.x) +
         (C.x * C.x + C.y * C.y) * (B.x - A.x)) /
        (2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)));

    Point center = Point(x, y);
    double radius = circumRadius();
    return Circle(center, radius);
  }

  Circle inscribedCircle() {
    Point A = vertices[0];
    Point B = vertices[1];
    Point C = vertices[2];

    double a = B.distance(C);
    double b = A.distance(C);
    double c = A.distance(B);

    double x = a * A.x + b * B.x + c * C.x;
    x /= a + b + c;

    double y = a * A.y + b * B.y + c * C.y;
    y /= a + b + c;
    Point center(x, y);

    double s = (a + b + c) / 2;
    double r = sqrt((s - a) * (s - b) * (s - c) / s);
    return Circle(center, r);
  }

  Point orthocenter() {
    Point A = vertices[0];
    Point B = vertices[1];
    Point C = vertices[2];

    double x, y;

    if (B.y == C.y)
      x = A.x;
    else if (A.y == C.y)
      x = B.x;
    else if (A.y == B.y)
      x = C.x;
    else {
      x = (A.y * A.y * (C.y - B.y) + B.x * C.x * (C.y - B.y) +
           B.y * B.y * (A.y - C.y) + A.x * C.x * (A.y - C.x) +
           C.y * C.y * (B.y - A.y) + +A.x * B.x * (A.y - B.y)) /
          (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    }

    if (B.x == C.x)
      y = A.y;
    else if (A.x == C.x)
      y = B.y;
    else if (A.x == B.x)
      y = C.y;
    else {
      y = (A.x * A.x * (B.x - C.x) + B.y * C.y * (B.x - C.x) +
           B.x * B.x * (C.x - A.x) + A.y * C.y * (C.x - A.x) +
           C.x * C.x * (A.x - B.x) + A.y * B.y * (A.x - B.x)) /
          (A.y * (C.x - B.x) + B.y * (A.x - C.x) + C.y * (B.x - A.x));
    }

    return Point(x, y);
  }

  Circle ninePointsCircle() {
    double radius = circumRadius() / 2;

    Point a = vertices[0];
    Point b = vertices[1];
    Point c = vertices[2];
    Point d = orthocenter();

    double x = (a.x + b.x + c.x + d.x) / 4;
    double y = (a.y + b.y + c.y + d.y) / 4;
    Point center = Point(x, y);

    return Circle(center, radius);
  }

  Line EulerLine() { return Line(ninePointsCircle().center(), centroid()); }

};

class Rectangle : public Polygon {
public:
  Rectangle(Point a, Point c, double ratio)
      : Polygon({a, getRectBD(a, c, ratio).first, c,
                 getRectBD(a, c, ratio).second}) {}

  std::pair<Line, Line> diagonals() {
    Line ac = Line(vertices[0], vertices[2]);
    Line bd = Line(vertices[1], vertices[3]);
    return std::pair<Line, Line>(ac, bd);
  }

  Point center() { centroid(); }
};

class Square : public Rectangle {
public:
  Square(Point a, Point c) : Rectangle(a, c, 1) {}

  Circle circumscribedCircle() {
    double radius = vertices[0].distance(vertices[2]) / 2;
    return Circle(center(), radius);
  }

  Circle inscribedCircle() {
    double radius = vertices[0].distance(vertices[1]) / 2;
    return Circle(center(), radius);
  }
};