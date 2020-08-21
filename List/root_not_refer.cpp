/* Remove trivial tree */

#include <vector>
#include <gtest/gtest.h>

using std::vector;

class Node {
public:
    Node() = default;
    Node(int idx): index(idx), next_node(0) {}
    int root() { return index; }
    Node* next() { return next_node; }
    void setNext(Node *node) { next_node = node; }
    Node *tail() {
        Node *pos, *next = next_node;
        while (next = next->next()) {
            pos = next;
        }
        return pos;
    }

  private:
    int index;
    Node *next_node;
};

inline bool is_another_tree(Node *current, Node *next) {
    return current->root() != next->root();
}

inline bool isCollide(Node *n1, Node *n2) {
    return n1 == n2;
}

inline bool isRefRecorded(vector<int> &ref, int idx) {
  for (auto i : ref) {
      if (i == idx)
          return true;
  }
  return false;
}

bool is_trivial_tree(int root_idx, vector<vector<int>> &refrel) {
    vector<int> &v = refrel[root_idx];

    if (v.size() == 0)
        return true;

    for (auto i : v) {

        // Tree i is referenced by
        // another tree so it's no a
        // trivial tree and also
        // Tree root_idx is not
        /// a trivial tree
        if (refrel[i].size() != 0) {
            return false;
        }
    }

    return true;
}

Node* travse_step(Node *pos, bool *travsed, vector<vector<int>> &refrel) {
    Node *next;
    bool isTreeChange;

    // Record travsed index
    travsed[pos->root()] = true;

    next = pos->next();
    if (!next) return next;

    // check
    if (is_another_tree(pos, next)) {
        if (!isRefRecorded(refrel[next->root()], pos->root()))
            refrel[next->root()].push_back(pos->root());
    }

    return next;
}

void travse_with_record(Node *root, bool *travsed, vector<vector<int>> &refrel, int size) {
    Node *fast = root, *slow = root;

    if (!root) return;

    fast = travse_step(fast, travsed, refrel);
    if (!fast) return;

    while (1) {
        // Fast travse two step during a turn
        fast = travse_step(fast, travsed, refrel);
        if (!fast || isCollide(fast, slow)) break;
        fast = travse_step(fast, travsed, refrel);
        if (!fast || isCollide(fast, slow)) break;

        // Slow travse only one step
        slow = slow->next();
    }
}

void remove_trivial_tree(vector<Node *> &trees) {
    int size = trees.size();
    vector<vector<int>> refrel(size);
    bool travsed[size];

    for (int i = 0; i < size; ++i) {
        travsed[i] = false;
    }

    // Travse
    for (auto root : trees) {
        if (travsed[root->root()])
            continue;

        travse_with_record(root, travsed, refrel, size);
    }

    // Trim trivial tree
    for (int i = 0; i < size; ++i) {
      if (refrel.size() == 0)
          break;
      if (is_trivial_tree(i, refrel)) {
          trees[i] = 0;
      }
    }
}

class RemoveTrivialTreeTest : public ::testing::Test {};

TEST_F(RemoveTrivialTreeTest, Case) {
    /* Setup */
    int size = 3;
    Node *pos;
    vector<Node *> trees;

    // Build Tree
    for (int i = 0; i < size; ++i) {
        pos = new Node(i);
        trees.push_back(pos);

        for (int j = 0; j < 2; ++j) {
            Node *newNode = new Node(i);
            pos->setNext(newNode);
            pos = pos->next();
        }
    }

    /* Create circles */
    Node *tail0 = trees[0]->tail(),
        *tail1 = trees[1]->tail(),
        *tail2 = trees[2]->tail();

    // Let Tree0 reference to Tree1
    tail0->setNext(tail1);

    // Let Tree1 reference to Tree0
    tail1->setNext(trees[0]->next());

    // Let Tree2 reference to Tree1
    tail2->setNext(tail1);

    /* Exercise */
    remove_trivial_tree(trees);

    /* Verify */
    ASSERT_TRUE(trees[0] != 0);
    ASSERT_TRUE(trees[1] != 0);
    ASSERT_TRUE(trees[2] == 0);
}
