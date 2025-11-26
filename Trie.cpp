#include<bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    bool isEnd = false;
    string value;
    unordered_map<char, unique_ptr<TrieNode>> child;
};

class Trie {
private:
    unique_ptr<TrieNode> root;

public:
    Trie() : root(make_unique<TrieNode>()) {}

    void insert(const string& key, const string& value) {
        TrieNode* current = root.get();
        for (char c : key) {
            if (current->child.find(c) == current->child.end()) {
                current->child[c] = make_unique<TrieNode>();
            }
            current = current->child[c].get();
        }
        current->isEnd = true;
        current->value = value;
    }

    optional<string> search(const string& key) const {
        const TrieNode* current = root.get();
        for (char c : key) {
            auto it = current->child.find(c);
            if (it == current->child.end()) return nullopt;
            current = it->second.get();
        }
        return current->isEnd ? optional<string>(current->value) : nullopt;
    }
};

class Router {
private:
    Trie trie;

public:
    void addRoutes(const string& route, const string& value) {
        trie.insert(route, value);
    }

    string getRoute(const string& route) {
        auto result = trie.search(route);
        return result.has_value() ? result.value() : "not found";
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
