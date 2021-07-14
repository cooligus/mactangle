#pragma once
#include <vector> //required for SC::Aggregate

namespace SC {
  //following here are several collision primitives:
  //Point, Rect, Line, Circle, and Triangle.
  //These are mostly simple structs and do not have
  //special behavior.

  struct Point {
    float x, y;
  };

  //Rect has helper functions for treating it as an
  //x,y,width,height rect, as that is more convenient
  //for some applications.
  //The raw representation is left,right,top,bottom, though,
  //as that is more convenient for acting on during testing.
  //The floats can be accessed directly, so the functions
  //are optional.
  struct Rect {
    float left, top, right, bottom;

    //accessors
    float x() const { return left; }
    float y() const { return top;  }
    float width() const  { return right - left; }
    float height() const { return bottom - top; }

    //mutators
    void x(float val) {
      right = val + width();
      left = val;
    }

    void y(float val) {
      bottom = val + height();
      top = val;
    }

    void width(float val)  { right = left + val; }
    void height(float val) { bottom = top + val; }

  };

  struct Line {
    Point a;
    Point b;
  };

  struct Circle {
    Point center;
    float radius;
  };

  struct Triangle {
    //Winding order is not important.
    Point a, b, c;
  };

  //The aggregate is a collection of primitive colliders that behave
  //as a single collider. This can be used to create complex shapes.
  struct Aggregate {
    std::vector<Point>    points;
    std::vector<Circle>   circles;
    std::vector<Rect>     rects;
    std::vector<Line>     lines;
    std::vector<Triangle> triangles;

    //move all members by dx,dy (relative)
    void move(float dx, float dy);
  };

  //Hereafter are the testOverlap() functions, which cover the range of possible
  //collider type pairs. If the two colliders passed to the function overlap one
  //another then the function will return true. Otherwise it returns false.
  bool testOverlap(const Point& a, const Point& b);
  bool testOverlap(const Point& a, const Rect& b);
  bool testOverlap(const Point& a, const Line& b);
  bool testOverlap(const Point& a, const Circle& b);
  bool testOverlap(const Point& a, const Triangle& b);
  inline bool testOverlap(const Rect& a, const Point& b) { return testOverlap(b, a); }
  bool testOverlap(const Rect& a, const Rect& b);
  bool testOverlap(const Rect& a, const Line& b);
  bool testOverlap(const Rect& a, const Circle& b);
  bool testOverlap(const Rect& a, const Triangle& b);
  inline bool testOverlap(const Line& a, const Point& b) { return testOverlap(b, a); }
  inline bool testOverlap(const Line& a, const Rect& b)  { return testOverlap(b, a); }
  bool testOverlap(const Line& a, const Line& b);
  bool testOverlap(const Line& a, const Circle& b);
  bool testOverlap(const Line& a, const Triangle& b);
  inline bool testOverlap(const Circle& a, const Point& b) { return testOverlap(b, a); }
  inline bool testOverlap(const Circle& a, const Rect& b)  { return testOverlap(b, a); }
  inline bool testOverlap(const Circle& a, const Line& b)  { return testOverlap(b, a); }
  bool testOverlap(const Circle& a, const Circle& b);
  bool testOverlap(const Circle& a, const Triangle& b);
  inline bool testOverlap(const Triangle& a, const Point& b)  { return testOverlap(b, a); }
  inline bool testOverlap(const Triangle& a, const Rect& b)   { return testOverlap(b, a); }
  inline bool testOverlap(const Triangle& a, const Line& b)   { return testOverlap(b, a); }
  inline bool testOverlap(const Triangle& a, const Circle& b) { return testOverlap(b, a); }
  bool testOverlap(const Triangle& a, const Triangle& b);

  template<class T>
  bool testOverlap(const Aggregate& a, const T& b) {
    for(auto& p : a.points)    { if(testOverlap(p, b)) { return true; } }
    for(auto& c : a.circles)   { if(testOverlap(c, b)) { return true; } }
    for(auto& r : a.rects)     { if(testOverlap(r, b)) { return true; } }
    for(auto& l : a.lines)     { if(testOverlap(l, b)) { return true; } }
    for(auto& t : a.triangles) { if(testOverlap(t, b)) { return true; } }
    return false;
  }

  inline bool testOverlap(const Point& a,    const Aggregate& b) { return testOverlap(b,a); }
  inline bool testOverlap(const Rect& a,     const Aggregate& b) { return testOverlap(b,a); }
  inline bool testOverlap(const Line& a,     const Aggregate& b) { return testOverlap(b,a); }
  inline bool testOverlap(const Circle& a,   const Aggregate& b) { return testOverlap(b,a); }
  inline bool testOverlap(const Triangle& a, const Aggregate& b) { return testOverlap(b,a); }

}
