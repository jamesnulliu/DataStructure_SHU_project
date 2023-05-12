#include "Sort_06.hpp"
#include <vector>
#include <algorithm>

using namespace std;

namespace dsp {
    namespace sort {
        void Task06::solve(std::istream& in)
        {
            int stuNum{};
            in >> stuNum;
            vector<Student> stuVec{};

            for (int id = 1; id <= stuNum; ++id) {
                Student stu{ id };
                in >> stu.ChScore;
                in >> stu.MaScore;
                in >> stu.EnScore;
                stu.Sum = stu.ChScore + stu.MaScore + stu.EnScore;
                stuVec.push_back(stu);
            }

            ranges::stable_sort(stuVec, std::greater<>{}, & Student::EnScore);
            ranges::stable_sort(stuVec, std::greater<>{}, & Student::MaScore);
            ranges::stable_sort(stuVec, std::greater<>{}, & Student::ChScore);
            ranges::stable_sort(stuVec, std::greater<>{}, & Student::Sum);

            for (int i = 0; i < 5 && i < stuVec.size(); ++i) {
                auto& stu = stuVec.at(i);
                cout << stu.id << ' ' << stu.Sum << endl;
            }

            std::cin.get();
        }
    }
}