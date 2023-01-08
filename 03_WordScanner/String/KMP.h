#pragma once
#include <string>
#include <vector>

inline int* getNext(const std::string& p)
{
    int j = 0;
    int k = -1;
    int size = p.length();
    int* next = new int[size] {-1};
    while (j < size - 1) {
        if (k == -1 || p[j] == p[k]) {
            j++;
            k++;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
    return next;
}

inline std::vector<int> KMP(const std::string& T, const std::string& p)
{
    int i = 0;
    int j = 0;
    int* next = getNext(T);
    std::vector<int> result;

    while (i < T.length() && j < p.length()) {
        if (j == -1 || T[i] == p[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    // If found matched substring:
    if (j == p.length()) {
        // Store the position to vector {result}:
        result.push_back(i - j);
        // Keep searching.
        j = next[j - 1];
        --i;
    }
    delete[] next;
    return result;
}
