#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
#include <iomanip>

using namespace std;

struct Pair{
    int index;
    long long val;

    Pair(int f_idx, long long f_val){
        this->index = f_idx;
        this->val = f_val;
    }
};

class JobQueue {
public:
    size_t num_workers_;
    vector<long long> jobs_;
    vector<Pair> thread_assignment;
    vector<Pair> threads;


    int comp_func(int a, int b){
        if(threads[a].val == threads[b].val)
            return (threads[a].index < threads[b].index)? a : b;
        return (threads[a].val < threads[b].val)? a : b;
    }

    void WriteResponse() {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << thread_assignment[i].index << " " << thread_assignment[i].val << "\n";
        }
    }

    void ReadData() {
        size_t m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for(int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void ReadDataWithFile(ifstream &input_file) {
        size_t m;
        input_file >> num_workers_ >> m;
        jobs_.resize(m);
        for(int i = 0; i < m; ++i)
            input_file >> jobs_[i];
    }

    void sift_down(int i){

        int min_idx = i;
        int l = 2*i+1, r = 2*i + 2;

        min_idx = (l < num_workers_)? comp_func(min_idx,l) : min_idx;
        min_idx = (r < num_workers_)? comp_func(min_idx,r) : min_idx;

        if(i != min_idx){
            swap(threads[min_idx],threads[i]);
            sift_down(min_idx);
        }
    }

    void heapify(vector<Pair> &threads){
        int n = threads.size();
        for(int i=(n-1)/2;i>=0;--i){
            sift_down(i);
        }
    }

    void AssignJobs() {
        thread_assignment.resize(jobs_.size(),Pair{-1,-1});
        threads.resize(num_workers_,Pair{-1,-1});
        long long limit = min(jobs_.size(),num_workers_);
        for(int i=0;i<limit;++i){
            thread_assignment[i] = Pair{i,0};
            threads[i] = Pair{i,jobs_[i]};
        }

        if(num_workers_ > jobs_.size())
            return;

        heapify(threads);

        for(int i=num_workers_;i<jobs_.size();++i){
            thread_assignment[i] = Pair{threads[0].index,threads[0].val};
            threads[0].val += jobs_[i];
            sift_down(0);
        }
    }

    void Validate(ifstream &solution_file) {
        long long i = 0, y, z;

        while (solution_file >> y >> z) {

            if(y != thread_assignment[i].index && z != thread_assignment[i].val){
                cout << "Test Case Failed." << '\n';
                cout << "iteration: " << i << endl;
                //cout << "Expected: " << setw(6) << y << " " << setw(6) << z << setw(12) <<
                //        " Obtained: " << setw(6) << thread_assignment[i].index << " " << setw(6) << thread_assignment[i].val << setw(12) <<
                //        " Matches: " << setw(6) << (y == thread_assignment[i].index && z == thread_assignment[i].val)? "Yes" : "No";
                //cout << endl;
                return;
                }
            ++i;
        }
        cout << "Test Case Passed." << '\n';
    }

public:
    void SolveWithFile() {
        //ifstream input_file("02"), solution_file("02.a");
        ifstream input_file("08"), solution_file("08.a");
        cout << "Reading File ..." << endl;
        ReadDataWithFile(input_file);
        cout << "Computing values ..." << endl;
        AssignJobs();
        cout << "Testing values ..." << endl;
        Validate(solution_file);

        input_file.close();
        solution_file.close();
    }

    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}

