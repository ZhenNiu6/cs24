#include "VoxMap.h"
#include "Errors.h"
#include <bitset>
#include <sstream>
#include <queue>
#include <set>
#include <unordered_set>
#include <iostream>

using namespace std;

VoxMap::VoxMap(std::istream& stream) {
    std::string width_str, length_str, height_str;
    stream >> width_str >> length_str >> height_str;
    width = std::stoi(width_str);
    length = std::stoi(length_str);
    height = std::stoi(height_str);
    
    stream.ignore(); // ignore the newline
    voxmap.resize(height);
    for (int z = 0; z < height; ++z) {
        voxmap[z].resize(length);
        for (int y = 0; y < length; ++y) {
            voxmap[z][y].resize(width, false); // Initialize to false
        }
    }

    for(int z = 0; z < height; z ++){
        stream.ignore();
        for(int y = 0; y < length; y ++){
            std::string line;
            std::getline(stream, line);
            for(int x = 0; x < width / 4; x ++){
                char digit = line[x];
                int value = (digit >= '0' && digit <= '9') ? digit - '0' : digit - 'A' + 10;
                for (int i = 0; i < 4; ++i) {
                    int bit = (value >> (3 - i)) & 1; // Extract each bit from the hex value
                    if(bit == 0){
                        voxmap[z][y][x * 4 + i] = false; 
                    }
                    else{
                        voxmap[z][y][x * 4 + i] = true; 
                    } 
                }
            }
        }
    }
}

VoxMap::~VoxMap() {}

int VoxMap::calculate_distance(const Point& current, const Point& dst) {
    return abs(current.x - dst.x) + abs(current.y - dst.y);
}

Route VoxMap::route(Point src, Point dst) {
    if((src.z < 0) || (src.z >= height) || (src.y < 0) || (src.y >= length) || (src.x < 0) || (src.x >= width)){
        throw InvalidPoint(src);
    }
    if((voxmap[src.z][src.y][src.x])){
        throw InvalidPoint(src);
    }
    if(src.z == 0){
        throw InvalidPoint(src);
    }
    if(!voxmap[src.z-1][src.y][src.x]){
        throw InvalidPoint(src);
    }
    if((dst.z < 0) || (dst.y < 0) || (dst.x < 0) || (dst.x >= width) || (dst.y >= length) || (dst.z >= height)){
        throw InvalidPoint(dst);
    }
    if((voxmap[dst.z][dst.y][dst.x])){
        throw InvalidPoint(dst);
    }
    if(dst.z == 0){
        throw InvalidPoint(dst);
    }
    if(!voxmap[dst.z-1][dst.y][dst.x]){
        throw InvalidPoint(dst);
    }
    
    std::priority_queue<std::pair<Point, Route> > best;
    src.distance = calculate_distance(src, dst);
    set_visited.insert(src);
    Point north = Point(src.x, src.y - 1, src.z);
    Point south = Point(src.x, src.y + 1, src.z);
    Point west = Point(src.x - 1, src.y, src.z);
    Point east = Point(src.x + 1, src.y, src.z);
    if(bound_check(north)) {
        north.direction = Move::NORTH;
        north.distance = calculate_distance(north, dst);
        best.push({north, {Move::NORTH}});
    }
    if(bound_check(south)) {
        south.direction = Move::SOUTH;
        south.distance = calculate_distance(south, dst);
        best.push({south, {Move::SOUTH}});
    }
    if(bound_check(west)) {
        west.direction = Move::WEST;
        west.distance = calculate_distance(west, dst);
        best.push({west, {Move::WEST}});
    }
    if(bound_check(east)) {
        east.direction = Move::EAST;
        east.distance = calculate_distance(east, dst);
        best.push({east, {Move::EAST}});
    }

    while(!best.empty()){
        auto next = best.top();
        Point next_point = next.first;
        Route next_route = next.second;
        if((next_point.x == dst.x) && (next_point.y == dst.y) && (next_point.z == dst.z)){
            return next_route;
        }
        best.pop();

        Move mydirection = next.first.direction;
        Point current_point;
        if(mydirection == Move::NORTH) {
            current_point = Point(next_point.x, next_point.y + 1, next_point.z);
        }
        else if(mydirection == Move::SOUTH) {
            current_point = Point(next_point.x, next_point.y - 1, next_point.z);
        }
        else if(mydirection == Move::WEST) {
            current_point = Point(next_point.x + 1, next_point.y, next_point.z);
        }
        else if(mydirection == Move::EAST) {
            current_point = Point(next_point.x - 1, next_point.y, next_point.z);
        }
        if((!bound_check(next_point)) || (set_visited.count(next_point))){
            continue;
        }
        if((!voxmap[next_point.z][next_point.y][next_point.x])){
            if(!voxmap[next_point.z - 1][next_point.y][next_point.x]){
                Point fall_point = fall(next_point);
                if((bound_check(fall_point)) && (!set_visited.count(fall_point)) && (!voxmap[fall_point.z][fall_point.y][fall_point.x])){
                    fall_point.distance = calculate_distance(fall_point, dst);
                    // best.push({fall_point, next_route});
                    set_visited.insert(fall_point);
                    next_point = fall_point;

                    Point next_north = Point(next_point.x, next_point.y - 1, next_point.z);
                    Point next_south = Point(next_point.x, next_point.y + 1, next_point.z);
                    Point next_west = Point(next_point.x - 1, next_point.y, next_point.z);
                    Point next_east = Point(next_point.x + 1, next_point.y, next_point.z);
                    if(bound_check(next_north)) {
                        next_north.direction = Move::NORTH;
                        next_north.distance = calculate_distance(next_north, dst);
                        Route new_route = next_route;
                        new_route.push_back(Move::NORTH);
                        best.push({next_north, new_route});
                    }
                    if(bound_check(next_south)) {
                        next_south.direction = Move::SOUTH;
                        next_south.distance = calculate_distance(next_south, dst);
                        Route new_route = next_route;
                        new_route.push_back(Move::SOUTH);
                        best.push({next_south, new_route});
                    }
                    if(bound_check(next_west)) {
                        next_west.direction = Move::WEST;
                        next_west.distance = calculate_distance(next_west, dst);
                        Route new_route = next_route;
                        new_route.push_back(Move::WEST);
                        best.push({next_west, new_route});
                    }
                    if(bound_check(next_east)) {
                        next_east.direction = Move::EAST;
                        next_east.distance = calculate_distance(next_east, dst);
                        Route new_route = next_route;
                        new_route.push_back(Move::EAST);
                        best.push({next_east, new_route});
                    }
                    
                    continue;
                }  
            }
            else{
                next_point.distance = calculate_distance(next_point, dst);
                // best.push({next_point, next_route});
                set_visited.insert(next_point);

                Point next_north = Point(next_point.x, next_point.y - 1, next_point.z);
                Point next_south = Point(next_point.x, next_point.y + 1, next_point.z);
                Point next_west = Point(next_point.x - 1, next_point.y, next_point.z);
                Point next_east = Point(next_point.x + 1, next_point.y, next_point.z);
                if(bound_check(next_north)) {
                    next_north.direction = Move::NORTH;
                    next_north.distance = calculate_distance(next_north, dst);
                    Route new_route = next_route;
                    new_route.push_back(Move::NORTH);
                    best.push({next_north, new_route});
                }
                if(bound_check(next_south)) {
                    next_south.direction = Move::SOUTH;
                    next_south.distance = calculate_distance(next_south, dst);
                    Route new_route = next_route;
                    new_route.push_back(Move::SOUTH);
                    best.push({next_south, new_route});
                }
                if(bound_check(next_west)) {
                    next_west.direction = Move::WEST;
                    next_west.distance = calculate_distance(next_west, dst);
                    Route new_route = next_route;
                    new_route.push_back(Move::WEST);
                    best.push({next_west, new_route});
                }
                if(bound_check(next_east)) {
                    next_east.direction = Move::EAST;
                    next_east.distance = calculate_distance(next_east, dst);
                    Route new_route = next_route;
                    new_route.push_back(Move::EAST);
                    best.push({next_east, new_route});
                }

                continue;
            }
        }
        else{
            if(current_point.z < height - 1){
                if(voxmap[current_point.z + 1][current_point.y][current_point.x]){ // a voxel above
                    continue;
                }
            }
            else if(next_point.z < height - 1){
                if(voxmap[next_point.z + 1][next_point.y][next_point.x]){
                    continue;
                }
            }
            Point jump_point = jump(next_point);
            if((bound_check(jump_point)) && (!set_visited.count(jump_point))){
                jump_point.distance = calculate_distance(jump_point, dst);
                // best.push({jump_point, next_route});
                set_visited.insert(jump_point);
                next_point = jump_point;

                Point next_north = Point(next_point.x, next_point.y - 1, next_point.z);
                Point next_south = Point(next_point.x, next_point.y + 1, next_point.z);
                Point next_west = Point(next_point.x - 1, next_point.y, next_point.z);
                Point next_east = Point(next_point.x + 1, next_point.y, next_point.z);
                if(bound_check(next_north)) {
                    next_north.direction = Move::NORTH;
                    next_north.distance = calculate_distance(next_north, dst);
                    Route new_route = next_route;
                    new_route.push_back(Move::NORTH);
                    best.push({next_north, new_route});
                }
                if(bound_check(next_south)) {
                    next_south.direction = Move::SOUTH;
                    next_south.distance = calculate_distance(next_south, dst);
                    Route new_route = next_route;
                    new_route.push_back(Move::SOUTH);
                    best.push({next_south, new_route});
                }
                if(bound_check(next_west)) {
                    next_west.direction = Move::WEST;
                    next_west.distance = calculate_distance(next_west, dst);
                    Route new_route = next_route;
                    new_route.push_back(Move::WEST);
                    best.push({next_west, new_route});
                }
                if(bound_check(next_east)) {
                    next_east.direction = Move::EAST;
                    next_east.distance = calculate_distance(next_east, dst);
                    Route new_route = next_route;
                    new_route.push_back(Move::EAST);
                    best.push({next_east, new_route});
                }
                continue;
            }
        }     
    }

    throw NoRoute(src, dst);
}


Point VoxMap::jump(Point point) const{
    if(point.z < height - 1){
        if(!voxmap[point.z + 1][point.y][point.x]){
            point.z ++;
            return point;
        }
    }
    point.z = -1;
    return point;
}

Point VoxMap::fall(Point point) const{
    while (point.z > 0 && !voxmap[point.z - 1][point.y][point.x]) {
        point.z--;
    }
    // If fell into water or reached the ground, adjust the point accordingly
    if (point.z == 0 || (point.z == 1 && !voxmap[0][point.y][point.x])) {
        point.z = -1; // Mark as invalid
    }
    return point;
}

bool VoxMap::bound_check(Point point) const{
    return ((point.z >= 0) && (point.z < height) && (point.y >= 0) && (point.y < length) && (point.x >= 0) && (point.x < width));
}
