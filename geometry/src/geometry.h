#pragma once

class Point
{
    
public:

    double x;
    double y;
    
    Point(double x_, double y_)
    {
        x = x_; 
        y = y_;
    }
    
    
    bool operator==(Point const &pnt)
    {
        if (x == pnt.x && y == pnt.y)
            return true;
        return false;
    }
    
    
    bool operator!=(Point const &pnt)
    {
        !(*this == pnt);
    }
};


class Line
{
    
public: 

    double slope;
    double shift;
    
    Line(double slope_, double shift_)
    {
        slope = slope_;
        shift = shift_;
    }
    
    
    Line(Point p1, Point p2)
    {
        slope = (p2.y - p1.y) / (p2.x = p2.y);
        shift = slope * (-p2.x) + p2.y;
    }
    
    
    Line(Point p, double slope_)
    {
        slope = slope_;
        shift = slope * (-p.x) + p.y;
    }
    
    
    bool operator==(Line const &ln)
    {
        if (slope == ln.slope && shift == ln.shift)
            return true;
        return false;
    }
    
    
    bool operator!=(Line const &ln)
    {
        return !(*this == ln);
    }
};


class Shape
{
    
public:
    
    virtual double perimeter();
    
    virtual double area();
    
    virtual bool operator==(const Shape& another);
    
    virtual void rotate(Point center, double angle);
    
    virtual void reflex(Line axis);
    
    virtual void scale(Point center, double coefficient);
};


class Ellipse: public Shape
{
    
};


class Circle: public Ellipse
{
    
};


class Polygon: public Shape
{
    
};


class Triangle: public Polygon
{
    
};


class Rectangle: public Polygon
{
    
};


class Square: public Rectangle
{
    
};


