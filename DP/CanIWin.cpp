/* Can I Win ? */

#include <gtest/gtest.h>
#include <vector>

using std::vector;

typedef enum {
    win,
    lose,
    draw
} duelState;

class DuelInfo {
public:
    DuelInfo() = default;
    DuelInfo(int remain) : remain(remain) {}
    bool inUsed(int pos) {
        for (auto i : used) {
            if (pos == i) {
                return true;
            }
        }
        return false;
    }

    vector<int> used;
    int remain;
    duelState s;
};

duelState duel(int n1, int n2, int R) {
  return n1 >= R ? win : (n1 + n2 >= R ? lose : draw);
}

// Assume maxChoosableinteger is a event number.
bool canIWin(int maxChoosableInteger, int desiredTotal) {
    int total_pool = 0;
    int size = maxChoosableInteger + 1;

    vector<int> pool;
    for (int i = 0; i < size; ++i)
        pool.push_back(i);

    for (auto num : pool) {
        total_pool += num;
    }

    DuelInfo init_info(desiredTotal - total_pool);
    vector<vector<DuelInfo>> infos(size);
    infos[0].push_back(init_info);

    for (int remain = 2; remain < size; remain+=2) {
        DuelInfo new_info;
        vector<DuelInfo> info = infos[remain-2];

        for (auto I : info)
        for (int i = 1; i < size; ++i) {
            if (I.inUsed(i)) continue;
            for (int j = 1; j < size; ++j) {
                if (j == i) continue;
                if (I.inUsed(j)) continue;

                new_info = DuelInfo();

                new_info.s = duel(pool[i], pool[j], I.remain + pool[i] + pool[j]);
                new_info.used = I.used;
                new_info.used.push_back(i);
                new_info.used.push_back(j);
                new_info.remain = pool[i] + pool[j] + I.remain;
                infos[remain].push_back(new_info);
            }
        }
    }

    vector<DuelInfo> info = infos[maxChoosableInteger];
    for (auto i : info) {
        if (i.s == win) {
            return true;
        }
    }
    return false;
}

class CanIWinTest : public ::testing::Test {};

TEST_F(CanIWinTest, Case_1) {
    ASSERT_TRUE(canIWin(2, 0));
    ASSERT_FALSE(canIWin(4, 10));
    ASSERT_TRUE(canIWin(4, 6));
}
