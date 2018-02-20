#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

struct DisjointSetsElement {
    long long size;
    int parent, rank;

    DisjointSetsElement(long long size = 0, int parent = -1, int rank = 0):
            size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
    long long size;
    long long max_table_size;
    vector <DisjointSetsElement> sets;

    DisjointSets(long long size): size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }

    int getParent(int table) {
        if(sets[table].parent != table){
            sets[table].parent = getParent(sets[table].parent);
        }
        return sets[table].parent;
    }

    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);

        if (realDestination == realSource)
            return;

        if (sets[realDestination].rank > sets[realSource].rank) {
            sets[realSource].parent = realDestination;
        } else {
            sets[realDestination].parent = realSource;
            if (sets[realDestination].rank == sets[realSource].rank)
                ++sets[realDestination].rank;
            swap(realDestination,realSource);
        }

        sets[realDestination].size += sets[realSource].size;
        sets[realSource].size = 0;
        max_table_size = max(max_table_size, sets[realDestination].size);

    }
};

void stress_test(){

    ifstream input_file("116"), solution_file("116.a");

    int n,m;
    long long result;

    //  input:
    input_file >> n >> m;
    DisjointSets tables(n);
    for (auto &table : tables.sets) {
        input_file >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }

    cout << "Testing...";
    for (int i = 0; i < m; i++) {
        int destination, source;
        input_file >> destination >> source;
        --destination;
        --source;
        tables.merge(destination, source);

        //  verification:
        solution_file >> result;
        if(result != tables.max_table_size){
            cout << "Test Case Failed." << '\n';
            cout << "Expected: " << result << " Obtained: " << tables.max_table_size << '\n';
            return;
        }
    }

    cout << "Test Case Passed." << '\n';

    input_file.close();
    solution_file.close();
}


int main() {

    //stress_test();

    // /*
    int n, m;
    cin >> n >> m;

    DisjointSets tables(n);
    for (auto &table : tables.sets) {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }

    for (int i = 0; i < m; i++) {
        int destination, source;
        cin >> destination >> source;
        --destination;
        --source;

        tables.merge(destination, source);
        cout << tables.max_table_size << '\n';
    }

    // */

    return 0;
}

