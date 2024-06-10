#include "WordList.h"

using namespace std;

WordList::WordList(std::istream& stream) {
    string line;
    while(stream >> line) {
        size_t count = 0;
        for(size_t i = 0; i < line.length(); ++i) {
            if(islower(line[i])) {
                count += 1;
            }
        }
        if(count == line.length()) {
            mWords.push_back(line);
        }
    }
}

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap myHeap = Heap(maxcount);
    for(size_t i = 0; i < mWords.size(); ++i) {
        if(mWords[i].length() != points.size()) {
            continue;
        }
        else {
            float score = 0;
            for(size_t j = 0; j < mWords[i].length(); ++j) {
                size_t position = mWords[i][j] - 97;
                Point original = QWERTY[position];
                Point input = points[j];
                score += 1 / (10 * ((original.x - input.x) * (original.x - input.x) + (original.y - input.y) * (original.y - input.y)) + 1);
                
            }
            score = score / mWords[i].length();
            bool check = true;
            for(size_t j = 0; j < myHeap.count(); ++j) {
                if(myHeap.lookup(j).value == mWords[i]) {
                    check = false;
                }
            }
            if(score < cutoff) {
                continue;
            }
            else {
                if(check == false) {
                    continue;
                }
                else if(myHeap.count() != myHeap.capacity()) {
                    myHeap.push(mWords[i], score);
                }
                else {
                    if(score > myHeap.lookup(0).score) {
                        myHeap.pushpop(mWords[i], score);
                    }
                }
            }
        }
    }
    return myHeap;
}

