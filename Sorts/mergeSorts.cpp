/* file: MergeSort.cpp */

#include <gtest/gtest.h>


template <std::random_access_iterator r_access_iter>
void combine(r_access_iter left, const int l_size, r_access_iter right, const int r_size) {

    int idx;
    std::vector<int> part_l, part_r;
    std::vector<int>::iterator left_it = left, right_it = right;

    for (idx = 0; idx < l_size; ++idx) {
        part_l.push_back(*left_it++);
    }
    left_it = part_l.begin();

    for (idx = 0; idx < r_size; ++idx) {
        part_r.push_back(*right_it++);
    }
    right_it = part_r.begin();

    int size = l_size + r_size;
    auto &val_l = part_l.front(), &val_r = part_r.front();
    std::vector<int>::iterator current = left,
        left_end = part_l.end(),
        right_end = part_r.end();

    for (idx = 0; idx < size; ++idx) {
        if (left_it < left_end && right_it < right_end) {
            val_l = *left_it;
            val_r = *right_it;

            if (val_r < val_l) {
                *current++ = val_r;
                ++right_it;
            } else {
                *current++ = val_l;
                ++left_it;
            }
        } else if (left_it < left_end) {
            *current++ = *left_it++;
        } else if (right_it < right_end) {
            *current++ = *right_it++;
        }
    }
}

template <std::random_access_iterator r_access_iter>
void merge_sort(r_access_iter begin, r_access_iter last) {
  if (begin >= last)
      return;

  int size = last - begin + 1;
  r_access_iter mid = begin + (size / 2) - 1;
  r_access_iter r_begin = mid+1;

  merge_sort(begin, mid);
  merge_sort(r_begin, last);
  combine(begin, mid-begin+1, r_begin, last-r_begin+1);
}

class MergeSortTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup
        for (int i = 1000; i > 0; --i) {
            vec.push_back(i);
        }
    }

    std::vector<int> vec;
};

TEST_F(MergeSortTest, Sort_100000_Integers) {
    // Exercise
    merge_sort(vec.begin(), vec.end() - 1);

    // Verify
    std::vector<int>::iterator current;
    for (current = vec.begin() + 1; current < vec.end(); ++current) {
        ASSERT_GT(*current, *(current - 1));
    }
}
