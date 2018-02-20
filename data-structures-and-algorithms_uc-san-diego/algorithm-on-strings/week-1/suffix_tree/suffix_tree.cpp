#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

struct Node{
    int index; unordered_map<char,Node*> children;
    Node(int _i):index(_i){}
    void set_child(char ch,int ch_index){
        children[ch] = new Node(ch_index);
    }
};

class Suffix_Tree{
    Node root = Node(0);
    string text;
public:
    /// constructor
    explicit Suffix_Tree(string &_text):text(_text){}
    /// builds suffix tree
    void build() {
        for(int i=0;i<text.size();++i){
            Node* current_node = &root; int j = i;
            while(current_node->children.find(text[j]) !=  current_node->children.end()){
                current_node = current_node->children[text[j]];
                ++j;
            }
            current_node->set_child(text[j],j+1);
        }
    }
    /// prints suffixes
    void print_suffixes(){
        string s;
        suffixes_helper(s,&root);
    }

private:
    void suffixes_helper(string s, Node* curr_node){
        if(curr_node->children.empty()) return;
        for(auto &each:curr_node->children){
            s.push_back(each.first);
            //cout << s << '\n';
            suffixes_helper(s,each.second);
            cout << s + text.substr(each.second->index) << '\n';
            s.pop_back();
        }
    }
};

int main() {
    string text;
    cin >> text;

    Suffix_Tree sft(text);
    sft.build();
    sft.print_suffixes();

    return 0;
}


