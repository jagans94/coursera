#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;



class HeapBuilder {
private:
    vector<long long> data_;
    vector< pair<int, int> > swaps_;

    void sift_down(int i){

        int min_idx = i;
        int l = 2*i+1, r = 2*i + 2;

        if(l < data_.size() && data_[l] < data_[min_idx]){
            min_idx = l;
        }

        if(r < data_.size() && data_[r] < data_[min_idx]){
            min_idx = r;
        }

        if(i != min_idx){
            swaps_.emplace_back(make_pair(i,min_idx));
            swap(data_[min_idx],data_[i]);
            sift_down(min_idx);
        }
    }

    void WriteResponse() {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    void ReadDataFromAFile(ifstream &input_file) {
        int i=0,n;
        input_file >> n;
        data_.resize(n);

        while(input_file >> data_[i++]);
    }

    void GenerateSwaps() {
        swaps_.clear();

        int n = data_.size();
        for(int i=(n-1)/2;i>=0;--i){
            sift_down(i);
        }
    }

    void Validate(ifstream &solution_file) {
        int i=0,x,y,z;
        solution_file >> x;
        if(x != swaps_.size()){
            cout << "Test Case Failed." << '\n';
            return;
        }
        while(solution_file >> y >> z){
            if(y == swaps_[i].first && z == swaps_[i].second){
                ++i;
                continue;
            }
            cout << "Test Case Failed." << '\n';
        }
        cout << "Test Case Passed." << '\n';
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }

    void SolveFromAFile() {

        ifstream input_file("04");
        ifstream solution_file("04.a");

        ReadDataFromAFile(input_file);
        GenerateSwaps();
        Validate(solution_file);

        input_file.close();
        solution_file.close();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}


