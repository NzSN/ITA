/* file: CountingSort.cpp */

#include <gtest/gtest.h>
#include <iostream>

template <std::random_access_iterator r_access_iter>
void counting_sort(r_access_iter begin, r_access_iter end, auto k) {
    std::vector<int> pos_tbl(k+1, 0);
    auto current = begin;

    for (current = begin; current < end; ++current) {
        ++pos_tbl[*current];
    }

    auto pos_tbl_end = pos_tbl.end();
    for (current = pos_tbl.begin()+1; current < pos_tbl_end; ++current) {
        *current += *(current - 1);
    }

    std::vector<int> sorted(end-begin, 0);
    for (current = begin; current < end; ++current) {
        sorted[pos_tbl[*current]-1] = *current;
    }

    int size = end-begin;
    current = begin;
    for (int i = 0; i < size; ++i) {
        *current = sorted[i];
        ++current;
    }
}

class CountingSortTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup
        for (int i = 1000; i > 0; --i) {
            vec.push_back(i);
        }
    }

    std::vector<int> vec;
};

TEST_F(CountingSortTest, Sort_1000_Integers) {
    // Exercise
    counting_sort(vec.begin(), vec.end(), 1000);

    // Verify
    std::vector<int>::iterator current;
    for (current = vec.begin() + 1; current < vec.end(); ++current) {
        ASSERT_GT(*current, *(current - 1));
    }

}
