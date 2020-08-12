/* file: Quicksort.cpp */

#include <concepts>
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

template <std::random_access_iterator r_access_iter>
r_access_iter partition(r_access_iter current, r_access_iter last) {
    auto &key = *last;
    r_access_iter less_than = current - 1;

    while (current < last) {
        if (*current < key) {
            ++less_than;
            std::iter_swap(current, less_than);
        }
        ++current;
    }

    r_access_iter mid = less_than + 1;
    std::iter_swap(last, mid);
    return mid;
}

template <std::random_access_iterator r_access_iter>
void quick_sort(r_access_iter begin, r_access_iter last) {
    if (!(last > begin))
        return;
    r_access_iter mid = partition(begin, last);
    quick_sort(begin, mid-1);
    quick_sort(mid+1, last);
}


// TestCases
class QuickSortTest : public ::testing::Test {
protected:
    QuickSortTest() = default;

    void SetUp() override {
        for (int i = 1000; i > 0; --i) {
            vec.push_back(i);
        }
    }

    std::vector<int> vec;
};

TEST_F(QuickSortTest, Sort_10000_Integer_Wrost) {
    // Exercise
    quick_sort(vec.begin(), vec.end() - 1);

    // Verify
   for (auto current = vec.begin() + 2; current < vec.end(); ++current) {
       ASSERT_GT(*current, *(current -1));
   }
}
