#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void print_array(const vector<int> & v){
    for(const int &val:v){
        cout << val << " ";
    }
    cout << endl;
}

void swap (int &a , int &b){
    int temp = a;
    a = b;
    b = temp;
}

pair<int,int> partition_3way(vector<int> &a, int left, int right){
    int i = left, j = right;
    int p = left, q = right;

    while(true){
        while(++i < right && a[i] < a[left]);
        while(--j > left && a[j] > a[left]);

        if(i>=j) break;

        swap(a[i],a[j]);

        if(a[i] == a[left]){
            swap(a[++p],a[i]);
        }

        if(a[j] == a[left]){
            swap(a[--q],a[j]);
        }
    }

    j = i-1;
    i = j+1;

    for (int k = left; k <= p; k++){
        swap(a[k], a[j--]);
    }

    for (int k = right-1; k >= q; k--){
        swap(a[i++], a[k]);
    }

    return make_pair(j+1,i);

}

void randomized_quick_sort3(vector<int> &a, int left, int right) {

    if (left == right) return;
    if (left + 1 == right) return;

    int pivot = left + rand() % (right-left);
    swap(a[left],a[pivot]);

    pair<int,int> keys = partition_3way(a,left,right);
    int m1 = keys.first, m2 = keys.second;

    randomized_quick_sort3(a,left,m1);
    randomized_quick_sort3(a,m2,right);
}

void stress_test(int n, int a_max){

    int testcase_number = 0;
    while(true){

        testcase_number++;

        vector<int> v_sort(n,0);
        for(int i=0;i<n;++i){
            v_sort[i] = 1 + rand() % a_max;
        }
        vector<int> v_rq_sort = v_sort;

        //cout << "Unsorted Array: " << '\n';
        //print_array(v_rq_sort);

        sort(v_sort.begin(),v_sort.end());

        //cout << "Sorted Array: 'STL sort' " << '\n';
        //print_array(v_sort);

        randomized_quick_sort3(v_rq_sort,0,v_rq_sort.size());

        //cout << "Sorted Array: 'randomized quick sort' " << '\n';
        //print_array(v_rq_sort);

        for(int i=0;i<v_rq_sort.size();++i){
            if (v_rq_sort[i] != v_sort[i]){
                cout << "Testcase #" << testcase_number <<  " Failed." << endl;
                return;
            }
        }
        cout << "Testcase #" << testcase_number <<  " Passed." << endl;
    }

}

int main() {
    srand(time(0));

    int n;
    std::cin >> n;
    vector<int> a(n,0);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    randomized_quick_sort3(a, 0, a.size());

    print_array(a);

    //stress_test(10000,10000);

}


