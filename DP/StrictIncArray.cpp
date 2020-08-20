/* Make array strict increase */

#include <vector>
#include <gtest/gtest.h>

using std::vector;

int strictInc(vector<int> &arr1, vector<int> &arr2) {
    return 0;
}

class StrictIncTest : public ::testing::Test {};

TEST_F(StrictIncTest, Case) {
    vector<int> arr1 = {1, 5, 3, 6, 7},
        arr2 = {1, 3, 2, 4};

    strictInc(arr1, arr2);

    int prev = 0;
    for (auto num : arr1) {
      if (prev == 0) {
          prev = num;
          continue;
      }

      ASSERT_GT(num, prev);
      prev = num;
    }
}
