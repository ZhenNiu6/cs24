#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <bitset>
#include <set>
#include <unordered_set>
#include <iostream>

using namespace std;

#include "Point.h"
#include "Route.h"

class VoxMap {
  // Member Variables
  int width;
  int depth;
  int height;
  string mymap;

  // Helper Functions


public:
  VoxMap(std::istream& stream);
  ~VoxMap();

  size_t position(Point d);
  size_t position(int w, int d, int h) const;

  size_t down_position(size_t current);
  // size_t up_position(size_t current);
  // size_t N_position(size_t current);
  // size_t S_position(size_t current);
  // size_t W_position(size_t current);
  // size_t E_position(size_t current);

  // int calculate_distance(const Point& current, const Point& dst);
  int calculate_distance(Point current, Point target);
  Route route(Point src, Point dst);

  bool bound_check(Point point) const;
  Point jump(Point point) const;
  Point fall(Point point) const;

  struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) ^ (std::hash<int>()(p.z) << 1));
    }
  };

};

#endif
