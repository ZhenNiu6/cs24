#include "Heap.h"
#include <stdexcept>


using namespace std;

Heap::Heap(size_t capacity) {
    mData = new Entry[capacity]();
    mCapacity = capacity;
    mCount = 0;
}

Heap::Heap(const Heap& other) {
    mCapacity = other.mCapacity;
    mCount = other.mCount;
    mData = new Entry[mCapacity];
    for(size_t i = 0; i < mCapacity; ++i) {
        mData[i] = other.mData[i];
    }
}

Heap::~Heap() {
    delete [] mData;
    mCount = 0;
}

size_t Heap::capacity() const {
    return mCapacity;
}

size_t Heap::count() const {
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const {
    if(index >= mCount || mCount == 0) {
        throw out_of_range("Invalid index.");
    }
    else {
        return mData[index];
    }
}

Heap::Entry Heap::pop() {
    if(mCount == 0) {
        throw underflow_error("Empty heap.");
    }
    else {
        Entry result = mData[0];
        Entry last;
        for(int i = mCapacity - 1; i >= 0; --i) {
            if(mData[i].score != 0 || mData[i].value.length() != 0) {
                last = mData[i];
                mData[i].score = 0;
                mData[i].value = "";
                break;
            }
        }
        if(mCount > 1) {
            mData[0].score = last.score;
            mData[0].value = last.value;
        }
        mCount -= 1;

        size_t index = 0;

        while(index * 2 + 1 < mCount) {
            if(index * 2 + 2 < mCount && mData[index * 2 + 2].score != 0) {
                if(mData[index * 2 + 1].score <= mData[index * 2 + 2].score) {
                    if(mData[index * 2 + 1].score < mData[index].score) {
                        swap(mData[index * 2 + 1], mData[index]);
                        index = index * 2 + 1;
                    }
                    else {
                        break;
                    }
                }
                else {
                    if(mData[index * 2 + 2].score < mData[index].score) {
                        swap(mData[index * 2 + 2], mData[index]);
                        index = index * 2 + 2;
                    }
                    else {
                        break;
                    }
                }
            }
            else {
                if(mData[index * 2 + 1].score < mData[index].score && mData[index * 2 + 1].score != 0) {
                    swap(mData[index * 2 + 1], mData[index]);
                    index = index * 2 + 1;
                }
                else {
                    break;
                }
            }
        }

        return result;
    }
}

void Heap::push(const std::string& value, float score) {
    if(mCount == mCapacity) {
        throw overflow_error("Full heap.");
    }
    else {
        int index = 0;
        for(size_t i = 0; i < mCapacity; ++i) {
            if(mData[i].score == 0 && mData[i].value.length() == 0) {
                mData[i].score = score;
                mData[i].value = value;
                index = i;
                break;
            }
        }
        while((index - 1) / 2 >= 0) {
            if(mData[index].score < mData[(index - 1) / 2].score) {
                swap(mData[index], mData[(index - 1) / 2]);
                index = (index - 1) / 2;
            }
            else {
                break;
            }
        }
        mCount += 1;
    }
}

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if(mCount == 0) {
        throw underflow_error("Empty heap.");
    }
    else {
        Entry result = mData[0];
        mData[0].score = score;
        mData[0].value = value;
        size_t index = 0;

        while(index * 2 + 1 < mCount) {
            if(index * 2 + 2 < mCount && mData[index * 2 + 2].score != 0) {
                if(mData[index * 2 + 1].score <= mData[index * 2 + 2].score) {
                    if(mData[index * 2 + 1].score < mData[index].score) {
                        swap(mData[index * 2 + 1], mData[index]);
                        index = index * 2 + 1;
                    }
                    else {
                        break;
                    }
                }
                else {
                    if(mData[index * 2 + 2].score < mData[index].score) {
                        swap(mData[index * 2 + 2], mData[index]);
                        index = index * 2 + 2;
                    }
                    else {
                        break;
                    }
                }
            }
            else {
                if(mData[index * 2 + 1].score < mData[index].score && mData[index * 2 + 1].score != 0) {
                    swap(mData[index * 2 + 1], mData[index]);
                    index = index * 2 + 1;
                }
                else {
                    break;
                }
            }
        }
        return result;
    }
}

const Heap::Entry& Heap::top() const {
    if(mCount == 0) {
        throw underflow_error("Empty heap.");
    }
    else {
        return mData[0];
    }
}

// int main() {
//     Heap myheap = Heap(3);
//     myheap.push("astegosaurus", 62);
//     myheap.pop();
//     for(size_t i = 0; i < myheap.mCapacity; ++i) {
//         cout << myheap.mData[i].value << '\n';
//     }
//     return 0;
// }