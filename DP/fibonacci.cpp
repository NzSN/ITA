/* file: fibonacci.cpp */
#include <vector>
#include <gtest/gtest.h>

using std::vector;

unsigned fibonacci_bottom_up(unsigned nth) {
    vector<unsigned> fibos{0, 1, 1};

    int last = 0;
    for (int i = 3; i <= nth; ++i) {
        last = fibos[i-1] + fibos[i-2];
        fibos.push_back(last);
    }

    return last;
}

class Fibonacci_BOTTOM_UP_Test : public ::testing::Test {};

TEST_F(Fibonacci_BOTTOM_UP_Test, Find_Fibo_Num) {
    ASSERT_EQ(3314859971, fibonacci_bottom_up(100));
}
