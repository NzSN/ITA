/* Can I Win ? */

#include <gtest/gtest.h>
#include <map>

using std::string;
using std::map;

// Assume maxChoosableinteger is a event number.
bool canIWin_memorized_aux(int max, int total, int idxs, int *states) {
    if (states[idxs] != 0)
        return states[idxs] == 1;

    for (int i = 1; i <= max; ++i) {
        int idx_tmp = 1 << (i-1);

        if ((idx_tmp & idxs) != 0)
            continue;

        if (total - i <= 0 || !canIWin_memorized_aux(max, total-i, idxs|idx_tmp, states)) {
            states[idxs] = 1;
            return true;
        }
    }

    states[idxs] = 2;
    return false;
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    if (maxChoosableInteger > desiredTotal)
        return true;
    if ((1 + maxChoosableInteger) * maxChoosableInteger / 2 < desiredTotal)
        return false;

    int size = (1 << maxChoosableInteger);
    int states[size];
    for (int i = 0; i < size; ++i)
        states[i] = 0;

    return canIWin_memorized_aux(maxChoosableInteger, desiredTotal, 0, states);
}

class CanIWinTest : public ::testing::Test {};

TEST_F(CanIWinTest, Case) {
    ASSERT_FALSE(canIWin(5, 50));
}

TEST_F(CanIWinTest, Case_1) {
    ASSERT_FALSE(canIWin(20, 210));
}

TEST_F(CanIWinTest, Case_16_100) {
    ASSERT_TRUE(canIWin(4, 6));
}
