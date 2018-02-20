#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <iomanip>


using namespace std;

struct Query {
    string type, s;
    size_t key;
};

class QueryProcessor {

    size_t bucket_count;
    vector<list<string>> hash_table;
    vector<string> results;

public:

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }


    explicit QueryProcessor(size_t bucket_count): bucket_count(bucket_count) {hash_table.resize(bucket_count);}

    Query readQuery() {
        Query query;
        cin >> query.type;
        if(query.type != "check"){
            cin >> query.s;
            query.key = hash_func(query.s);
        }
        else
            cin >> query.key;
        return query;
    }

    Query readQueryFromAFile(ifstream &input_file) {
        Query query;
        input_file >> query.type;
        if(query.type != "check"){
            input_file >> query.s;
            query.key = hash_func(query.s);
        }
        else
            input_file >> query.key;
        return query;
    }

    void processTheQuery(const Query& query) {

        if(query.type == "check"){
            for(const auto &each : hash_table[query.key]){
                cout << each << " ";
                //results.emplace_back(each);
            }
            cout <<'\n';
        }

        auto it = find(hash_table[query.key].begin(),hash_table[query.key].end(),query.s);
        bool exists = it != hash_table[query.key].end();

        if(query.type == "find"){
            cout << (exists?"yes":"no") << '\n';
            //results.emplace_back((exists?"yes":"no"));
        }

        //  Delete 'only' if the item exists.
        //  Add 'only' if the item doesn't exist.
        if(exists){
            if(query.type == "del")
                hash_table[query.key].remove(query.s);
        } else{
            if (query.type == "add")
                hash_table[query.key].push_front(query.s);
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processTheQuery(readQuery());
    }

    void processQueriesFromAFile(ifstream &input_file,ifstream &output_file) {
        size_t n;
        input_file >> n;
        for (int i = 0; i < n; ++i){
            processTheQuery(readQueryFromAFile(input_file));
        }

        int i = 0;
        string line;
        while (output_file >> line){
            cout << line << '\t' << results[i++] << '\n';
        }

    }
};

int main() {

    /*
    ifstream input_file("06"),solution_file("06.a");
    size_t bucket_count;
    input_file >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueriesFromAFile(input_file, solution_file);
    input_file.close(); solution_file.close();
    */

    //  /*
    std::ios_base::sync_with_stdio(false);
    size_t bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    //  */
    return 0;
}

