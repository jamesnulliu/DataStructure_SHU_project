#include "../Tools/ColorIO.hpp"
#include "../Tools/Random.hpp"
#include "../Tools/TimeCounter.hpp"
#include "../UserInterface/OptionSwitcher.hpp"
#include "Sort_01.hpp"

namespace dsp {
    namespace sort {
        void Task01::solve()
        {
            sgc::setConColor();
            OptionSwitcher<char> ops({
                    { 'q', "Go back to solution list." },
                    { '1', "Input a seq and test." },
                    { '2', "Generate a random seq and test." }
                });

            char option{ ops() };
            std::vector<int> data{}, data_copy{};

            if (option == '0') {
                return;
            } else if (option == '1') {
                int elem{};
                sgc::cout() << "Enter a seq of integers, ended with q:\n";
                sgc::cout() << ">>> ";
                sgc::setConColor(4);
                while (std::cin >> elem) {
                    data.push_back(elem);
                };
                sgc::flushInputBuffer();
            } else {
                Rand_Normal<int> rand;
                int num{};
                double mean{}, sigma{};
                sgc::cout() << "Enter number of elements to generate, mean, and sigma:\n";
                sgc::cout() << ">>> ";
                sgc::cin(4) >> num >> mean >> sigma;
                sgc::flushInputBuffer();
                newLine();
                sgc::setConColor();
                data = rand.generateVec(num, mean, sigma);
            }
            data_copy = data;
            newLine();
            sgc::setConColor(0);
            DistVisualizer<int>{}(data);
            newLine();
            sgc::cout() << "Sorting...\n";
            newLine();

            TimeCounter counter;

            counter.startCounting();
            countingSort(data);
            counter.endCounting();
            sgc::cout() << "* Counting sort finished, cost " << counter.msecond() << "ms.\n";
            counter.init();
            counter.startCounting();
            std::ranges::sort(data_copy);
            counter.endCounting();
            sgc::cout() << "* std::sort finished, cost " << counter.msecond() << "ms.\n";

            newLine();

            if (data_copy == data) {
                sgc::cout(2) << "Sorting result is correct.\n";
            } else {
                sgc::cout(3) << "Sorting result is incorrect.\n";
            }
            sgc::cout() << "Press Enter to go back to option list: ";
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