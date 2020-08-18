/* file: Maximum_Subarray.cpp */
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using std::max;
using std::vector;

int maxSubArray(vector<int> &nums) {
    int max_sums = nums[0];

    int size = nums.size(), maximum = 0,
        cur_num;
    for (int i = 1; i < size; ++i) {
        cur_num = nums[i];
        maximum = maximum+cur_num > cur_num ? maximum+cur_num : cur_num;
        max_sums = maximum > max_sums ? maximum : max_sums;
    }

    return max_sums;
}

class MaximumSubArray_Test : public ::testing::Test {};

TEST_F(MaximumSubArray_Test, ValidTest) {
    vector<int> nums{-2,1,-3,4,-1,2,1,-5,4};
    ASSERT_EQ(6, maxSubArray(nums));
    vector<int> nums_only_one{-1};
    ASSERT_EQ(-1, maxSubArray(nums_only_one));
    vector<int> nums_smallest{-2147483647};
    ASSERT_EQ(-2147483647, maxSubArray(nums_smallest));
}
