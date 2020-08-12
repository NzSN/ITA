#include <concepts>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <gtest/gtest.h>

using std::random_access_iterator;

template <typename ContRange>
concept ContR = requires(ContRange a) {
    { a.begin() } -> std::same_as<typename ContRange::iterator>;
    { a.end() } -> std::same_as<typename ContRange::iterator>;
};

template <std::random_access_iterator Rand_Iter>
int index(Rand_Iter cur, Rand_Iter begin) {
    return cur - begin;
}

inline int parent_shift(int idx) {
    return (idx >> 1) - idx;
}

inline int leftChild_shift(int idx) {
    return (idx << 1) - idx;
}

inline int rightChild_shift(int idx) {
    return (idx << 1) + 1 - idx;
}

inline bool validRange(int idx, int size) {
    return idx >=0 && idx < size;
}

template <
    std::random_access_iterator Rand_Iter,
    ContR SeqCont>
void heapify_max(SeqCont &cont, Rand_Iter current, int sorted_num) {

    typename SeqCont::iterator begin = cont.begin();

    int idx = index(current, begin),
        l_shift = leftChild_shift(idx),
        r_shift = rightChild_shift(idx),
        size = cont.size() - sorted_num;

    Rand_Iter largest = current;

    if (validRange(idx+l_shift, size)) {
        Rand_Iter left = current + l_shift;
        if (*left > * current )
            largest = left;
    }

    if (validRange(idx+r_shift, size)) {
        Rand_Iter right = current + r_shift;
        if (*right > * largest)
            largest = right;
    }

    if (largest != current) {
        std::iter_swap(largest, current);
        heapify_max(cont, largest, sorted_num);
    }
}

template <std::random_access_iterator Rand_Iter, ContR SeqCont>
void build_max_heap(SeqCont &cont) {
    typedef typename SeqCont::iterator SeqIter;

    Rand_Iter begin = cont.begin() + 1;
    // Point to last interior node.
    int size = cont.size();
    Rand_Iter current = cont.end() - 1;
    current = current + parent_shift(size-1);

    while (current >= begin) {
        heapify_max(cont, current, 0);
        current--;
    }
}

template <std::random_access_iterator Rand_Iter, ContR SeqCont>
void HeapSort(SeqCont &cont) {
    int sorted_num = 0;
    Rand_Iter stop = cont.begin(), largest = stop + 1;

    build_max_heap<std::vector<int>::iterator>(cont);

    for (auto current = cont.end()-1; current > stop; --current) {
        std::iter_swap(current, largest);
        heapify_max(cont, largest, ++sorted_num);
    }
}

/* TestCases */
class HeapSortTest : public ::testing::Test {
protected:
    HeapSortTest() = default;

    void SetUp() override {
        for (int i = 0; i < 10000; ++i) {
            vec.push_back(i);
        }
    }

    std::vector<int> vec;
};

TEST_F(HeapSortTest, Sort_10000_Integer) {
    // Exercise
    std::vector<int>::iterator iter = vec.begin();
    HeapSort<std::vector<int>::iterator>(vec);

    // Verify
    for (auto current = vec.begin() + 2; current < vec.end(); ++current) {
        ASSERT_GT(*current, *(current - 1));
    }

}
