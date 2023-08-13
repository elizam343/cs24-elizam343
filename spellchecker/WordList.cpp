#include "WordList.h"
#include <cmath>

WordList::WordList(std::istream& stream) {
    std::string word;
    while (stream >> word) {
        mWords.push_back(word);
    }
}


Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);

    float tot = 0.0;
    for (std::string str : mWords) {
        if (str.length() != points.size()) {
            continue; // Skip the word if its length doesn't match the number of points.
        }

        bool isValid = true;  // A flag to check if the word contains only lowercase letters

        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] < 'a' || str[i] > 'z') {
                // Handle non-lowercase characters
                // Assuming you want to continue and ignore this word
                tot = 0.0;
                isValid = false;
                break;
            }

            Point charStr = QWERTY[str[i] - 'a'];
            float x_distance = charStr.x - points[i].x;
            float y_distance = charStr.y - points[i].y;
            float distance = sqrt(x_distance * x_distance + y_distance * y_distance);
            float score = 1 / (10 * (distance * distance) + 1);
            tot += score;
        }

        if (!isValid) {
            continue;
        }

        float avg = tot / str.length();

        if (avg > cutoff) {
            if (heap.count() < maxcount) {
                heap.push(str, avg);
            } else if (avg > heap.top().score) {
                heap.pushpop(str, avg);
            }
        }
        tot = 0.0;
    }
    return heap;
}



