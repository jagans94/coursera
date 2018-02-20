#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
    int key;
    // Sum of all the keys in the subtree - remember to update
    // it after each operation that changes the tree.
    long long sum;
    Vertex* left;
    Vertex* right;
    Vertex* parent;

    Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent)
            : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
    if (v == nullptr) return;
    v->sum = v->key + (v->left != nullptr ? v->left->sum : 0ll) + (v->right != nullptr ? v->right->sum : 0ll);
    if (v->left != nullptr) {
        v->left->parent = v;
    }
    if (v->right != nullptr) {
        v->right->parent = v;
    }
}

void small_rotation(Vertex* v) {
    Vertex* parent = v->parent;
    if (parent == nullptr) {
        return;
    }
    Vertex* grandparent = v->parent->parent;
    if (parent->left == v) {
        Vertex* m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Vertex* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != nullptr) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        } else {
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
    if (v == nullptr) return;
    while (v->parent != nullptr) {
        if (v->parent->parent == nullptr) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns nullptr.
Vertex* find(Vertex*& root, int key) {
    Vertex* v = root;
    Vertex* last = root;
    Vertex* next = nullptr;
    while (v != nullptr) {
        if (v->key >= key && (next == nullptr || v->key < next->key)) {
            next = v;
        }
        last = v;
        if (v->key == key) {
            break;
        }
        if (v->key < key) {
            v = v->right;
        } else {
            v = v->left;
        }
    }
    splay(root, last);
    return next;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
    right = find(root, key);
    splay(root, right);
    if (right == nullptr) {
        left = root;
        return;
    }
    left = right->left;
    right->left = nullptr;
    if (left != nullptr) {
        left->parent = nullptr;
    }
    update(left);
    update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    Vertex* min_right = right;
    while (min_right->left != nullptr) {
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

// Code that uses splay tree to solve the problem

Vertex* root = nullptr;

void insert(int x) {
    Vertex* left = nullptr;
    Vertex* right = nullptr;
    Vertex* new_vertex = nullptr;
    split(root, x, left, right);
    if (right == nullptr || right->key != x) {
        new_vertex = new Vertex(x, x, nullptr, nullptr, nullptr);
    }
    root = merge(merge(left, new_vertex), right);
}


bool find(int x) {
    Vertex *N = find(root, x);
    return N != nullptr && N->key == x;
}

void erase(int x) {
    if(!find(x)) return;
    root = merge(root->left, root->right);
    /// Important: Fix the root
    if(root != nullptr) root->parent = nullptr;
}

long long sum(int from, int to) {
    Vertex* left = nullptr, *middle = nullptr, *right = nullptr;
    split(root, from, left, middle);
    split(middle, to + 1, middle, right);
    long long ans = 0;
    /// Most of the work is already done...
    if(middle != nullptr) ans = middle->sum;
    /// Important: Fix the tree & root.
    root = merge(merge(left, middle), right);
    if(root != nullptr) root->parent = nullptr;
    return ans;
}

const int MODULO = 1000000001;

int main(){
    int n; vector<string> result;
    scanf("%d", &n);
    int last_sum_result = 0;
    for (int i = 0; i < n; i++) {
        char buffer[10];
        scanf("%s", buffer);
        char type = buffer[0];
        switch (type) {
            case '+' : {
                int x;
                scanf("%d", &x);
                insert((x + last_sum_result) % MODULO);
            } break;
            case '-' : {
                int x;
                scanf("%d", &x);
                erase((x + last_sum_result) % MODULO);
            } break;
            case '?' : {
                int x;
                scanf("%d", &x);
                result.push_back((find((x + last_sum_result) % MODULO) ? "Found" : "Not found"));
            } break;
            case 's' : {
                int l, r;
                scanf("%d %d", &l, &r);
                long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
                result.push_back(to_string(res));
                last_sum_result = int(res % MODULO);
            }
        }
    }

    for(const auto &r:result)
        cout << r << '\n';

    return 0;
}

