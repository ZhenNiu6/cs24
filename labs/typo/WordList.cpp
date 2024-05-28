#include "WordList.h"
#include "Heap.h"
#include "Point.h"

#include <istream>
#include <string>
#include <cctype>
#include <vector>
#include <cmath>

WordList::WordList(std::istream& stream){
    std::string word;
    while(stream >> word){
        bool lower = true;
        for(size_t i = 0; i < word.length(); i ++){
            if(!islower(word[i])){
                lower = false;
                break;
            }
        }
        if(lower){
            bool exists = false;
            for(const std::string& w: mWords){
                if(w == word){
                    exists = true;
                    break;
                }
            }
            if(!exists){
                mWords.push_back(word);
            }
        }
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const{
    Heap heap(maxcount);
    for(const std::string& word: mWords){
        if(word.length() != points.size()){ // does not match the times of touching screen
            continue;
        }
        float total = 0;
        for(size_t i = 0; i < word.length(); i ++){
            int index = word[i] - 'a';
            float x_coordinate = QWERTY[index].x - points[i].x;
            float y_coordinate = QWERTY[index].y - points[i].y;
            float d = std::sqrt(x_coordinate * x_coordinate + y_coordinate * y_coordinate);
            float score = 1 / (10 * d * d + 1);
            total += score;
        }
        float average = total / word.length();
        if(average >= cutoff){
            if(heap.count() == maxcount){
                if(average < heap.top().score){
                    continue;
                }
                heap.pushpop(word, average);
            }
            else{
                heap.push(word, average);
            }
        }
        // if(heap.count() == maxcount){
        //     if(average < heap.top().score){
        //         continue;
        //     }
        //     heap.pushpop(word, average);
        // }
        // else{
        //     heap.push(word, average);
        // }
    }
    return heap;
}