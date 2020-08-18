/* file: cut_rod_problem.cpp */
#include <algorithm>
#include <gtest/gtest.h>

using std::max;

int cut_rod(int prices[], int length) {
    if (length == 0) {
        return 0;
    }

    int revenue = 0;
    for (int i = 1; i <= length; ++i) {
        revenue = max(revenue, prices[i] + cut_rod(prices, length-i));
    }

    return revenue;
}

class DP_PROBLEMS_TEST : public ::testing::Test {};

TEST_F(DP_PROBLEMS_TEST, CURT_ROD) {
    int prices[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    ASSERT_EQ(13, cut_rod(prices, 5));
}
