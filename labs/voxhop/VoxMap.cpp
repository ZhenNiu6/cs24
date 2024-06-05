#include "VoxMap.h"
#include "Errors.h"
#include <bitset>
#include <sstream>
#include <queue>

VoxMap::VoxMap(std::istream& stream) {
    // int width, length, height; // Use integer variables for dimensions
    std::string width_str, length_str, height_str;

    // Read dimension strings from the stream
    stream >> width_str >> length_str >> height_str;

    // Convert dimension strings to integers
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
    // Point floor_s(src.x, src.y, src.z - 1);
    if((src.z < 0) || (src.y < 0) || (src.x < 0)){
        throw InvalidPoint(src);
    }
    if((voxmap[src.z][src.y][src.x]) || (src.z == 0) || (!voxmap[src.z-1][src.y][src.x]) || (src.x >= width) || (src.x < 0) || (src.y >= length) || (src.y < 0) || (src.z >= height) || (src.z < 0)){
        throw InvalidPoint(src);
    }
    // Point floor_d(dst.x, dst.y, dst.z - 1);
    if((dst.z < 0) || (dst.y < 0) || (dst.x < 0)){
        throw InvalidPoint(src);
    }
    if((voxmap[dst.z][dst.y][dst.x]) || (dst.z == 0) || (!voxmap[dst.z-1][dst.y][dst.x]) || (dst.x >= width) || (dst.x < 0) || (dst.y >= length) || (dst.y < 0) || (dst.z >= height) || (dst.z < 0)){
        throw InvalidPoint(dst);
    }
    throw NoRoute(src, dst);
}

