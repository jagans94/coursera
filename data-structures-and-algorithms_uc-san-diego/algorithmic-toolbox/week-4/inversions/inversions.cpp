#include <iostream>
#include <vector>

using namespace std;

long long merge_count(vector<long long> &v, int left, int center, int right)
{
    int n1 = center - left + 1, n2 =  right - center;
    long long inv_count = 0;
    vector<long long> v1 (n1,0), v2 (n2,0);

    for (int i = 0; i < n1; i++)
        v1[i] = v[left + i];

    for (int j = 0; j < n2; j++)
        v2[j] = v[center + 1 + j];

    int i=0,j=0,k=left;

    while (i < n1 && j < n2){
        if (v1[i] > v2[j]){
            v[k++] = v2[j++];
            //  This is all you really need to do, if you have a working merge sort.
            inv_count+=n1-i;
        }
        if(v1[i] <= v2[j])
            v[k++] = v1[i++];
    }

    while (i < n1)
        v[k++] = v1[i++];

    while (j < n2)
        v[k++] = v2[j++];

    return inv_count;
}

long long count_inversion(vector<long long> &v, int left, int right)
{
    if (left == right) return 0;

    long long inv_count = 0;
    int center = left + (right - left)/2;

    //  Total inversion = Inversion of each half + Inversion b/w the two halves.
    inv_count = count_inversion(v,left,center) + count_inversion(v,center+1,right) + merge_count(v,left,center,right);

    return inv_count;
}

int main() {
    long long n;
    std::cin >> n;
    vector<long long> a(n,0);
    for (long long i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << count_inversion(a, 0, a.size()-1) << '\n';
}

