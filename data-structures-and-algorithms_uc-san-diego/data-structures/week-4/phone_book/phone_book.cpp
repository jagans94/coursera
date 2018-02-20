#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#define MAXPHNO 10000000

using namespace std;

typedef unordered_map<int,string> phone_book;

vector<string> process_queries_direct_addressing() {
    size_t n;
    cin >> n;

    int number; string type,name;
    vector<string> queries(MAXPHNO,"");

    vector<string> results;
    while(n > 0){
        cin >> type >> number;
        if (type == "add")
            cin >> queries[number];
        else if (type == "find"){
            string found = (!queries[number].empty())? queries[number] : "not found";
            results.emplace_back(found);
        } else if (type == "del"){
            queries[number] = "";
        }
        --n;
    }
    return results;
}

vector<string> process_queries() {
    size_t n;
    cin >> n;

    int number; string type,name;
    phone_book queries(n);

    vector<string> results;
    while(n > 0){
        cin >> type >> number;
        if (type == "add")
            cin >> queries[number];
        else if (type == "find"){
            string found = (queries.find(number) != queries.end())? queries[number] : "not found";
            results.emplace_back(found);
        } else if (type == "del"){
            queries.erase(number);
        }
        else
            cout << "Invalid Input." << '\n';
        --n;
    }
    return results;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

int main() {
    write_responses(process_queries_direct_addressing());
    return 0;
}

