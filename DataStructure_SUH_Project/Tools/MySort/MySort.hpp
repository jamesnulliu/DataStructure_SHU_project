#pragma once
#include <algorithm>
#include <functional>
#include <climits>
#include <random>
#include <vector>
#include <iostream>

class MySort
{
    using int32 = int;
    using int64 = long long;
    using index = int64;
public:
    static MySort& getInstance() {
        static MySort _sort;
        return _sort;
    }
private:
    MySort() {};
    MySort(const MySort&) = delete;
    MySort& operator=(const MySort&) = delete;

// SELECTION SORT @{
public:
    /**
    * @param first -The index of the first element.
    * @param last -The index of the last element.
    */
    template<class _RandIt, class _Pr = std::less<void>>
    void selectionSort(_RandIt seq, index first, index last, const _Pr& comp = {}) {
        for (index i = first; i < last; ++i) {
            // The index of the smallest (or largest) elem in {seq[i : last-1]} (should be).
            index selected = i;
            // Following for-loop actually make {selected} the smallest (or largest):
            for (index j = i + 1; j <= last; ++j) {
                if (!comp(*(seq + selected), *(seq + j))) { selected = j; }
            }
            // Swap the selected and {seq[i]}:
            if (selected != i) { std::iter_swap(seq + selected, seq + i); }
        }
    }
// @} SELECTION SORT END

// INSERTION SORT @{
public:
    /**
    * @param first -The index of the first element.
    * @param last -The index of the last element.
    */
    template<class _RandIt, class _Pr = std::less<void>>
    void insertionSort(_RandIt seq, index first, index last, const _Pr& comp = {})
    {
        for (index j = first + 1; j <= last; ++j) {
            // {key} is the elem to insert.
            auto key = *(seq + j);
            index i = j - 1;
            // {seq[first : j-1]} must be already sorted;
            // The while-loop move the consecutive subseq whose elems are larger than {key}
            // 1 pos forward to overlap {key}'s position:
            while (i >= first && !comp(*(seq + i), key)) {
                *(seq + 1 + i) = *(seq + i);
                --i;
            }
            // Insert {key} to the appropriate position:
            *(seq + 1 + i) = key;
        }
    }
//  @} INSERTION SORT END

// MERGE SORT @{
public:
    /**
    * @param first - The index of the first element.
    * @param last - The index of the last elemen.
    * @param MAX - The maximum value among the type of the element.
    * @param MIN - The minimum value among the type of the element.
    */
    template<class _RandIt, class _Pr = std::less<void>>
    void mergeSort(_RandIt seq, index first, index last, auto MAX, auto MIN, const _Pr& comp = {})
    {
        if (first >= last) return;
        index mid = (first + last) / 2;
        mergeSort(seq, first, mid, MAX, MIN, comp);
        mergeSort(seq, mid + 1, last, MAX, MIN, comp);
        merge(seq, first, mid, last, MAX, MIN, comp);
    }
private:
    /**
    * @brief Merge two ordered subsequences seq[subAFirst, subALast] and seq(subALast, subBLast] to seq[subAFirst, subBLast].
    * @param subAFirst -The index of the first element in subseq A.
    * @param subALast -The index of the last element in subseq A.
    * @param subBLast -The index of the last element in subseq B.
    * @param MAX -The maximum value of the element type.
    * @param MIN -The minimum value of the element type.
    */
    template<class _RandIt, class _Pr>
    void merge(_RandIt seq, index subAFirst, index subALast, index subBLast, auto MAX, auto MIN, const _Pr& comp)
    {
        // {END} is set at the end of each subarray.
        auto END = comp(MIN, MAX) ? MAX : MIN;

        size_t sizeSubA = subALast - subAFirst + 2;
        size_t sizeSubB = subBLast - subALast + 1;

        auto subA = new typename std::remove_reference<decltype(*seq)>::type[sizeSubA];
        std::copy(seq + subAFirst, seq + subALast + 1, subA);
        subA[sizeSubA - 1] = END;

        auto subB = new typename std::remove_reference<decltype(*seq)>::type[sizeSubB];
        std::copy(seq + subALast + 1, seq + subBLast + 1, subB);
        subB[sizeSubB - 1] = END;

        // Merge two subsequences to origin {seq[subAFirst : subBLast]}:
        for (index k = subAFirst, i = 0, j = 0; k <= subBLast; ++k) {
            if (i >= sizeSubA || j >= sizeSubB) return;
            // Merge:
            if (comp(subA[i], subB[j])) {
                *(seq + k) = subA[i]; ++i;
            } else {
                *(seq + k) = subB[j]; ++j;
            }
        }

        delete[] subA;
        delete[] subB;
    }
// @} MERGE SORT END

// QUICK SORT @{
public:
    template<class _RandIt, class _Pr = std::less<void>>
    void quickSort_Lomuto(_RandIt seq, index first, index last, const _Pr& comp = {})
    {
        if (first >= last) return;
        // Basic quick sort always choose the last (or the first) element as pivot.
        // If the seq is already sorted (or reverse-sorted), the complexity rises to O(n^2).
        index p = partition_Lomuto(seq, first, last, comp);
        quickSort_Lomuto(seq, first, p - 1, comp);
        quickSort_Lomuto(seq, p + 1, last, comp);
    }
    template<class _RandIt, class _Pr = std::less<void>>
    void quickSort_TailRecursive_Lomuto(_RandIt seq, index first, index last, const _Pr& comp = {})
    {
        while (first < last) {
            index p = partition_Lomuto(seq, first, last, comp);
            quickSort_Lomuto(seq, first, p - 1, comp);
            first = p + 1;
        }
    }
    template<class _RandIt, class _Pr = std::less<void>>
    void quickSort_Lomuto_rand(_RandIt seq, index first, index last, const _Pr& comp = {})
    {
        if (first >= last) return;
        // If the pivot is choosen randomly, the algorithm does not rely on the input seq,
        // which avoid the sorted case.
        // The complexity (i.e., the expectation of T(n)) is O(nlgn).
        // But if all the elements are the same, the complexitiy is still O(n^2).
        index p = partition_rand_Lomuto(seq, first, last, comp);
        quickSort_Lomuto_rand(seq, first, p - 1, comp);
        quickSort_Lomuto_rand(seq, p + 1, last, comp);
    }
    template<class _RandIt, class _Pr1 = std::less<void>, class _Pr2 = std::equal_to<void>>
    void quickSort_Lomuto_rand_repit(_RandIt seq, index first, index last, const _Pr1& comp = {}, const _Pr2& equal = {})
    {
        if (first >= last) return;
        // See comments of function {Paritition_rand_repit_Lomuto()}.
        index* p = partition_rand_repit_Lomuto(seq, first, last, comp, equal);
        quickSort_Lomuto_rand_repit(seq, first, p[0] - 1, comp, equal);
        quickSort_Lomuto_rand_repit(seq, p[1] + 1, last, comp, equal);
        delete p;
    }
    template<class _RandIt, class _Pr1 = std::less<void>, class _Pr2 = std::equal_to<void>>
    void quickSort_Lomuto_rand_repit_insert
    (_RandIt seq, index first, index last, const _Pr1& comp = {}, const _Pr2& equal = {}, int64 cut = 10LL)
    {
        if (first >= last) return;
        // Use insertionSort if the length is small.
        if (last - first + 1LL == cut) {
            insertionSort(seq, first, last, comp);
            return;
        }
        index* p = partition_rand_repit_Lomuto(seq, first, last, comp, equal);
        quickSort_Lomuto_rand_repit_insert(seq, first, p[0] - 1, comp, equal, cut);
        quickSort_Lomuto_rand_repit_insert(seq, p[1] + 1, last, comp, equal, cut);
    }
    // @brief Hoare's primitive quick sort is basically the fastest if the input scale is large, with the least use of swap.
    template<class _RandIt, class _Pr1 = std::less<void>, class _Pr2 = std::greater<void>>
    void quickSort_Hoare(_RandIt seq, index first, index last, const _Pr1& comp1 = {}, const _Pr2 comp2 = {}) {
        if (first >= last) return;
        index p = partition_Hoare(seq, first, last, comp1, comp2);
        quickSort_Hoare(seq, first, p, comp1, comp2);
        quickSort_Hoare(seq, p + 1, last, comp1, comp2);
    }
    template<class _RandIt, class _Pr1 = std::less<void>, class _Pr2 = std::greater<void>>
    void quickSort_Hoare_rand(_RandIt seq, index first, index last, const _Pr1& comp1 = {}, const _Pr2 comp2 = {}) {
        if (first >= last) return;
        index p = partition_rand_Hoare(seq, first, last, comp1, comp2);
        quickSort_Hoare_rand(seq, first, p, comp1, comp2);
        quickSort_Hoare_rand(seq, p + 1, last, comp1, comp2);
    }
    template<class _RandIt, class _Pr1 = std::less<void>, class _Pr2 = std::greater<void>>
    void quickSort_Hoare_rand_insertion
    (_RandIt seq, index first, index last, const _Pr1& comp1 = {}, const _Pr2 comp2 = {}, int64 cut = 10LL) {
        if (first >= last) return;
        if (last - first + 1LL == cut) {
            insertionSort(seq, first, last, comp1);
            return;
        }
        index p = partition_rand_Hoare(seq, first, last, comp1, comp2);
        quickSort_Hoare_rand_insertion(seq, first, p, comp1, comp2);
        quickSort_Hoare_rand_insertion(seq, p + 1, last, comp1, comp2);
    }
private:
    /**
    * @brief Partition the array {seq[first : last]} into 2 (possibly empty) subarrays
            {seq[fisrtIndex : q - 1]} and {seq[q + 1 : last]}, such that each element of
            {seq[first : q - 1]} <=(or >=) {seq[q]} and, in turn, {seq[q]} <=(or >=) each
            element of {seq[q+1 : last]}.
            [*] Following partition always chooses the last element to be {[q]}.
    * @comp  O(n)
    * @param first -The index of the first element in {seq}.
    * @param last -The index of the last element in {seq}.
    * @return
    */
    template<class _RandIt, class _Pr>
    index partition_Lomuto(_RandIt seq, index first, index last, const _Pr& comp)
    {
        auto x = *(seq + last); // The pivot.
        /*
        *                     {i}                       {j}
        *                      ��                         ��
        * [ ...comp(elem, x)...o ] [ ...!comp(elem, x)...o ] [ ...unknown... ] {x}
        */
        index i = first - 1;
        index j = first;
        for (; j <= last - 1; ++j) {
            if (comp(*(seq + j), x)) {
                ++i;
                std::iter_swap(seq + i, seq + j);
            }
        }
        ++i;
        std::iter_swap(seq + i, seq + last);
        return i;
    }
    /**
    * @brief Partition the array {seq[first : last]} into 2 (possibly empty) subarrays
            {seq[fisrtIndex : q - 1]} and {seq[q + 1 : last]}, such that each element of
            {seq[first : q - 1]} <=(or >=) {seq[q]} and, in turn, {seq[q]} <=(or >=) each
            element of {seq[q+1 : last]}.
            [*] Index {q} is chosen randomly, with the method: Median-of-3 Partition.
    * @comp  O(n)
    * @param first -The index of the first element in {seq}.
    * @param last -The index of the last element in {seq}.
    * @return
    */
    template<class _RandIt, class _Pr>
    index partition_rand_Lomuto(_RandIt seq, index first, index last, const _Pr& comp)
    {
        // Get 3 index randomly in range of [first, last]:
        index a = random_uniform(first, last);
        index b = random_uniform(first, last);
        index c = random_uniform(first, last);
        // Choose the median of the 3 randomly chosen elems:
        index mid = // index of the median
            (comp(*(seq + a), *(seq + b)) && comp(*(seq + b), *(seq + c))) ? b    // comp(A,B) and comp(B,C) => B is median
            : (comp(*(seq + b), *(seq + a)) && comp(*(seq + a), *(seq + c))) ? a  // comp(B,A) and comp(A,C) => A is median
            : c;                                                                  // otherwise               => C is median
        std::iter_swap(seq + last, seq + mid);
        return partition_Lomuto(seq, first, last, comp);
    }
    /**
    * @brief Partition the array {seq[first : last]} into 3 subarrays:
            elems in {seq[m : n]} all equal to the pivot;
            elems in {seq[first : m-1]} all less(or larger) than the pivot;
            elems in {seq[n+1 : last]} all larger(or less) than the pivot.
            [*] Index of pivot is chosen randomly, with the method: Median-of-3 Partition.
            [*] Repitition optimized.
    * @comp  O(n)
    * @param first -The index of the first element in {seq}.
    * @param last -The index of the last element in {seq}.
    * @return An array with the first and last index of subarray that equals to the pivot.
            [*] Remember to free the memory.
    */
    template<class _RandIt, class _Pr1, class _Pr2>
    index* partition_rand_repit_Lomuto(_RandIt seq, index first, index last, const _Pr1& comp, const _Pr2& equal)
    {
        // Get 3 index randomly in range of [first, last]:
        index a = random_uniform(first, last);
        index b = random_uniform(first, last);
        index c = random_uniform(first, last);
        // Choose the median of the 3 randomly chosen elems:
        index mid = // index of the median
            (comp(*(seq + a), *(seq + b)) && comp(*(seq + b), *(seq + c))) ? b    // comp(A,B) and comp(B,C) => B is median
            : (comp(*(seq + b), *(seq + a)) && comp(*(seq + a), *(seq + c))) ? a  // comp(B,A) and comp(A,C) => A is median
            : c;                                                                  // otherwise               => C is median
        std::iter_swap(seq + last, seq + mid);

        auto x = *(seq + last); // The pivot.

        /*
        * {eqLeft} is left of (before) elems that equal to {x};
        * {i} is at the end of elems equal to {x}, left of (before) NOT{(bool)comp(elem,x)};
        * {j} is at the end of elems NOT{(bool)comp(elem,x)}, left of (before) unknown.
        *                   {eqLeft}                    {i}                       {j}
        *                      ��                         ��                         ��
        * [ ...comp(elem, x)...o ] [ ...equal(elem, x)...o ] [ ...!comp(elem, x)...o ] [ ...unknown... ] {x}
        */
        index eqLeft = first - 1;
        index i = first - 1;
        index j = first;

        for (; j <= last - 1; ++j) {
            if (comp(*(seq + j), x)) {
                ++i;
                std::iter_swap(seq + i, seq + j);
                ++eqLeft;
                if (eqLeft != i) {
                    std::iter_swap(seq + eqLeft, seq + i);
                }
            } else if (equal(*(seq + j), x)) {
                ++i;
                std::iter_swap(seq + i, seq + j);
            }
        }
        ++i;
        std::iter_swap(seq + i, seq + last);
        ++eqLeft;
        return (new index[2]{ eqLeft, i });
    }
    /**
    * @brief Partition the array to 2 subarrays, any element in {seq[first : j]} is smaller (or larger)
            than any in {seq[j+1 : last]}.
            Hoare��s scheme is more efficient than Lomuto��s partition scheme because it does three times fewer
            swaps on average, and it creates efficient partitions even when all values are equal.
            [*] The pivot��s final location is not necessarily at the index that was returned.
            [*] If input array is already sorted, complexity will also degrade to O(n^2).
    * @comp  O(n)
    * @param first -The index of the first element in {seq}.
    * @param last -The index of the last element in {seq}.
    * @return
    */
    template<class _RandIt, class _Pr1, class _Pr2>
    index partition_Hoare(_RandIt seq, index first, index last, const _Pr1& comp1, const _Pr2& comp2)
    {
        auto x = *(seq + first);
        index i = first - 1;
        index j = last + 1;
        while (true) {
            do { --j; } while (comp2(*(seq + j), x));
            do { ++i; } while (comp1(*(seq + i), x));
            if (i < j) {
                std::iter_swap(seq + i, seq + j);
            } else {
                // Any element in {seq[first : j]} is smaller than any in {seq[j+1 : last]}.
                return j;
            }
        }
    }
    /**
    * @brief Partition the array to 2 subarrays, any element in {seq[first : j]} is smaller (or larger)
            than any in {seq[j+1 : last]}.
            Hoare��s scheme is more efficient than Lomuto��s partition scheme because it does three times fewer
            swaps on average, and it creates efficient partitions even when all values are equal.
            [*] The pivot��s final location is not necessarily at the index that was returned.
            [*] Pivot is chosen randomly, with the method: Median-of-3 Partition.
    * @comp  O(n)
    * @param first -The index of the first element in {seq}.
    * @param last -The index of the last element in {seq}.
    * @return
    */
    template<class _RandIt, class _Pr1, class _Pr2>
    index partition_rand_Hoare(_RandIt seq, index first, index last, const _Pr1& comp1, const _Pr2& comp2)
    {
        // Get 3 index randomly in range of [first, last]:
        index a = random_uniform(first, last);
        index b = random_uniform(first, last);
        index c = random_uniform(first, last);
        // Choose the median of the 3 randomly chosen elems:
        index mid = // index of the median
            (comp1(*(seq + a), *(seq + b)) && comp1(*(seq + b), *(seq + c))) ? b    // comp(A,B) and comp(B,C) => B is median
            : (comp1(*(seq + b), *(seq + a)) && comp1(*(seq + a), *(seq + c))) ? a  // comp(B,A) and comp(A,C) => A is median
            : c;                                                                    // otherwise               => C is median
        std::iter_swap(seq + first, seq + mid);

        auto x = *(seq + first);
        index i = first - 1;
        index j = last + 1;
        while (true) {
            do { --j; } while (comp2(*(seq + j), x));
            do { ++i; } while (comp1(*(seq + i), x));
            if (i < j) {
                std::iter_swap(seq + i, seq + j);
            } else {
                // Any element in {seq[first : j]} is smaller than any in {seq[j+1 : last]}.
                return j;
            }
        }
    }
// @} QUICK SORT END

// COUNTING SORT @{
public:
    // @brief All the elements in {seq} should be in range of [0, {max}].
    void countingSort(std::vector<int64>& seq, std::vector<int64>& res, const int64 max) {
        // {seq} should at least has 2 elems, and {max} should be at least <1>.
        if (seq.size() == 0 || seq.size() == 1 || max == 0) return;
        res.resize(seq.size());
        std::vector<int64> count(max + 1, 0);
        // {count[i]} infers the number of elems in {seq} that equal to {i}:
        for (const auto elem : seq) { ++count[elem]; }
        // {count[i]} now infers the number of elems in {seq} that less than or equal to {i}:
        for (auto it = count.begin() + 1; it != count.end(); ++it) { *it += *(it - 1); }
        for (index i = (index)seq.size() - 1; i >= 0; --i) {
            res[count[seq[i]] - 1] = seq[i];
            --count[seq[i]];
        }
    }
// @} COUNTING SORT END

// RADIX SORT @{
// @} RADIX SORT END

// RAND NUMBER GENERATOE @{
public:
    template<class _Ty = void> _Ty random_uniform(_Ty, _Ty) = delete;
    template<> int64 random_uniform<int64>(int64 min, int64 max)
    {
        // A random number engine based on Mersenne Twister algorithm:
        static std::default_random_engine engine(_rd());
        std::uniform_int_distribution<int64> distribution(min, max);
        return distribution(engine);
    }
    template<> int32 random_uniform<int32>(int32 min, int32 max) {
        // A random number engine based on Mersenne Twister algorithm:
        static std::default_random_engine engine(_rd());
        std::uniform_int_distribution<int32> distribution(min, max);
        return distribution(engine);
    }
    template<> double random_uniform<double>(double min, double max) {
        // A random number engine based on Mersenne Twister algorithm:
        static std::default_random_engine engine(_rd());
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(engine);
    }
    template<class _Ty = void> _Ty random_normal(double, double) = delete;
    template<> double random_normal<double>(double mean, double sigma) {
        // A random number engine based on Mersenne Twister algorithm:
        static std::default_random_engine engine(_rd());
        std::normal_distribution<double> distribution(mean, sigma);
        return distribution(engine);
    }
    template<> int64 random_normal<int64>(double mean, double sigma) {
        return (int64)std::lround(random_normal<double>(mean, sigma));
    }
private:
    // Obtain a seed for the random number engine:
    std::random_device _rd;
// @} RAND NUMBER GENERATOR END

// OTHER TOOLS @{
public:
    template<class _SeqTy>
    void printSeq(_SeqTy& seq)
    {
        for (auto& elem : seq) { std::cout << elem << ' '; }
        putchar('\n');
    }
    template<class _RandIt>
    void printSeq(_RandIt begin, _RandIt end)
    {
        for (auto iter = begin; iter != end; ++iter) { std::cout << *iter << ' '; }
        putchar('\n');
    }

// @} OTHER TOOLS END
};