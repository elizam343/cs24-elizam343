#include "WordList.h"
#include <cmath>

WordList::WordList(std::istream& stream) {
    std::string word;
    while (stream >> word) {
        mWords.push_back(word);
    }
}

#include <cctype>  // For std::tolower

Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap heap(maxcount);

    for (const auto& word : mWords) {
        if (word.length() != points.size()) {
            continue;  // Skip words of different lengths
        }

        float totalScore = 0.0;

        for (size_t i = 0; i < word.length(); ++i) {
            char c = word[i];  // Removed tolower()

            float score;

            if (c >= 'a' && c <= 'z') {
                Point charPoint = QWERTY[c - 'a'];

                float dx = charPoint.x - points[i].x;
                float dy = charPoint.y - points[i].y;
                float distance = sqrt(dx * dx + dy * dy);

                score = 1 / (10 * distance * distance + 1);
            } else {
                // Handle non-lowercase alphabetic characters or assign default score
                // Here, you might want to set a default score or add some specific handling
                // for characters like 'I'. For now, let's assign a default score.
                score = 0.001;  // Assigning a default low score
            }
            
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
    }

    return heap;
}
