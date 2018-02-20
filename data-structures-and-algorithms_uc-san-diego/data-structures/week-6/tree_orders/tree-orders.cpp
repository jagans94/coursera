#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iterator>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders {

    size_t n;
    vector <int> key;
    vector <int> left;
    vector <int> right;

    vector <int> result;

public:
    void read() {
        cin >> n;
        key.resize(n);left.resize(n);right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }

    void readFromAFile(ifstream &inputFile) {
        inputFile >> n;
        key.resize(n);left.resize(n);right.resize(n);
        for (int i = 0; i < n; i++) {
            inputFile >> key[i] >> left[i] >> right[i];
        }
        inputFile.close();
    }

    void inorderTraversal(int i=0) {
        int current_state = i;
        stack<int> _stack;

        while(!_stack.empty() || current_state != -1){
            if(current_state != -1){
                _stack.push(current_state);
                current_state = left[current_state];
            }
            else{
                current_state = _stack.top(); _stack.pop();
                result.emplace_back(key[current_state]);
                current_state = right[current_state];
            }
        }
    }

    void preorderTraversal(int i=0) {
        if (i == -1) return;
        stack<int> _stack;
        _stack.push(i);

        while (!_stack.empty()) {
            int current_state = _stack.top();
            result.emplace_back(key[current_state]);
            _stack.pop();

            if (right[current_state] != -1) _stack.push(right[current_state]);
            if (left[current_state]  != -1) _stack.push(left[current_state]);

        }
    }


    void postorderTraversal(int i=0) {
        if (i == -1) return;
        stack<int> _stack;
        _stack.push(i);
        vector<int> result;

        while (!_stack.empty()) {
            int current_state = _stack.top();
            result.emplace_back(key[current_state]);
            _stack.pop();

            if (left[current_state] != -1) _stack.push(left[current_state]);
            if (right[current_state]  != -1) _stack.push(right[current_state]);

        }
        reverse(result.begin(),result.end());
        for(const int &each : result){
            TreeOrders::result.emplace_back(each);
        }
    }

    void print() {
        for (size_t i = 0; i < result.size(); i++) {
            if (i == result.size()/3 || i == 2*result.size()/3) {
                cout << "\n";
            }
            cout << result[i] << " ";
        }
    }

    void checker(ifstream &solutionFile){
        int val;
        for(const int &each:result){
            solutionFile >> val;
            if(each != val){
                cout << "Expected: " << setw(10) <<  val << " Obtained: " << setw(10) << each << '\n';
                cout << "Test Case Failed.";
                return;
            }
        }
        cout << "Test Case Passed. ";
        solutionFile.close();
    }

    void validate(){
        cout << "accessing test files...\n";
        ifstream input_file("21"), solution_file("21.a");
        cout << "reading the test file \n";
        readFromAFile(input_file);
        cout << "performing traversals...\n";
        inorderTraversal(); preorderTraversal(); postorderTraversal();
        cout << "validating the solution\n";
        checker(solution_file);
    }
};

int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    TreeOrders t;
    //t.validate();
    t.read();
    t.inorderTraversal();
    t.preorderTraversal();
    t.postorderTraversal();
    t.print();
    return 0;
}

int main (int argc, char **argv)
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

    return main_with_large_stack_space();
}


