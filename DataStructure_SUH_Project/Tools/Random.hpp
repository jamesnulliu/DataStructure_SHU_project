#pragma once
#include <random>
#include <iostream>
#include <vector>
#include <numeric>

template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
class Rand_Uniform
{
public:
    inline _ValTy operator()(_ValTy min, _ValTy max) const
    {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(_engine);
    }

    std::vector<_ValTy> generateVec(size_t size, _ValTy min, _ValTy max) const
    {
        std::vector<_ValTy> vec;
        while (size--) { vec.push_back(this->operator()(min, max)); }
        puts("[Rand_Uniform] Data Generation Finished.");
        return vec;
    }

private:
    static std::random_device _rd;
    static std::default_random_engine _engine;
};

template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
std::random_device Rand_Uniform<_ValTy>::_rd{};
template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
std::default_random_engine Rand_Uniform<_ValTy>::_engine{ _rd() };

template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
class Rand_Normal
{
public:
    inline _ValTy operator()(double mean, double sigma) const
    {
        std::normal_distribution<double> distribution(mean, sigma);
        return static_cast<_ValTy>(distribution(_engine));
    }

    std::vector<_ValTy> generateVec(size_t size, _ValTy mean, _ValTy sigma) const
    {
        std::vector<_ValTy> vec;
        while (size--) { vec.push_back(this->operator()(mean, sigma)); }
        puts("[Rand_Normal] Data Generation Finished.");
        return vec;
    }

private:
    static std::random_device _rd;
    static std::default_random_engine _engine;
};

template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
std::random_device Rand_Normal<_ValTy>::_rd{};
template<class _ValTy>
    requires std::is_same<_ValTy, int>::value || std::is_same<_ValTy, long long>::value || std::is_same<_ValTy, double>::value
std::default_random_engine Rand_Normal<_ValTy>::_engine{ _rd() };

template<class _ValTy>
class DistVisualizer
{
public:
    void operator()(const std::vector<_ValTy>& randVec,
        const size_t binNum = 10,
        const size_t maxStarNum = 15) const
    {
        if (randVec.empty()) return;
        _ValTy minElem = *std::ranges::min_element(randVec);
        _ValTy maxElem = *std::ranges::max_element(randVec);
        _ValTy range = maxElem - minElem;
        double average = std::accumulate(randVec.begin(), randVec.end(), 0.0) / randVec.size();
        std::vector<size_t> bins(binNum);

        std::cout << "min: " << minElem << " max: " << maxElem << " average: " << average << std::endl;

        for (const auto& val : randVec) {
            size_t bin = static_cast<size_t>(double(val - minElem) / range * binNum);
            if (bin == bins.size()) { bin -= 1; }
            ++bins[bin];
        }

        size_t maxS = *std::ranges::max_element(bins);

        double resizer = double(maxS) / maxStarNum;

        for (auto& val : bins) {
            val = ceil(val / resizer);
        }

        for (size_t i = 0; i < bins.size(); ++i) {
            std::cout << i << ": ";
            for (size_t j = 0; j < bins[i]; ++j) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }

        return;
    }
};
