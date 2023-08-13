#include "WordList.h"
#include <algorithm>
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
        float score = calculateScore(word, points);
        if (score < cutoff) {
            if (heap.count() < maxcount) {
                heap.push(word, score);
            } else if (score < heap.top().score) {
                heap.pushpop(word, score);
            }
        }
    }

    return heap;
}

float WordList::calculateScore(const std::string& word, const std::vector<Point>& points) const {
    // Implement scoring algorithm here
    // You might compare the points to the QWERTY positions of the letters in the word
    if (word.length() != points.size()) {
        return INFINITY;  // or some large value to indicate mismatch in size
    }

    float totalDistance = 0.0;

    for (size_t i = 0; i < word.length(); ++i) {
        char c = word[i];
        Point charPoint = QWERTY[c - 'a']; //lowercase letter

        float dx = charPoint.x - points[i].x;
        float dy = charPoint.y - points[i].y;

        totalDistance += sqrt(dx * dx + dy * dy);
    }

    return totalDistance / word.length();
}
