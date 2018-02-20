#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

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

int get_median_element(vector<int> &a, int left, int right) {

    if (left == right) return -1;
    if (left + 1 == right) return a[left];

    int med_pos = (a.size()-1)/2;

    //Randomly select the pivot
    int pivot = left + rand()%(right - left);
    swap(a[left],a[pivot]);

    pair<int,int> keys = partition_3way(a,left,right);
    int m1 = keys.first, m2 = keys.second;

    if(med_pos < m1){
        return get_median_element(a,left,m1);
    }

    if (med_pos > m2){
        return get_median_element(a,m2,right);
    }

    return a[med_pos];
}

int get_majority_element(vector<int> &a, int left, int right) {

    srand(time(0));
    int median = get_median_element(a, left, right);
    int count = 0;
    for (int i = 0; i < right && count <= right/2 ; ++i){
        if (a[i] == median) {
            ++count;
        }
    }
    return (count > right/2)? median : -1;
}

int moores_voting_algorithm(vector<int> &a){
    int pos = 0, count = 1;

    //  To obtain the majority element.
    for(int i=1;i<a.size();++i){
        if(a[pos] == a[i]){
            ++count;
        }
        else{
            --count;
        }
        if(count == 0){
            pos = i;
            //  Don't forget to reset the count.
            count = 1;
        }
    }

    count = 0;

    //  To check whether the element we obtained is a majority element.
    for (int i = 0; i < a.size() && count <= a.size()/2 ; ++i){
        if (a[i] == a[pos]) {
            ++count;
        }
    }
    return (count > a.size()/2)? a[pos] : -1;
}

void stress_test(int n, int a_max){

    int testcase_number = 0;
    while(true) {

        testcase_number++;

        vector<int> v(n, 0);
        for (int i = 0; i < n; ++i) {
            v[i] = 1 + rand() % a_max;
        }

        int gt_maj = get_majority_element(v, 0, v.size());
        int mva = moores_voting_algorithm(v);

        if (gt_maj != mva) {
            cout << "Testcase #" << testcase_number << " Failed." << endl;
            return;
        }
        cout << "Testcase #" << testcase_number << " Passed." << endl;
    }
}

int main() {
    
    int n;
    std::cin >> n;
    vector<int> a(n,0);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    //std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
    std::cout << (moores_voting_algorithm(a) != -1) << '\n';

    //stress_test(10000,1000);

}


