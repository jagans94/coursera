#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
        this->parent = nullptr;
    }

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};

int tree_height_brute_force(vector<Node> &nodes){

    int maxHeight = 0;
    for (int leaf_index = 0; leaf_index < nodes.size(); leaf_index++) {
        int height = 0;
        for (Node *v = &nodes[leaf_index]; v != nullptr; v = v->parent)
            height++;
        maxHeight = std::max(maxHeight, height);
    }

    return maxHeight;
}

int tree_height_lot(Node *root_node){
    queue<Node*> q1;
    q1.push(root_node);
    auto *current_node = new Node;

    while(!q1.empty()){
        current_node = q1.front();
        if(!current_node->children.empty()){
            for(const auto &item : current_node->children){
                q1.push(item);
            }
        }
        q1.pop();
    }

    int tree_height = 1;
    while(current_node->key != root_node->key){
        current_node = current_node->parent;
        tree_height++;
    }

    return tree_height;
}

void stress_test(int argc, char *argv[]){

    ifstream input_file;
    int file_number = 1;
    int i = 0;

    while(file_number < argc){

        input_file.open (argv[file_number]);

        size_t n;
        input_file >> n;

        auto *root_node = new Node();
        vector<Node> nodes(n);

        for (int child_index = 0; child_index < n; child_index++) {
            int parent_index;
            input_file >> parent_index;
            if (parent_index >= 0)
                nodes[child_index].setParent(&nodes[parent_index]);
            else
                root_node = &nodes[child_index];
            nodes[child_index].key = child_index;
        }

        input_file.close();

        ++file_number;
        input_file.open (argv[file_number]);

        int result;
        input_file >> result;

        input_file.close();

        if(result == tree_height_lot(root_node)){
            cout << "Test case #" << i+1 << " Passed." << '\n';
            ++i;
        }
        else {
            cout << "Test case #" << i+1 << " Failed." << '\n';
            cout << "Expected: " << result << " Output: " << tree_height_lot(root_node) << '\n';
            return;
        }

        ++file_number;
    }
}

int main_with_large_stack_space(int argc, char *argv[]) {
    std::ios_base::sync_with_stdio(0);

    //stress_test(argc,argv);

    size_t n;
    std::cin >> n;

    auto *root_node = new Node();
    std::vector<Node> nodes(n);

    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0)
            nodes[child_index].setParent(&nodes[parent_index]);
        else
            root_node = &nodes[child_index];
        nodes[child_index].key = child_index;
    }

    //cout << "Faster Method: ";
    cout << tree_height_lot(root_node) << endl;
    //cout << "Bruteforce Method: " << tree_height_brute_force(nodes) << std::endl;

    return 0;
}

int main (int argc, char *argv[])
{
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
    return main_with_large_stack_space(argc,argv);
}

