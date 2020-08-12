/* file: MergeSort.cpp */

#include <gtest/gtest.h>

template <std::random_access_iterator r_access_iter>
void combine(r_access_iter left, int l_size, r_access_iter right, int r_size) {
    std::array<int> array_l;
}

template <std::random_access_iterator r_access_iter>
void merge_sort(r_access_iter begin, r_access_iter last) {
  if (begin >= last)
      return;

  int size = last - begin;
  r_access_iter mid = begin + (size / 2);
  r_access_iter r_begin = mid+1;

  merge_sort(begin, mid);
  merge_sort(r_begin, last);
  combine(begin, mid-begin, r_begin, last-r_begin);
}
