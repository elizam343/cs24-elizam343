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

    for (std::string str : mWords) {
        bool isValid = true;
        float tot = 0.0;
        int lengthDifference = std::abs(static_cast<int>(points.size()) - static_cast<int>(str.length()));

        if (lengthDifference > 1) {
            // Skip words that have a length difference greater than 1 from the points
            continue;
        }

        size_t comparisonLength = std::min(points.size(), str.length());

        for (size_t i = 0; i < comparisonLength; i++) {
            if (str[i] < 'a' || str[i] > 'z') {
                // Handle non-lowercase characters
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

        float penalty = 1.0;  // No penalty by default

        // If lengths differ by 1, apply a penalty to the score
        if (lengthDifference == 1) {
            penalty = 0.9;  // Adjust this value based on how strongly you want to penalize mismatches
        }

        float avg = (tot / comparisonLength) * penalty;

        if (avg > cutoff) {
            if (heap.count() < maxcount) {
                heap.push(str, avg);
            } else if (avg > heap.top().score) {
                heap.pushpop(str, avg);
            }
        }
    }
    return heap;
}
