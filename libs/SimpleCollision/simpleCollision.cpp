#include "simpleCollision.h"
#include <algorithm>
#include <array>

//A namespace without a name is referred to as an "anonymous" namespace
//and within a cpp file has the same effect as making all of its members
//static: The things declared here will not be available outside this file.
namespace {
  //Epsilon is a value used to compare floating point numbers for equality.
  //Because float is a bit erratic, testing for equality using == is likely
  //to fail in unexpected places. Because of this it is better to select a
  //very low value called 'epsilon' and simply check to see whether the two
  //values being compared are within that distance of one anoter.
  const float EPSILON = 0.001f;

  //get difference between two floats
  float diff(float a, float b) { return abs(a - b); }

  //test two floats for equality
  bool feq(float a, float b) { return diff(a, b) < EPSILON; }

  //square
  float sq(float val) { return val * val; }

  //simple vector for helping out with the math
  struct Vec2f {
    float x, y;

    Vec2f() {};
    Vec2f(float x, float y) : x(x), y(y) {}

    //conversion to/from SC::Point
    Vec2f(const SC::Point& p) : x(p.x), y(p.y) {}
    operator SC::Point() const { return SC::Point{ x, y }; }

    Vec2f& operator+=(const Vec2f& other) {
      x += other.x;
      y += other.y;
      return *this;
    }

    Vec2f operator+(Vec2f other) const {
      return other += *this;
    }

    Vec2f& operator-=(const Vec2f& other) {
      x -= other.x;
      y -= other.y;
      return *this;
    }

    Vec2f operator-(Vec2f other) const {
      auto copy = *this;
      return copy -= other;
    }

    Vec2f& operator*=(float scalar) {
      x *= scalar;
      y *= scalar;
      return *this;
    }

    Vec2f operator*(float scalar) const {
      auto copy = *this;
      copy *= scalar;
      return copy;
    }

    Vec2f& operator/=(float scalar) {
      return operator*=(1.0f / scalar);
    }

    Vec2f operator/(float scalar) const {
      return operator*(1.0f / scalar);
    }

    float dot(const Vec2f& other) const {
      return (x * other.x) + (y * other.y);
    }

    float cross(const Vec2f& other) const {
      return (x * other.y) - (y * other.x);
    }

    float length() const {
      return sqrt(sq(x) + sq(y));
    }

    void normalize() {
      float len = length();
      if(len == 0) { x = 1.0f; y = 0; }
      else { operator/=(len); }
    }

    Vec2f normalized() const {
      auto copy = *this;
      copy.normalize();
      return copy;
    }

    Vec2f getNormal() const {
      return Vec2f{ -y, x }.normalized();
    }

  };

  //Misc utilities
  std::vector<SC::Line> getTriEdges(const SC::Triangle& tri) {
    return { SC::Line{ tri.a, tri.b }, SC::Line{ tri.b, tri.c }, SC::Line{ tri.c, tri.a } };
  }

  SC::Rect getAABB(const SC::Circle& circ) {
    return SC::Rect{
      circ.center.x - circ.radius,
      circ.center.y - circ.radius,
      circ.center.x + circ.radius,
      circ.center.y + circ.radius
    };
  }

  SC::Rect getAABB(const SC::Triangle& tri) {
    return SC::Rect{
      std::min({ tri.a.x, tri.b.x, tri.c.x }),
      std::min({ tri.a.y, tri.b.y, tri.c.y }),
      std::max({ tri.a.x, tri.b.x, tri.c.x }),
      std::max({ tri.a.y, tri.b.y, tri.c.y })
    };
  }

  SC::Rect getAABB(const SC::Line& ln) {
    return SC::Rect{
      std::min({ ln.a.x, ln.b.x }),
      std::min({ ln.a.y, ln.b.y }),
      std::max({ ln.a.x, ln.b.x }),
      std::max({ ln.a.y, ln.b.y })
    };
  }
}

bool SC::testOverlap(const SC::Point& a, const SC::Point& b) {
  //Simply test for equality on both axes.
  if(!feq(a.x, b.x)) { return false; }
  if(!feq(a.y, b.y)) { return false; }
  return true;
}

bool SC::testOverlap(const SC::Point& pt, const SC::Rect& rect) {
  //This is a kind of lazy SAT (separating axis theorem) - rect is
  //axis-aligned, so all we need to do is see if there's a gap on
  //either axis. If not then the shapes overlap.
  if(pt.x < rect.left)   { return false; }
  if(pt.x > rect.right)  { return false; }
  if(pt.y < rect.top)    { return false; }
  if(pt.y > rect.bottom) { return false; }
  return true;
  //If you're a certain kind of person you probably want to compact
  //this into a single line with one return statement.
  //The compiler will do the same thing with this as it would do
  //with that, so I favor readability here.
}

bool SC::testOverlap(const SC::Point& pt, const SC::Line& ln) {
  //Method by Brian Hayes, outlined in 'Beautiful Code'
  //Note that it is very difficult to trigger this test, as it is
  //extremely precise. If this is problematic for your use then a
  //circle v line test with a small, fine-tuned radius can give you
  //greater control over sensitivity.

  auto& a = ln.a;
  auto& b = ln.b;
  auto& c = pt;

  //triangle area = ((Ax-Cx)(By-Cy) - (Bx-Cx)(Ay-Cy)) / 2
  //if area == 0 then vertices are co-linear
  //0 = ((Ax-Cx)(By-Cy) - (Bx-Cx)(Ay-Cy)) / 2
  //2*0 = (Ax-Cx)(By-Cy) - (Bx-Cx)(Ay-Cy)
  //0 = (Ax-Cx)(By-Cy) - (Bx-Cx)(Ay-Cy)
  //(Bx-Cx)(Ay-Cy) = (Ax-Cx)(By-Cy)
  return feq((b.x-c.x)*(a.y-c.y), (a.x-c.x)*(b.y-c.y));
}

bool SC::testOverlap(const SC::Point& pt, const SC::Circle& circ) {
  float xd = pt.x - circ.center.x;
  float yd = pt.y - circ.center.y;

  //sqrt is a very expensive operation so instead of taking the square root
  //to find the distance between the point and the circle's center we just
  //leave it in its squared form and compare it to the square of the radius
  float sqDist = sq(xd) + sq(yd);
  return sqDist < sq(circ.radius);
}

bool SC::testOverlap(const SC::Point& pt, const SC::Triangle& tri) {
  //Strategy here is to take each vertex of the triangle and get the vectors
  //leading to the next vert and the point being tested. The sign of the cross
  //product of those vectors will indicate which side of the triangle edge the
  //point is on. If the point is outside the triangle then the signs will not
  //match, since the point will be on the far side of one or two, but never all
  //three of the lines.
  //Note that the winding order of the triangle may be either direction, so
  //testing for all positive or all negative is no good. Instead we simply check
  //whether the signs are equal to one another.

  //get all involved vertices
  Vec2f a(tri.a);
  Vec2f b(tri.b);
  Vec2f c(tri.c);
  Vec2f d(pt);

  //the triangle edges as vectors
  Vec2f ab = b - a;
  Vec2f bc = c - b;
  Vec2f ca = a - c;

  //vector from each vertex to the test point
  Vec2f ad = d - a;
  Vec2f bd = d - b;
  Vec2f cd = d - c;

  //we get our cross products...
  float i = ab.cross(ad);
  float j = bc.cross(bd);
  float k = ca.cross(cd);

  //extract their signs...
  bool p = signbit(i);
  bool q = signbit(j);
  bool r = signbit(k);

  //and check equality
  return (p == q) && (p == r);
}

bool SC::testOverlap(const SC::Rect& a, const SC::Rect& b) {
  //You'll notice that this is almost the same as Point v Rect,
  //since we're still dealing with axis-aligned edges.
  if(a.right < b.left) { return false; }
  if(a.left > b.right) { return false; }
  if(a.bottom < b.top) { return false; }
  if(a.top > b.bottom) { return false; }
  return true;
}

bool SC::testOverlap(const SC::Rect& rect, const SC::Line& ln) {
  //The strategy here is to clip the line along one axis so that only the part
  //which overlaps the rect on that axis remains. Then we test the remaining part
  //against the rect on the other axis and if there's overlap there then we have
  //collision. Essentially we're checking to see if and section of the line overlaps
  //the rect on all axes. For more information and some illustration check out Jorge
  //Rodriguez's MFGD video at https://www.youtube.com/watch?v=USjbg5QXk3g.
  //(The whole series is great, in case you haven't seen it.)
  
  //figuring out which endpoints of the line are at which axial extremes...
  //This names aren't strictly necessary, but make it easier to visualize.
  Vec2f lineTop = ln.a;
  Vec2f lineBot = ln.b;
  if(lineTop.y > lineBot.y) { std::swap(lineTop, lineBot); }
  Vec2f lineLeft = ln.a;
  Vec2f lineRight = ln.b;
  if(lineLeft.x > lineRight.x) { std::swap(lineLeft, lineRight); }

  //since we have these measures we can construct an AABB for free
  SC::Rect lineHull = SC::Rect{ lineLeft.x, lineTop.y, lineRight.x, lineBot.y };
  //and see if we can get an early-out on the cheap
  if(!testOverlap(rect, lineHull)) { return false; }

  //considering lineBot.y as 0.0 and lineTop.y as 1.0, clip the line such that only the segment
  //which vertically overlaps the rect remains

  //lowSect describes the low point on the line vector - 0 indicates the original lineBot
  //if lowSect becomes 0.5f then the bottom half of the line will be cut off, etc.
  float lowSect = 0.0f;
  if(lineBot.y > rect.bottom) { lowSect = (lineBot.y - rect.bottom) / lineHull.height(); }

  //hiSect describes the high point on the line vector and functions similarly to lowSect.
  //if hiSect is 0.75f then the top quarter of the line will be cut off
  float hiSect = 1.0f;
  if(lineTop.y < rect.top) { hiSect = (lineBot.y - rect.top) / lineHull.height(); }

  //vector from bot to top
  Vec2f span = lineTop - lineBot;

  //get clipped line's endpoints and figure out which is left and right
  SC::Point right(lineBot + (span * lowSect));
  SC::Point left(lineBot + (span * hiSect));
  if(right.x < left.x) { std::swap(left, right); }

  //if the clipped line overlaps the box horizontally then there is a collision
  if(left.x  > rect.right) { return false; }
  if(right.x < rect.left)  { return false; }
  return true;
}

bool SC::testOverlap(const SC::Rect& rect, const SC::Circle& circ) {
  //Several cases to follow require an AABB test, so we can do the AABB test
  //first here as an early-out, and then later on we assume that AABB passes.
  if(!testOverlap(rect, getAABB(circ))) { return false; }

  //determine Voronoi region of circle center, numbered left-to-right, top-to-bottom
  //[clarification] the lines bounding region 4 are the rect we're testing:
  // 0|1|2
  // -+-+-
  // 3|4|5
  // -+-+-
  // 6|7|8

  int region = 0;
  if(circ.center.x > rect.left) {
    region += 1;
    if(circ.center.x > rect.right) { region += 1; }
  }
  if(circ.center.y > rect.top) {
    region += 3;
    if(circ.center.y > rect.bottom) { region += 3; }
  }

  //There are three kinds of cases here, and we know which case we're in based
  //  on the region number:
  //Region 4 - The center of the circle is inside the rect, so there's defintitely
  //  a collision
  //Other even numbered regions - The center of the circle is nearest a corner of
  //  the rect so we test the circle against the point representing that corner.
  //Odd numbered regions - The center of the circle is nearest one of the sides of
  //  the rect, so we need to test the radius against the distance from the center
  //  point to that side. Alternatively, we can do an AABB test against the rect,
  //  which we did earlier and passed, so if we're in an odd numbered region then
  //  we have a collision.

  //So all we really need to do at this point is handle corner region cases...
  switch(region) {
  case 0: return testOverlap(SC::Point{rect.left, rect.top}, circ);
  case 2: return testOverlap(SC::Point{rect.right, rect.top}, circ);
  case 6: return testOverlap(SC::Point{rect.left, rect.bottom}, circ);
  case 8: return testOverlap(SC::Point{rect.right, rect.bottom}, circ);
  }

  //...and we can assume collision for all other cases.
  return true;

}

bool SC::testOverlap(const SC::Rect& rect, const SC::Triangle& tri) {
  //Here we're using a half implementation of Separating Axis Theorem (SAT).
  //The general idea behind SAT is to take the normal of every edge on both
  //polygons, project them onto the one-dimensional axis described by that normal,
  //and then check for a gap between them. If there's a gap anywhere then they're
  //not overlapping. If no normal axis has a gap then the polygons are overlapping.
  //In this case we don't need to take the normals of the rect because it's axis
  //aligned, so we can just do an AABB test for the rect and then do the triangle's
  //half of SAT.

  //AABB test serves as SAT for the rect's normals since it's edges are all axis-aligned.
  if(!testOverlap(rect, getAABB(tri))) { return false; }

  //get triangle's edge normals
  std::vector<Vec2f> triNormals = {
    (Vec2f(tri.b) - tri.a).getNormal(),
    (Vec2f(tri.c) - tri.b).getNormal(),
    (Vec2f(tri.a) - tri.c).getNormal()
  };

  //get the vertices of the rect so we can project them onto the normals
  std::vector<Vec2f> rectVerts = {
    { rect.left, rect.top },
    { rect.left, rect.bottom },
    { rect.right, rect.top },
    { rect.right, rect.bottom }
  };

  //for each normal, project both polygons into its 1D space and then check
  //for gaps between the two shapes. Any gap means that the polygons are not
  //overlapping: They have at least one separating axis.
  for(auto axis : triNormals) {
    //we're going to find the high and low extents of both polys in the 1D space
    float triLo = std::numeric_limits<float>::max();
    float triHi = std::numeric_limits<float>::lowest();
    float recLo = std::numeric_limits<float>::max();
    float recHi = std::numeric_limits<float>::lowest();

    //project the rect verts onto the axis and find the low and high points
    for(auto vert : rectVerts) {
      float proj = axis.dot(vert);
      recLo = std::min(proj, recLo);
      recHi = std::max(proj, recHi);
    }

    //same for the triangle
    for(Vec2f vert : { tri.a, tri.b, tri.c }) {
      float proj = axis.dot(vert);
      triLo = std::min(proj, triLo);
      triHi = std::max(proj, triHi);
    }

    //check for gaps between the two
    if(recLo > triHi) { return false; }
    if(recHi < triLo) { return false; }
  }

  //shapes were not seperated by any reasonable axis, so they must be overlapping
  return true;
}

bool SC::testOverlap(const SC::Line& a, const SC::Line& b) {
  //if segments intersect then the points of 'a' will be on opposite sides
  //of 'b' and the points of 'b' will be on opposite sides of 'a', as described
  //at http://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

  //However, I'm skipping the special cases here and just allowing the floating
  //point approximation of continuous values to manage it, which does reasonably
  //well. I'm also simply comparing cross product signs instead of doing the
  //heavier orientation testing, and letting the colinear cases handle themselves.

  Vec2f aSpan = Vec2f(a.b) - a.a;
  //we cross the vector representing line 'a' with the vector from a.a to b.a...
  float axba = aSpan.cross(Vec2f(b.a) - a.a);
  //...then b.b
  float axbb = aSpan.cross(Vec2f(b.b) - a.a);
  //and then just check for sign equality
  if(signbit(axba) == signbit(axbb)) { return false; }

  //same thing the other way around
  Vec2f bSpan = Vec2f(b.b) - b.a;
  float bxaa = bSpan.cross(Vec2f(a.a) - b.a);
  float bxab = bSpan.cross(Vec2f(a.b) - b.a);
  if(signbit(bxaa) == signbit(bxab)) { return false; }

  return true;
}

bool SC::testOverlap(const SC::Line& ln, const SC::Circle& circ) {
  //handle degenerate line since we normalize later (which would divide by zero)
  if(testOverlap(ln.a, ln.b)) { return testOverlap(ln.a, circ); }

  //get the axis described by the line
  Vec2f dir = Vec2f(ln.b) - ln.a;
  float length = dir.length(); //nab the line's length before normalizing the vector
  dir /= length;

  //get the vector from point a to the circle's center
  Vec2f toCenter = Vec2f(circ.center) - ln.a;

  //We're going to project the centerpoint onto the axis described by the line.
  //In order to do that we have a normalized vector describing that axis (dir), and
  //we get the dot product of that vector and the vector from ln.a to circ.center.
  //The resulting value will be the length of the vector from  ln.a to the projected
  //point. That is, dir * dotProd == projectedPoint.
  //Considering this, we know that the projection of ln on that axis extends from zero
  //to 'length', so before we do the multiplication to get the projected point we can
  //check to see if dotProd is between those bounds. If not then we can just do a 
  //circle v point test on the nearest endpoint of ln and then call it a day.
  //If it is between the endpoints then we finish calculating the projected point and
  //test against that instead.

  //start projecting the circle's center onto the line's axis
  float dotProd = dir.dot(toCenter);

  //dp less than zero means the projection is off the line on the A side, so point test vs A
  if(dotProd < 0)      { return testOverlap(ln.a, circ); }
  
  //dp greater than 'length' means the projection is off the line on the B side, so point test B
  if(dotProd > length) { return testOverlap(ln.b, circ); }

  //otherwise finish projecting and point test the circle vs the projected point
  Point proj = (dir * dotProd) + ln.a;
  return testOverlap(proj, circ);
}

bool SC::testOverlap(const SC::Line& ln, const SC::Triangle& tri) {
  //if either endpoint is inside then collision
  if(testOverlap(ln.a, tri)) { return true; }
  if(testOverlap(ln.b, tri)) { return true; }
  
  //otherwise check edges against line
  for(auto edge : getTriEdges(tri)) {
    if(testOverlap(edge, ln)) { return true; }
  }

  return false;
}

bool SC::testOverlap(const SC::Circle& a, const SC::Circle& b) {
  //circle vs circle is essentially checking to see if the distance
  //between centerpoints is greater than the sum of the radii.
  //Rather than do that explicitly we can just transfer the full radius
  //to one circle and delegate to circle v point.
  SC::Circle copy = b;
  copy.radius += a.radius;
  return testOverlap(a.center, copy);
}

bool SC::testOverlap(const SC::Circle& circ, const SC::Triangle& tri) {
  //if centerpoint is inside then collide
  if(testOverlap(circ.center, tri)) { return true; }

  //otherwise test against edges
  for(auto edge : getTriEdges(tri)) {
    if(testOverlap(edge, circ)) { return true; }
  }

  return false;
}

bool SC::testOverlap(const SC::Triangle& a, const SC::Triangle& b) {
  //This is a full SAT implementation. We can't cheat this time like we did
  //in rect v tri because neither shape is axis aligned.

  //collect all axes to test along
  const std::array<Vec2f, 6> normals = {
    (Vec2f(a.b) - a.a).getNormal(),
    (Vec2f(a.c) - a.b).getNormal(),
    (Vec2f(a.a) - a.c).getNormal(),
    (Vec2f(b.b) - b.a).getNormal(),
    (Vec2f(b.c) - b.b).getNormal(),
    (Vec2f(b.a) - b.c).getNormal()
  };

  const std::array<Vec2f, 3> aVerts = { a.a, a.b, a.c };
  const std::array<Vec2f, 3> bVerts = { b.a, b.b, b.c };

  //for each normal, project both polygons into its 1D space and check for gaps.
  //any gap means that the polygons are not overlapping
  for(auto axis : normals) {
    //we're going to find the high and low extents of both polys in the 1D space
    float alo = std::numeric_limits<float>::max();
    float ahi = std::numeric_limits<float>::lowest();
    float blo = std::numeric_limits<float>::max();
    float bhi = std::numeric_limits<float>::lowest();

    for(auto vert : aVerts) {
      float proj = axis.dot(vert);
      alo = std::min(proj, alo);
      ahi = std::max(proj, ahi);
    }

    for(auto vert : bVerts) {
      float proj = axis.dot(vert);
      blo = std::min(proj, blo);
      bhi = std::max(proj, bhi);
    }

    //check for gaps
    if(alo > bhi) { return false; }
    if(ahi < blo) { return false; }
  }

  //shapes are not seperated by any reasonable axis, so they must be overlapping
  return true;
}

//helper function for moving an aggregate
void SC::Aggregate::move(float dx, float dy) {
  for(auto& p : points) {
    p.x += dx;
    p.y += dy;
  }

  for(auto& c : circles) {
    c.center.x += dx;
    c.center.y += dy;
  }

  for(auto& r : rects) {
    r.x(r.x() + dx);
    r.y(r.y() + dy);
  }

  for(auto& l : lines) {
    l.a.x += dx;
    l.a.y += dy;
    l.b.x += dx;
    l.b.y += dy;
  }

  for(auto& t : triangles) {
    t.a.x += dx;
    t.a.y += dy;
    t.b.x += dx;
    t.b.y += dy;
    t.c.x += dx;
    t.c.y += dy;
  }

}

