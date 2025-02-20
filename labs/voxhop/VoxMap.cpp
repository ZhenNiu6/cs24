#include "VoxMap.h"
#include "Errors.h"


string hexCharToBin(char hexChar) {
    string result;
    int value;

    if (hexChar >= '0' && hexChar <= '9') {
        value = hexChar - '0';
    } 
    else {
        value = hexChar - 'a' + 10;
    }

    for (int i = 3; i >= 0; --i) {
        result += ((value >> i) & 1) ? '1' : '0';
    }

    return result;
}

VoxMap::VoxMap(std::istream& stream) {
  string line;
  int test = 0;
  width = 0;
  depth = 0;
  height = 0;
  while (stream >> line) {
    if(line[0] == '\0') {
      continue;
    }
    if(test < 3) {
      if(test == 0) {
        width = stoi(line);
      }
      else if(test == 1) {
        depth = stoi(line);
      }
      else {
        height = stoi(line);
      }
      test += 1;
    }
    else {
      for(size_t i = 0; i < line.length(); ++i) {
        mymap.append(hexCharToBin(line[i]));
      }
    }
  }

}

VoxMap::~VoxMap() {

}

size_t VoxMap::position(Point d) {
  size_t result = width * depth * d.z + width * d.y + d.x;
  return result;
}

size_t VoxMap::position(int w, int d, int h) const {
  size_t result = width * depth * h + width * d + w;
  return result;
}

size_t VoxMap::down_position(size_t current) {
  return current - width * depth;
}


Route VoxMap::route(Point src, Point dst) {
  Route result;

  size_t src_pos = position(src);
  size_t dst_pos = position(dst);
  if(src.x < 0 || src.x >= width || src.y < 0 || src.y >= depth || src.z <= 0 || src.z >= height || mymap[src_pos] == '1' || mymap[down_position(src_pos)] == '0') {
    throw InvalidPoint(src);
  }
  else if(dst.x < 0 || dst.x >= width || dst.y < 0 || dst.y >= depth || dst.z <= 0 || dst.z >= height || mymap[dst_pos] == '1' || mymap[down_position(dst_pos)] == '0') {
    throw InvalidPoint(dst);
  }
  else {
    std::vector<Move> moves = {Move::NORTH, Move::EAST, Move::SOUTH, Move::WEST};
    std::queue<std::pair<Point, Route> > q; 
    std::unordered_set<Point, PointHash> visited;

    q.push({src, {}});
    visited.insert(src);

    while(!q.empty()){
        auto current = q.front();
        Point current_point = current.first;
        Route current_route = current.second;
        q.pop(); // remove the current point from the queue
        if((current_point.x == dst.x) && (current_point.y == dst.y) && (current_point.z == dst.z)){
            return current_route;
        }
        for(auto move: moves){
            
            Point next_point = current_point;
            switch (move) {
                case Move::NORTH:
                    // next_point.y--;
                    next_point.y = next_point.y + (~1 + 1);
                    break;
                case Move::EAST:
                    next_point.x++;
                    break;
                case Move::SOUTH:
                    next_point.y++;
                    break;
                case Move::WEST:
                    // next_point.x--;
                    next_point.x = next_point.x + (~1 + 1);
                    break;
            }
            if((!bound_check(next_point)) || visited.find(next_point) != visited.end()){
                continue;
            }
            if((mymap[position(next_point.x, next_point.y, next_point.z)] == '0')){
                if(mymap[position(next_point.x, next_point.y, next_point.z + (~1 + 1))] == '0'){
                    Point fall_point = fall(next_point);
                    if((bound_check(fall_point)) && (visited.find(fall_point) == visited.end()) && (mymap[position(fall_point.x, fall_point.y, fall_point.z)] == '0')){
                        Route next_route = current_route;
                        next_route.push_back(move);
                        q.push({fall_point, next_route});
                        visited.insert(fall_point);
                        continue;   
                    }
                }
                else{
                    Route next_route = current_route;
                    next_route.push_back(move);
                    q.push({next_point, next_route});
                    visited.insert(next_point);
                    continue;
                }
            }
            else{
                if(current_point.z < height + (~1 + 1)){
                  if(mymap[position(current_point.x, current_point.y, current_point.z + 1)] == '1'){ // a voxel above
                        continue;
                    }
                }
                else if(next_point.z < height + (~1 + 1)){
                    if(mymap[position(next_point.x, next_point.y, next_point.z + 1)] == '1'){
                        continue;
                    }
                }
                Point jump_point = jump(next_point);
                if((bound_check(jump_point)) && (visited.find(jump_point) == visited.end())){
                    Route next_route = current_route;
                    next_route.push_back(move);
                    q.push({jump_point, next_route});
                    visited.insert(jump_point);
                    continue;
                }
            }
        }
        visited.insert(current_point);
    }
    throw NoRoute(src, dst);
  }
  return result;
}

bool VoxMap::bound_check(Point point) const{
    return ((point.z >= 0) && (point.z < height) && (point.y >= 0) && (point.y < depth) && (point.x >= 0) && (point.x < width));
}

Point VoxMap::jump(Point point) const{
    if(point.z < height + (~1 + 1)){
        if(mymap[position(point.x, point.y, point.z + 1)] == '0') {
            point.z ++;
            return point;
        }
    }
    point.z = -1;
    return point;
}

Point VoxMap::fall(Point point) const{
  
    while (point.z > 0 && mymap[position(point.x, point.y, point.z + (~1 + 1))] == '0') {
        // point.z--;
        point.z = point.z + (~1 + 1);
    }
    // If fell into water or reached the ground, adjust the point accordingly
    if (point.z == 0 || (point.z == 1 && mymap[position(point.x, point.y, 0)] == '0')) {
        point.z = -1; // Mark as invalid
    }
    return point;
}