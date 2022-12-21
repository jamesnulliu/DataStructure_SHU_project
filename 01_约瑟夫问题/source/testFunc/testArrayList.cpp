#include "../../header/arrayList/arrayListWithIterator.h"
#include "../../header/testFunc/testArrayList.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

void array_test1(int N, const int k, const int m, std::ostream* out)
{
    std::string outputStr = {}; // ouput string containing the result

    arrayList<int> arr; // array that holds the resume

    // Push back n elements (1,2,...,n) to {arr}:
    for (int i = 0; i < N; ++i) { arr.push_back(i + 1); }

    int nResume = arr.size(); // number of resume

    // Define 2 lambda functions:
    auto leftRotate = [&nResume, k](int start) ->int { return (nResume + start + k % nResume - 1) % nResume; };
    auto rightRotate = [&nResume, m](int start) ->int { return (nResume + start - m % nResume + 1) % nResume; };

    // Set the initial starting point of x and y:
    int xStart = 0, xTake = 0;
    int yStart = N - 1, yTake = 0;

    while (true) {
        // Calculate index of the x taken and y taken:
        xTake = leftRotate(xStart);
        yTake = rightRotate(yStart);

        if (xTake == yTake) {
            outputStr += (std::to_string(arr[xTake]) + "; ");
            nResume -= 1;
            arr.erase(xTake);
        } else {
            outputStr += (std::to_string(arr[xTake]) + ", " + std::to_string(arr[yTake]) + "; ");
            nResume -= 2;
            // Erase the taken resume:
            arr.erase(std::max(xTake, yTake));
            arr.erase(std::min(xTake, yTake));
        }

        // Following line is the exit of whole while loop.
        if (nResume == 0) { break; }

        // Reset {xStart} and {yStart} based on new array index: @{
        // [Attention] - Here {n} has already been updated.
        if (yTake < xTake) {
            yStart = (nResume + yTake - 1) % nResume;
            xStart = (nResume + xTake - 1) % nResume;
        } else if (yTake > xTake) {
            yStart = (nResume + yTake - 2) % nResume;
            // `xStart = xTake` is also okay
            xStart = (nResume + xTake) % nResume;
        } else {
            yStart = (nResume + yTake - 1) % nResume;
            // `xStart = xTake` is also okay
            xStart = (nResume + xTake) % nResume;
        }
        // @} Reset end.
    }

    // Shrink {outputStr}:
    while (outputStr.back() == ' ' || outputStr.back() == ';') { outputStr.pop_back(); }

    // Output {outputStr} to terminal:
    if (out != nullptr) {
        (*out) << outputStr << std::endl;
    }
}

int array_test2(int N, const int k, const int m, std::ostream* out)
{
    int endingN = 0;

    std::string outputStr = {}; // ouput string containing the result

    arrayList<int> arr; // array that holds the resume

    // Push back n elements (1,2,...,n) to {arr}:
    for (int i = 0; i < N; ++i) { arr.push_back(i + 1); }

    int nResume = arr.size(); // number of remaining resume

    // Define 2 lambda functions:
    auto leftRotate = [&nResume, k](int start) ->int { return (nResume + start + k % nResume - 1) % nResume; };
    auto rightRotate = [&nResume, m](int start) ->int { return (nResume + start - m % nResume + 1) % nResume; };

    // Set the initial starting point of x and y:
    int xStart = 0, xTake = 0;
    int yStart = N - 1, yTake = 0;

    while (true) {
        // Calculate index of the x to take and the y to take:
        xTake = leftRotate(xStart);
        yTake = rightRotate(yStart);

        if (xTake == yTake) {
            // Store the taken resume's info into {outputStr}:
            outputStr += (std::to_string(arr[xTake]) + "; ");
            // * Check if taking 1 resume would cause the total number to be 0:
            if (nResume - 1 == 0) { break; }
            // * Due to z would supplement one resume in front of x, {arr[xTake]} does not need to be erased:
            arr[xTake] = ++N;
            // * Check if the current situation is an endless loop;
            if ((k + m) % nResume == 1) {
                outputStr += " => Endless loop.";
                endingN = nResume;
                break;
            }
        } else {
            // Store the taken resume's info into {outputStr}:
            outputStr += (std::to_string(arr[xTake]) + ", " + std::to_string(arr[yTake]) + "; ");
            // * Check if taking 2 resume would cause the total number to be 0:
            if ((nResume -= 2) == 0) { break; }
            // * Supplement 1 resume back:
            nResume += 1;
            arr[xTake] = ++N;
            // * Erase the taken resume:
            arr.erase(yTake);
        }

        // * Reset {xStart} and {yStart} based on new array index: @{
        // [Attention] - Here {n} has already been updated.
        if (yTake < xTake) {
            yStart = (nResume + yTake - 1) % nResume;
            xStart = (nResume + xTake - 1) % nResume;
        } else if (yTake > xTake) {
            yStart = (nResume + yTake - 1) % nResume;
            // `xStart = xTake` is also okay
            xStart = (nResume + xTake) % nResume;
        } else {
            yStart = (nResume + yTake - 1) % nResume;
            // `xStart = xTake` is also okay
            xStart = (nResume + xTake) % nResume;
        }
        // @} Reset end.
    }

    // Shrink {outputStr}:
    while (outputStr.back() == ' ' || outputStr.back() == ';') { outputStr.pop_back(); }

    // Output {outputStr} to terminal:
    if (out != nullptr) { (*out) << outputStr << std::endl; }

    return endingN;
}

int array_test2_iterator(int N, const int k, const int m, std::ostream* out)
{
    int endingN = 0;

    std::string outputStr = {}; // ouput string containing the result

    arrayList<int> arr; // array that holds the resume

    // Push back n elements (1,2,...,n) to {arr}:
    for (int i = 0; i < N; ++i) { arr.push_back(i + 1); }

    int nResume = arr.size(); // number of remaining resume

    // Define 2 lambda functions:
    auto leftRotate = [&nResume, k](int start) ->int { return (nResume + start + k % nResume - 1) % nResume; };
    auto rightRotate = [&nResume, m](int start) ->int { return (nResume + start - m % nResume + 1) % nResume; };

    // Set the initial starting point of x and y:
    int xStart = 0, xTake = 0;
    int yStart = N - 1, yTake = 0;

    while (true) {
        // Create the iterator of {arr}:
        auto it_begin = arr.begin();

        // Calculate index of the x taken and y taken:
        xTake = leftRotate(xStart);
        yTake = rightRotate(yStart);

        auto it_xTake = it_begin + xTake;
        auto it_yTake = it_begin + yTake;

        if (xTake == yTake) {
            // Store the taken resume's info into {outputStr}:
            outputStr += (std::to_string(*it_xTake) + "; ");
            // * Check if taking 1 resume would cause the total number to be 0:
            if (nResume - 1 == 0) { break; }
            // * Due to z would supplement one resume in front of x, {arr[xTake]} does not need to be erased:
            *it_xTake = ++N;
            if ((k + m) % nResume == 1) {
                outputStr += " => Endless loop.";
                endingN = nResume;
                break;
            }
        } else {
            // Store the taken resume's info into {outputStr}:
            outputStr += (std::to_string(*it_xTake) + ", " + std::to_string(*it_yTake) + "; ");
            // * Check if taking 2 resume would cause the total number to be 0:
            if ((nResume -= 2) == 0) { break; }
            // * Supplement 1 resume back:
            nResume += 1;
            *it_xTake = ++N;
            // * Erase the taken resume:
            arr.erase(yTake);
        }

        // * Reset {xStart} and {yStart} based on new array index: @{
        // [Attention] - Here {n} has already been updated.
        if (yTake < xTake) {
            yStart = (nResume + yTake - 1) % nResume;
            xStart = (nResume + xTake - 1) % nResume;
        } else if (yTake > xTake) {
            yStart = (nResume + yTake - 1) % nResume;
            // `xStart = xTake` is also okay
            xStart = (nResume + xTake) % nResume;
        } else {
            yStart = (nResume + yTake - 1) % nResume;
            // `xStart = xTake` is also okay
            xStart = (nResume + xTake) % nResume;
        }
        // @} Reset end.
    }

    // Shrink {outputStr}:
    while (outputStr.back() == ' ' || outputStr.back() == ';') { outputStr.pop_back(); }

    // Output {outputStr} to terminal:
    if (out != nullptr) { (*out) << outputStr << std::endl; }

    return endingN;
}

void outputResultofTest2(int N)
{
    std::ofstream outputFile("test2_result.txt");
    outputFile << "N\tM+K\tN' when endless loop" << std::endl;
    for (int n = 1; n <= N; ++n) {
        std::unordered_map<int, int> map;
        for (int k = 1; k <= n; ++k) {
            for (int m = 1; m <= k; ++m) {
                int endingN = array_test2(n, k, m, nullptr);
                if (map[m + k] != 0) {
                    if (map[m + k] != endingN) throw "error";
                } else {
                    map[m + k] = endingN;
                    if (endingN != 0) {
                        outputFile << n << '\t' << m + k << '\t' << endingN << std::endl;
                    }
                }
            }
        }
    }
    outputFile.close();
    std::cout << "Output Succeed." << std::endl;
}