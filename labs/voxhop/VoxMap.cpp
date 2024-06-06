#include "VoxMap.h"
#include "Errors.h"
#include <bitset>
#include <sstream>
#include <queue>
#include <set>
#include <iostream>

VoxMap::VoxMap(std::istream& stream) {
    std::string width_str, length_str, height_str;
    stream >> width_str >> length_str >> height_str;

    std::istringstream(width_str) >> width;
    std::istringstream(length_str) >> length;
    std::istringstream(height_str) >> height;

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
            // std::cout << line << '\n';
            for(int x = 0; x < width / 4; x ++){
                char digit = line[x];
                // std::cout << digit << '\n';
                int value = (digit >= '0' && digit <= '9') ? digit - '0' : digit - 'A' + 10;
                for (int i = 0; i < 4; ++i) {
                    int bit = (value >> (3 - i)) & 1; // Extract each bit from the hex value
                    if(bit == 0){
                        voxmap[z][y][x * 4 + i] = false; 
                    }
                    else{
                        voxmap[z][y][x * 4 + i] = true; 
                    } 
                    // std::cout << bit << " ";
                }
            }
        }
    }
}

VoxMap::~VoxMap() {}

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
    // std::vector<std::pair<Move, char> > moves = {{Move::NORTH, 'N'}, {Move::EAST, 'E'}, {Move::SOUTH, 'S'}, {Move::WEST, 'W'}};
    std::vector<Move> moves = {Move::NORTH, Move::EAST, Move::SOUTH, Move::WEST};
    std::set<Point> visited;
    std::deque<std::pair<Point, Route> > q; // a double ended queue
    q.push_back({src, {}});
    visited.insert(src);
    // int x = 0;
    while(!q.empty()){
        auto current = q.front();
        Point current_point = current.first;
        Route current_route = current.second;
        q.pop_front(); // remove the current point from the queue
        if((current_point.x == dst.x) && (current_point.y == dst.y) && (current_point.z == dst.z)){
            return current_route;
        }
        
        // x ++;
        // std::cout << x << '\n';
        for(auto move: moves){
            
            Point next_point = current_point;
            switch (move) {
                case Move::NORTH:
                    next_point.y--;
                    break;
                case Move::EAST:
                    next_point.x++;
                    break;
                case Move::SOUTH:
                    next_point.y++;
                    break;
                case Move::WEST:
                    next_point.x--;
                    break;
            }
            
            if(!bound_check(next_point)){
                continue;
            }
            if((bound_check(next_point)) && (!visited.count(next_point)) && (!voxmap[next_point.z][next_point.y][next_point.x])){
                Route next_route = current_route;
                next_route.push_back(move);
                q.push_back({next_point, next_route});
                visited.insert(next_point);
                continue;
            }
            // std::cout << "here" << '\n';
            // std::cout << next_point.x << " " << next_point.y << " " << next_point.z << '\n';
            Point jump_point = jump(next_point);
            // std::cout << "here6" << '\n';
            if((bound_check(jump_point)) && (!visited.count(jump_point)) && (!voxmap[jump_point.z][jump_point.y][jump_point.x])){
                // std::cout << "here2" << '\n';
                Route next_route = current_route;
                next_route.push_back(move);
                q.push_back({jump_point, next_route});
                visited.insert(jump_point);
                // std::cout << "here3" << '\n';
                continue;
            }
            // std::cout << "here7" << '\n';
            Point fall_point = fall(next_point);
            // std::cout << "here8" << '\n';
            if((bound_check(fall_point)) && (!visited.count(fall_point)) && (!voxmap[fall_point.z][fall_point.y][fall_point.x])){
                // std::cout << "here4" << '\n';
                Route next_route = current_route;
                next_route.push_back(move);
                q.push_back({fall_point, next_route});
                visited.insert(fall_point);
                // std::cout << "here5" << '\n';
                continue;
            }
        }
    }
    throw NoRoute(src, dst);
}

Point VoxMap::jump(Point point) const{
    if((point.z < height - 1) && (!voxmap[point.z + 1][point.y][point.x])){
        point.z ++;
    }
    return point;
}

Point VoxMap::fall(Point point) const{
    while((point.z > 1) && (!voxmap[point.z - 1][point.y][point.x])){
        point.z --;
    }
    return point;
}

bool VoxMap::bound_check(Point point) const{
    return ((point.z >= 0) && (point.z < height) && (point.y >= 0) && (point.y < length) && (point.x >= 0) && (point.x < width));
}
