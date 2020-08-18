/* file: Maximum_Product_Subarray.cpp */

#include <vector>
#include <gtest/gtest.h>
#include <random>
#include <algorithm>

using std::vector;
using std::max;
using std::min;

int maxSubProduct(vector<int> &v) {
    if (v.size() == 0)
        return 0;

    int maximum = v.front(),
        maximum_tmp,
        minimum = v.front(),
        maxProduct = v.front();

    for (auto pos = v.begin()+1; pos < v.end(); ++pos) {
        maximum_tmp = max(max(*pos, *pos * maximum), *pos * minimum);
        minimum = min(min(*pos, *pos * maximum), *pos * minimum);
        maximum = maximum_tmp;

        maxProduct = max(maxProduct, maximum);
    }

    return maxProduct;
}

class MaxSubProductTest : public ::testing::Test {};
class MaxSubProductBenchTest : public ::testing::Test {
protected:
    void SetUp() {
        // Setup

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(-10, 10);

        for (int i = 0; i < 1000; ++i) {
            v_bench.push_back(i);
        }
    }

    vector<int> v_bench;
};

TEST_F(MaxSubProductTest, Case_1) {
    // Setup
    vector<int> v = {};

    // Exercise
    int ret = maxSubProduct(v);

    // Verify
    ASSERT_EQ(0, ret);
}

TEST_F(MaxSubProductTest, Case_2) {
    // Setup
    vector<int> v = {1};

    // Exercise
    int ret = maxSubProduct(v);

    // Verify
    ASSERT_EQ(ret, 1);
}

TEST_F(MaxSubProductTest, Case_3) {
    // Setup
    vector<int> v = {1, 5, 7, 1, 2, 3, -3, -6, 7, -8};

    // Exercise
    int ret = maxSubProduct(v);

    // Verify
    ASSERT_EQ(ret, 26460);
}

TEST_F(MaxSubProductBenchTest, Benchmark) {
    // Exercise
    int ret = maxSubProduct(v_bench);
}
