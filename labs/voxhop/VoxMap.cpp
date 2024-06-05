#include "VoxMap.h"
#include "Errors.h"
#include <bitset>
#include <sstream>
#include <queue>

// VoxMap::VoxMap(std::istream& stream) {
//   std::string width, length, height;
//   stream >> width >> length >> height;
//   voxmap.resize(height, std::vector<std::vector<std::bitset<4>>>(length, std::vector<std::bitset<4>>(width / 4)));
//   std::string line;
//   std::getline(stream, line); // a newline 
//   for(size_t z = 0; z < height; z ++){ // z-axis
//     std::getline(stream, line);
//     for(size_t y = 0; y < length; y ++){
//       std::getline(stream, line);
//       for(size_t x = 0; x < width / 4; x ++){
//         char digit = line[x];
//         int value = (digit >= '0' && digit <= '9') ? digit - '0' : digit - 'A' + 10;
//         voxmap[z][y][x] = std::bitset<4>(value);
//         // for(size_t i = 0; i < 4; i ++){
//         //   int a = (digit >= '0' && digit <= '9') ? digit - '0' : digit - 'A' + 10;
//         //   int b = 1 << i;
//         //   int c = a & b;
//         //   bool filled;
//         //   if(c != 0){
//         //     filled = true;
//         //   }
//         //   else{
//         //     filled = false;
//         //   }
//         //   voxmap[z][y][x * 4 + i] = filled;
//         // }
//       }
//     }
//   }
// }


VoxMap::VoxMap(std::istream& stream) {
    size_t width, length, height; // Use integer variables for dimensions
    std::string width_str, length_str, height_str;

    // Read dimension strings from the stream
    stream >> width_str >> length_str >> height_str;

    // Convert dimension strings to integers
    std::istringstream(width_str) >> width;
    std::istringstream(length_str) >> length;
    std::istringstream(height_str) >> height;

    stream.ignore(); // ignore the newline
    voxmap.resize(height);
    for(auto& layer: voxmap){
        layer.resize(length);
        for(auto& line: layer){
            line.resize(width / 4);
        }
    }

    for(size_t z = 0; z < height; z ++){
        stream.ignore();
        for(size_t y = 0; y < length; y ++){
            std::string line;
            std::getline(stream, line);
            for(size_t x = 0; x < width; x ++){
                char digit = line[x];
                size_t value = (digit >= '0' && digit <= '9') ? digit - '0' : digit - 'A' + 10;
                for (size_t i = 0; i < 4; ++i) {
                    size_t bit = (value >> (3 - i)) & 1; // Extract each bit from the hex value
                    voxmap[z][y][x * 4 + i] = bit; 
                }
            }
        }
    }

}

VoxMap::~VoxMap() {}

Route VoxMap::route(Point src, Point dst) {
  throw NoRoute(src, dst);
}

