#include<bits/stdc++.h>
using namespace std;

class TrieNode {
public:    
    string value = "";
    map<char, TrieNode*> child;
    
    ~TrieNode() {
        for (auto& p : child) {
            delete p.second;
        }
    }
};

class Trie {
    TrieNode* root;
public:    
    Trie() {
        root = new TrieNode;
    }
    
    ~Trie() {
        delete root;
    }
    
public:
    void insert(const string &key, const string &value) {
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
    
    optional<string> search(const string &key) const {
        TrieNode* current = root;
        int size = key.size();
        for (int i = 0; i < size; i++) {
            if (current->child.find(key[i]) == current->child.end()) {
                return nullopt;
            }
            current = current->child[key[i]];
        }
        if (current->value == "") {
            return nullopt;
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
    
    ~Router() {
        delete t;
    }
    
    void addRoutes(const string &route, const string &value) {
        t->insert(route, value);
    }
    
    string getRoute(string route) {
        auto res = t->search(route);
        return res.value_or("not found");
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
