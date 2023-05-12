#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "Search_02.hpp"

namespace search {
    template<class _RandIt, class _ValueTy>
        requires std::random_access_iterator<_RandIt>&& std::totally_ordered<_ValueTy>
    _RandIt binary_search(_RandIt _First, _RandIt _Last, const _ValueTy& _Val);

    std::vector<long long> search::Task02::solve(std::ifstream& in)
    {
        std::string str;
        std::istringstream istr;

        int* arr[3] = { new int[100000], new int[100000], new int[100000] };
        int size[3] = { 0, 0, 0 };

        for (long long i = 0; i < 3; ++i) {
            in >> size[i]; in.get();
            std::getline(in, str);
            istr.str(str);
            for (int j = 0; j < size[i]; ++j) {
                istr >> arr[i][j];
            }
            istr.clear();
        }

        for (long long i = 0; i < size[0]; ++i) {
            int* res1 = binary_search(arr[1], arr[1] + size[1], arr[0][i]);
            if (res1 == arr[1] + size[1]) continue;

            int* res2 = binary_search(arr[2], arr[2] + size[2], arr[0][i]);
            if (res2 == arr[2] + size[2]) continue;

            return { i, res1 - arr[1], res2 - arr[2] };
        }

        return { -1,-1,-1 };
    }

    template<class _RandIt, class _ValueTy>
        requires std::random_access_iterator<_RandIt>&& std::totally_ordered<_ValueTy>
    _RandIt binary_search(_RandIt first, _RandIt last, const _ValueTy& _Val)
    {
        _RandIt mid{};
        _RandIt end = last;
        while (first < last) {
            mid = first + (last - first) / 2;
            if (*mid < _Val) first = mid + 1;
            else if (*mid > _Val) last = mid;
            else {
                while (mid != first && *mid == _Val) --mid;
                if (*first == _Val) return first;
                else return (mid + 1);
            }
        }
        return end;
    }
}