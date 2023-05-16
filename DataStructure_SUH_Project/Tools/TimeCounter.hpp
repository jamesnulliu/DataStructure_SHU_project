#pragma once
#include <ctime>
#include <string>
#include <numeric>
#include <vector>

class TimeCounter
{
    const clock_t msPerSec = CLOCKS_PER_SEC;
public:
    TimeCounter() = default;
    ~TimeCounter() = default;

    clock_t getStartingTime() const { return time1; }
    clock_t getEndingTime() const { return time2; }

    // @brief Clear the content in {resultList}.
    void init()
    {
        resultList.clear();
    }

    // @brief Start counting.
    void startCounting()
    {
        time1 = clock();
        whetherStart = true;
    }
    // @brief Stop counting and store duration into {resultList}.
    void endCounting()
    {
        if (whetherStart == false) {
            throw "End Counting before starting.";
        }
        time2 = clock();
        resultList.push_back(time2 - time1);
        whetherStart = false;
    }

    // @brief Return average duration in millisecond.
    long msecond()
    {
        return calAverage();
    }
    // @brief Return average duration in second.
    double second()
    {
        return static_cast<double>(calAverage()) / msPerSec;
    }

private:
    // @brief Return average duration in {resultList}.
    clock_t calAverage() { return clock_t(std::accumulate(resultList.begin(), resultList.end(), 0L) / resultList.size()); }
    bool whetherStart = false;
    clock_t time1 = 0L;
    clock_t time2 = 0L;
    std::vector<clock_t> resultList = {};
};