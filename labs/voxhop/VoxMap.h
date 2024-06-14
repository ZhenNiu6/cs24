#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <vector>

#include "Point.h"
#include <unordered_set>


class VoxMap {
  // Member Variables
  std::vector<std::vector<std::vector<bool> > > voxmap;
  
  int width, length, height;

  int calculate_distance(const Point& current, const Point& dst);

  // Helper Functions
  Point jump(Point point) const;
  Point fall(Point point) const;
  bool bound_check(Point point) const;

  struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) ^ (std::hash<int>()(p.z) << 1));
    }
  };
  std::unordered_set<Point, PointHash> set_visited;


public:
  VoxMap(std::istream& stream);
  ~VoxMap();

  Route route(Point src, Point dst);
};

#endif
