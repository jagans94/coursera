#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int edit_distance(const string &str1, const string &str2) {
    int edit_dist = 0, diff;
    size_t n = str1.size(), m = str2.size();
    vector<vector<int>> dist_matrix (n+1,vector<int> (m+1,0));

    for(int i=0;i<n+1;++i){
        dist_matrix[i][0] = i;
    }

    for(int j=0;j<m+1;++j){
        dist_matrix[0][j] = j;
    }

    for(int j=1;j<m+1;++j){
        for(int i=1;i<n+1;++i){
            //  The matrix is indexed from (0..n) and (0...m) respectively.
            //  However, the indexing on strings starts from (1...n) and (1...m).
            //  Therefore, you need to left shift the indexes for a valid comparison.
            if(str1[i-1] == str2[j-1]){
                diff = 0;
                //cout << "i,j: " << i << "," << j << endl;
            }
            else{
                diff = 1;
            }
            dist_matrix[i][j] = min(dist_matrix[i-1][j]+1,dist_matrix[i][j-1]+1);
            dist_matrix[i][j] = min(dist_matrix[i-1][j-1] + diff,dist_matrix[i][j]);
        }
    }

    /*
    for(int i=0;i<n+1;++i) {
        for (int j = 0; j < m + 1; ++j) {
            cout << setw(10) << dist_matrix[i][j];
        }
        cout << '\n';
    }
    cout << endl;
     */

    edit_dist = dist_matrix[n][m];

    return edit_dist;
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}

