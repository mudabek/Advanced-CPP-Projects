#pragma once

#include <cmath>
#include <iostream>
#include <vector>

double PI = 2 * acos(0.0);



class Point {

public:
  double x;
  double y;

  Point(double x_, double y_) : x(x_), y(y_) {}

  Point(const Point &copy) {
    x = copy.x;
    y = copy.y;
  }

  Point &operator=(const Point &pnt) {
    if (pnt == *this)
      return *this;

    x = pnt.x;
    y = pnt.y;

    return *this;
  }

  bool operator==(Point const &pnt) const {
    if (x == pnt.x && y == pnt.y)
      return true;
    return false;
  }

  bool operator!=(Point const &pnt) const { !(*this == pnt); }

  double distance(const Point &pnt) {
    return sqrt((x - pnt.x) * (x - pnt.x) + (y - pnt.y) * (y - pnt.y));
  }

  Point midpoint(const Point &pnt) {
    double deltaX = abs(x - pnt.x);
    double deltaY = abs(y - pnt.y);

    double midX, midY;

    x < pnt.x ? midX = x + deltaX / 2 : midX = pnt.x + deltaX / 2;
    y < pnt.y ? midY = y + deltaY / 2 : midY = pnt.y + deltaY / 2;

    return Point(midX, midY);
  }
};

class Line {

public:
  double slope;
  double shift;

  Line(double slope_, double shift_) : slope(slope_), shift(shift_) {}

  Line(Point p1, Point p2) {
    slope = (p2.y - p1.y) / (p2.x = p2.y);
    shift = slope * (-p2.x) + p2.y;
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

  bool operator==(Line const &ln) const {
    if (slope == ln.slope && shift == ln.shift)
      return true;
    return false;
  }

  bool operator!=(Line const &ln) const { return !(*this == ln); }
};

//helper for construction rectangle
double rectHelper(double x, double y, double w, double l) {
  double root = pow(-1 * y, 2) * (pow(x, 4) + 2 * pow(x, 2) * pow(y, 2) - 2 * pow(x, 2) * pow(l, 2) - 2 * pow(x, 2) * pow(w, 2)
              + pow(y, 4) - 2 * pow(y, 2) * pow(l, 2) - 2 * pow(y, 2) * pow(w, 2) + pow(l , 4) - 2 * pow(l, 2) * pow(w, 2) + pow(w, 4));
              
  return sqrt(root);
}


// Helper function to find line perpendicular to two points
Line perpend(Point &a, Point &b) {
  Line abLine = Line(a, b);
  Point abMid = a.midpoint(b);
  return Line(abMid, -1 / abLine.slope);
}

//helper function for rectangle construction
std::pair<Point, Point> getRectBD(Point a, Point c, double ratio) {
  double diag = a.distance(c);
  double w = diag / sqrt(ratio * ratio + 1);
  double l = w * ratio;
  
  double tranX = a.x;
  double tranY = a.y;
  
  double xSh = c.x - a.x;
  double ySh = c.y - a.y;
  
  double bRoot = rectHelper(xSh, ySh, w, l);
  
  double bX = (1 / (2 * (pow(xSh, 2) + pow(ySh, 2)))) * (pow(xSh, 3) - 
              bRoot + xSh * pow(ySh, 2) + xSh * pow(l, 2) - xSh * pow(w, 2));
  double bY = (1 / (2 * ySh * (pow(xSh, 2) + pow(ySh, 2)))) * (pow(xSh, 2) * pow(ySh, 2) + 
              xSh * bRoot + pow(ySh, 4) + pow(ySh, 2) * pow(l, 2) - pow(ySh, 2) * pow(w, 2));
  Point b = Point(bX + xSh, bY + ySh);
  
  double bcSlope = Line(c, b).slope;
  Line ad = Line(a , bcSlope);
  Line bcPerpend = perpend(b, c);
  Point d = ad.intersect(bcPerpend);
  
  return std::pair<Point, Point> (b, d);
}

class Shape {

public:
  virtual double perimeter();

  virtual double area();

  virtual bool operator==(const Shape &another);

  virtual void rotate(Point center, double angle);

  virtual void reflex(Line axis);

  virtual void scale(Point center, double coefficient);
};

class Ellipse : public Shape {

public:
  Point foc1;
  Point foc2;
  double mjor;

  Ellipse(Point foc1_, Point foc2_, double mjor_)
      : foc1(foc1_), foc2(foc2_), mjor(mjor_) {}

  Point center() { return foc1.midpoint(foc2); }

  std::pair<Point, Point> focuses() {
    return std::pair<Point, Point>(foc1, foc2);
  }

  double eccentricity() { return center().distance(foc1) / mjor / 2; }
  
  //https://www.mathsisfun.com/geometry/ellipse-perimeter.html
  double perimeter() {
    double a = mjor / 2;
    double b = sqrt(pow(mjor, 2) - pow(foc1.distance(foc2), 2)) / 2;
    double h = pow(a - b, 2) / pow(a + b, 2);
    double kern = 1 + 3 * h / (10 + sqrt(4 - 3 * h));
    return PI * (a + b) * kern;
  }
  
  double area() {
    double a = mjor / 2;
    double b = sqrt(pow(mjor, 2) - pow(foc1.distance(foc2), 2)) / 2;
    return PI * a * b;
  }
  
  bool operator==(const Ellipse& another) {
    if (another.foc1 == foc1 && another.foc2 == foc2 && another.mjor == mjor)
      return true;
    return false;
  }
  
  void rotate(Point center, double angle) {
    
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

  int verticesCount() { return vertices.size(); }

  std::vector<Point> getVertices() { return vertices; }
};

class Triangle : public Polygon {

public:
  Triangle(Point a, Point b, Point c) : Polygon({a, b, c}) {}

  double circumRadius() {
    Point a = vertices[0];
    Point b = vertices[1];
    Point c = vertices[2];

    double ab = a.distance(b);
    double ac = a.distance(c);
    double bc = b.distance(c);

    double s = 0.5 * (ab + ac + bc);
    double radius =
        (ab * ac * bc) / (4 * sqrt(s * (s - ab) * (s - ac) * (s - bc)));

    return radius;
  }

  // https://math.libretexts.org/Bookshelves/Precalculus/Book%3A_Elementary_Trigonometry_(Corral)/02%3A_General_Triangles/2.05%3A_Circumscribed_and_Inscribed_Circles
  Circle circumscribedCircle() {
    double radius = circumRadius();

    Point a = vertices[0];
    Point b = vertices[1];
    Point c = vertices[2];

    Line abPerp = perpend(a, b);
    Line acPerp = perpend(a, c);
    Point center = abPerp.intersect(acPerp);

    return Circle(center, radius);
  }

  // https://math.stackexchange.com/questions/617403/how-many-ways-to-find-the-center-of-an-inscribed-circle
  Circle inscribedCircle() {
    Point a = vertices[0];
    Point b = vertices[1];
    Point c = vertices[2];

    double ab = a.distance(b);
    double ac = a.distance(c);
    double bc = b.distance(c);

    double sumSides = ab + ac + bc;
    double s = 0.5 * sumSides;
    double radius = sqrt((s - ab) * (s - ac) * (s - bc) / s);

    double x = (bc * a.x + ac * b.x + ab * c.x) / (sumSides);
    double y = (bc * a.y + ac * b.y + ab * c.y) / (sumSides);
    Point center = Point(x, y);

    return Circle(center, radius);
  }

  Point centroid() {
    Point a = vertices[0];
    Point b = vertices[1];
    Point c = vertices[2];

    double x = (a.x + b.x + c.x) / 3;
    double y = (a.y + b.y + c.y) / 3;

    return Point(x, y);
  }

  Point orthocenter() {
    Point a = vertices[0];
    Point b = vertices[1];
    Point c = vertices[2];

    Line abPerp = perpend(a, b);
    Line acPerp = perpend(a, c);

    Line abOrtho = Line(c, abPerp.slope);
    Line acOrtho = Line(b, acPerp.slope);

    return abOrtho.intersect(acOrtho);
  }

  Line EulerLine() { return Line(centroid(), orthocenter()); }

  // https://en.wikipedia.org/wiki/Nine-point_center
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
};

class Rectangle : public Polygon {
public:
  Rectangle(Point a, Point c, double ratio) : Polygon({a, getRectBD(a, c, ratio).first, 
                                                    c, getRectBD(a, c, ratio).second}){}
  
  std::pair<Line, Line> diagonals() {
    Line ac = Line(vertices[0], vertices[2]);
    Line bd = Line(vertices[1], vertices[3]);
    return std::pair<Line, Line>(ac, bd);
  }
  
  Point center() {
    std::pair<Line, Line> dPair = diagonals();
    return dPair.first.intersect(dPair.second);
  }
};

class Square : public Rectangle {};





