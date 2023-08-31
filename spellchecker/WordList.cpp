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

    for (const auto& word : mWords) {
        if (word.length() != points.size()) {
            continue;  // Skip words of different lengths
        }

        float totalScore = 0.0;

        for (size_t i = 0; i < word.length(); ++i) {
            char c = word[i];
            Point charPoint = QWERTY[c - 'a'];  // assume lowercase letter

            float dx = charPoint.x - points[i].x;
            float dy = charPoint.y - points[i].y;
            float distance = sqrt(dx * dx + dy * dy);

            float score = 1 / (10 * distance * distance + 1);
            totalScore += score;
        }

        float averageScore = totalScore / word.length();

        if (averageScore > cutoff) {
            if (heap.count() < maxcount) {
                heap.push(word, averageScore);
            } else if (averageScore > heap.top().score) {
                heap.pushpop(word, averageScore);
            }
        }
        totalScore = 0.0;
    }

    return heap;
}

