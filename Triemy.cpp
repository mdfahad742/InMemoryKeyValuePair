#include<bits/stdc++.h>
using namespace std;

class TrieNode {
public:    
    string value = "";
    map<char, TrieNode*> child;
};

class Trie {
    TrieNode* root;
public:    
    Trie() {
        root = new TrieNode;
    }
    
public:
    void insert(string key, string value) {
        TrieNode* current = root;
        int size = key.size();
        for (int i = 0; i < size; i++) {
            if (current->child.find(key[i]) == current->child.end()) {
                current->child[key[i]] = new TrieNode();
            }
            current = current->child[key[i]];
        }
        current->value = value;
    }
    
    string search(string key) {
        TrieNode* current = root;
        int size = key.size();
        for (int i = 0; i < size; i++) {
            if (current->child.find(key[i]) == current->child.end()) {
                return "not found";
            }
            current = current->child[key[i]];
        }
        if (current->value == "") {
            return "not found";
        }
        return current->value;
    } 
};

class Router {
    
    Trie* t;
public:    
    Router() {
        t = new Trie();
    }
    
    void addRoutes(string route, string value) {
        t->insert(route, value);
    }
    
    string getRoute(string route) {
        return t->search(route);
    }
    
};




int main() {
    Router r;
    r.addRoutes("/foo", "value");
    r.addRoutes("/foo/bar", "happy");
    cout << r.getRoute("/foo") << endl;
    cout << r.getRoute("/foo/bar") << endl;
    return 0;
}
