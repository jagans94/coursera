#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

struct MinMax{
    long long min, max;
};

typedef vector<vector<long long>> multi_vector;
typedef vector<long long> single_vector;

long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}

void print_array(const multi_vector &A, const multi_vector &B){
    for(int i=0;i<A.size();++i){
        for(int j=0;j<A[i].size();++j){
            cout << setw(4) << A[i][j] << " ";
        }
        cout << "\t\t";
        for (int j = 0; j < B[i].size(); ++j) {
            cout << setw(4) << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

MinMax get_min_max_values(const string &ops, const multi_vector &max_matrix, const multi_vector &min_matrix, int i, int j){

    long long min_val = std::numeric_limits<int>::max();
    long long max_val = std::numeric_limits<int>::min();

    for(int k=i;k<j;++k){
        long long a = eval(max_matrix[i][k],max_matrix[k+1][j],ops[k]);
        long long b = eval(max_matrix[i][k],min_matrix[k+1][j],ops[k]);
        long long c = eval(min_matrix[i][k],max_matrix[k+1][j],ops[k]);
        long long d = eval(min_matrix[i][k],min_matrix[k+1][j],ops[k]);

        min_val = min(min_val,min(min(a,b),min(c,d)));
        max_val = max(max_val,max(max(a,b),max(c,d)));
    }

    return MinMax{min_val,max_val};
}

long long get_maximum_value(const string &exp) {

    //  splitting the string into operands and operators
    single_vector values; string ops;
    for(int i=0;i<exp.size();++i) {
        //  correction for value conversion from char to int
        values.emplace_back(exp[i]-48);
        ops.push_back(exp[++i]);
    }

    size_t n = values.size();
    multi_vector min_array(n,single_vector (n,0)) , max_array (n,single_vector (n,0));

    //  initializing the matrix
    for(int i=0;i<n;++i){
        max_array[i][i] = values[i];
        min_array[i][i] = values[i];
    }

    //  computing the minimum and maximum values for states represented by i,j
    for(int s=1;s<n;++s){
        for(int i=0;i<n-s;++i){
            int j = i + s;
            min_array[i][j] = get_min_max_values(ops,max_array,min_array,i,j).min;
            max_array[i][j] = get_min_max_values(ops,max_array,min_array,i,j).max;
        }
    }

    //  final solution
    return max_array[0][n-1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}

