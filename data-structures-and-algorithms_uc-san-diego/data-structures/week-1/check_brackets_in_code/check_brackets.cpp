#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <vector>

using namespace std;

struct Bracket {
    Bracket(char type, int position):type(type), position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int check_brackets(const string &string1){
    stack <Bracket> opening_brackets_stack;
    int position;
    for (position = 0; position < string1.length(); ++position) {
        char next = string1[position];

        if (next == '(' || next == '[' || next == '{') {
            opening_brackets_stack.push(Bracket(next,position+1));
        }

        if (next == ')' || next == ']' || next == '}') {
            if(opening_brackets_stack.empty()){
                return position +  1;
            }
            if(opening_brackets_stack.top().Matchc(next)){
                opening_brackets_stack.pop();
            }
            else{
                return position + 1;
            }
        }
    }
    return opening_brackets_stack.empty()?-1: opening_brackets_stack.top().position;
}

void stress_test(int argc, char *argv[]){

    vector<string> results;
    string curr_str;

    ifstream current_file;
    int file_number = 1;

    while(file_number < argc){

        current_file.open (argv[file_number]);

        while(current_file >> curr_str);

        current_file.close();

        if(check_brackets(curr_str) == -1){
            results.push_back("Success");
        }
        else{
            results.push_back(to_string(check_brackets(curr_str)));
        }
        file_number+=2;
    }

    file_number = 2;
    int i=0;
    
    current_file.clear(); // clear stream flags and error state
    current_file.seekg(0, ios::beg); // reset read position

    while(file_number < argc){

        current_file.open (argv[file_number]);

        while(current_file >> curr_str);

        current_file.close();

        if(results[i] == curr_str){
            cout << "Test case #" << i+1 << " Passed." << '\n';
            ++i;
        }
        else{
            cout << "Test case #" << i+1 << " Failed." << '\n';
            cout << "Expected: " << curr_str << " Output: " << results[i] << '\n';
            return;
        }
        file_number+=2;
    }
}

int main(int argc, char *argv[]) {
    std::string text;
    getline(std::cin, text);

    //stress_test(argc,argv);

    if(check_brackets(text) != -1)
        cout << check_brackets(text);
    else
        cout << "Success";
}

