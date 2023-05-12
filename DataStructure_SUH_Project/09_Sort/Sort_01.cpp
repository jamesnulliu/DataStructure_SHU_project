#include "../Tools/ColorIO.hpp"
#include "../Tools/Random.hpp"
#include "../Tools/TimeCounter.hpp"
#include "Sort_01.hpp"

namespace dsp {
    namespace sort {
        void Task01::solve()
        {
            char option{};
            sgc::cout() << "1. Input a seq and test.\n"
                << "2. Generate a random seq and test.\n"
                << "0. Go back to solution list\n";
            newLine();
            sgc::cout(6) << "Enter option: ";
            while (true) {
                sgc::cin(2) >> option;
                sgc::flushInputBuffer();
                if (option == '0') return;
                if (option == '1' || option == '2') break;
                sgc::cout(6) << "Wrong input, try again!\nEnter option: ";
            }
            newLine();
            std::vector<int> data{};
            if (option == '1') {
                int elem{};
                sgc::cout(6) << "Enter a seq of integers, ended with Ctrl^Z:\n";
                sgc::setConColor();
                while (std::cin.good()) {
                    std::cin >> elem;
                };
                sgc::flushInputBuffer();
            } else {
                Rand_Normal<int> rand;
                int num{};
                double mean{}, sigma{};
                sgc::cout(6) << "Enter number of elements to generate, mean, and sigma:\n";
                sgc::setConColor();
                std::cin >> num >> mean >> sigma;
                sgc::flushInputBuffer();
                for (int i = 0; i < num; ++i) {
                    data.push_back(rand(mean, sigma));
                }
                sgc::cout(6) << "Data generation finished.\n";
            }

            std::vector<int> dataCopy = data;

            TimeCounter counter;
            counter.startCounting();
            countingSort(data);
            counter.endCounting();
            sgc::cout() << "Counting sort finished, cost " << counter.msecond() << "ms.\n";

            counter.init();
            counter.startCounting();
            std::ranges::sort(dataCopy);
            counter.endCounting();
            sgc::cout() << "std::sort finished, cost " << counter.msecond() << "ms.\n";

            newLine();

            if (dataCopy == data) {
                sgc::cout(2) << "Sorting result is correct.\n";
            } else {
                sgc::cout(3) << "Sorting result is incorrect.\n";
            }
            std::cin.get();
        }

        void Task01::countingSort(std::vector<int>& vec)
        {
            std::vector<int> rank(vec.size(), 0);
            std::vector<int> result(vec.size(), 0);
            for (size_t i = 0; i < vec.size(); ++i) {
                for (size_t j = 0; j < i; ++j) {
                    if (vec[j] <= vec[i]) ++rank[i];
                    else ++rank[j];
                }
            }
            for (size_t i = 0; i < vec.size(); ++i) {
                result[rank[i]] = vec[i];
            }
            std::swap(vec, result);
        }
    }
}