#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

//  custom data structure
class Pair{
public:
    int point;
    char type;
    int count = 0;
    int index = -1;

    Pair(int f_point, char f_type){
        this->point = f_point;
        this->type = f_type;
    }
};

//  lambda function
bool sort_func(Pair &A, Pair &B){
    if(A.point == B.point){
        return A.type < B.type;
    }
    return A.point<B.point;
}

bool sort_func_revert(Pair &A, Pair &B){
    return A.index < B.index;
}

void fast_count_segments(vector<Pair> &pairs){

    /*
    cout << "Before Sorting: " << '\n';
    for(int i=0;i<pairs.size();++i){
        cout << '(' << pairs[i].point << ',' << pairs[i].type << ')' << " ";
    }
    cout << '\n';
     */

    sort(pairs.begin(),pairs.end(),sort_func);

    /*
    cout << "After Sorting: " << '\n';
    for(int i=0;i<pairs.size();++i){
        cout << '(' << pairs[i].point << ',' << pairs[i].type << ')' << " ";
    }
    cout << '\n';
    */

    int i=0,j=pairs.size()-1;
    int count_L = 0, count_R = 0;

    while(i < pairs.size() && j > -1){
        if(pairs[i].type == 'L'){
            ++count_L;
        }
        else if(pairs[i].type == 'P'){
            pairs[i].count += count_L;
        }
        if(pairs[j].type == 'R'){
            ++count_R;
        }
        else if(pairs[j].type == 'P'){
            pairs[j].count += count_R;
        }
        ++i; --j;
    }
    sort(pairs.begin(),pairs.end(), sort_func_revert);
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

void print_array(const vector<int> &arr){
    cout << endl;
    for(int i=0;i<arr.size();++i){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void stress_test(size_t n, size_t  m, int a_max, int a_min){

    int j = 1;
    while(true){
        vector<int> starts(n), ends(n), points(m);
        vector<Pair> pairs;

        for (size_t i = 0; i < starts.size(); i++) {
            starts[i] = a_min + rand()%(a_max-a_min);
            pairs.emplace_back(Pair(starts[i],'L'));
            ends[i] = starts[i] + rand()%(a_max-starts[i]);
            pairs.emplace_back(Pair(ends[i],'R'));
        }

        for (size_t i = 0; i < points.size(); i++) {
            points[i] = a_min + rand()%(a_max-a_min);
            pairs.emplace_back(Pair(points[i],'P'));
            pairs.back().index = i;
        }

        //  naive solution
        vector<int> count_naive = naive_count_segments(starts,ends,points);

        //  fast solution
        fast_count_segments(pairs);
        vector<int> count_fast;
        for(int i=0;i<pairs.size();++i){
            if(pairs[i].index != -1){
                count_fast.push_back(pairs[i].count - n);
            }
        }

        bool break_flag = false;

        cout << "Testcase #" << j++ ;
        for (size_t i = 0; i < count_naive.size(); i++) {
            if(count_naive[i] != count_fast[i]){
                cout << " Failed." << '\n';
                break_flag = true;
                break;
            }
        }
        if (break_flag){
            cout << "line segment - starts: ";
            print_array(starts);
            cout << "line segment - ends: ";
            print_array(ends);
            cout << "points: ";
            print_array(points);
            cout << "naive solution: ";
            print_array(count_naive);
            cout << "fast solution: " << '\n';
            print_array(count_fast);
            break;
        }

        cout << " Passed." << '\n';
    }

}

int main() {

    //srand(time(0));
    //stress_test(3902,2839, 232324, -44242);

    size_t n, m;
    cin >> n >> m;

    vector<int> starts(n), ends(n);
    vector<Pair> pairs;

    for (size_t i = 0; i < starts.size(); i++) {
        cin >> starts[i] >> ends[i];
        pairs.emplace_back(Pair(starts[i],'L'));
        pairs.emplace_back(Pair(ends[i],'R'));
    }

    vector<int> points(m);
    int init_val = -starts.size();

    for (size_t i = 0; i < points.size(); i++) {
        cin >> points[i];
        pairs.emplace_back(Pair(points[i],'P'));
        pairs.back().index = i;
    }
    cout << endl;

    fast_count_segments(pairs);

    for(int i=0;i<pairs.size();++i){
        if(pairs[i].index != -1){
            cout << pairs[i].count - n << " ";
        }
    }
}

