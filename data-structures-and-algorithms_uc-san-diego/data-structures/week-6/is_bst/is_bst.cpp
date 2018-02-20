#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

#define MIN -1000000000000000000

using namespace std;

struct Node {
    long long key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(long long key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree(const vector<Node>& tree, int i = 0) {
    if(tree.empty()){
        return true;
    }
    int curr_state = i;
    stack<int> _stack;
    long long curr_val, prev_val = MIN;

    while(!_stack.empty() || curr_state != -1){
        if(curr_state != -1){
            _stack.push(curr_state);
            curr_state = tree[curr_state].left;
        }
        else{
            curr_state = _stack.top(); _stack.pop();
            curr_val = tree[curr_state].key;
            if(prev_val >= curr_val) return false;
            curr_state = tree[curr_state].right;
            prev_val = curr_val;
        }
    }
    return true;
}

int main() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) {
        long long key;
        int left, right;
        cin >> key >> left >> right;
        tree.emplace_back(Node(key, left, right));
    }
    if (IsBinarySearchTree(tree)){
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}

