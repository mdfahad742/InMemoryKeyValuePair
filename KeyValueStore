#include <bits/stdc++.h>
using namespace std;

class KeyValueStore {
private:
    map<string, string> &store;
    list<map<string, string>> &transactionStack;
    bool &isTransactionStarted;
    mutex &mtx;
    
public:
    KeyValueStore(map<string, string> &store, list<map<string, string>> &transactionStack, bool &isTransactionStarted, mutex &mtx) : store(store), transactionStack(transactionStack), isTransactionStarted(isTransactionStarted), mtx(mtx) {}

    ~KeyValueStore() {}

    void create(string key, string value) {
      {
        lock_guard<mutex> lock(mtx);
        if (!this->isTransactionStarted) {
          this->store[key] = value;
        } else {
          map<string, string> transactionStore;
          if (this->transactionStack.size() > 0) {
            transactionStore = this->transactionStack.back();
          }
          transactionStore[key] = value;
          this->transactionStack.push_back(transactionStore);
        }
        cout << "create success key: " << key << ", value: " << value << '\n';
      }
    }

    string read(string key) {
      if (this->transactionStack.size() > 0) {
        map<string, string> transactionStore = this->transactionStack.back();
        if (this->isTransactionStarted && transactionStore.find(key) != transactionStore.end() && transactionStore[key] != "-1") {
          return transactionStore[key];
        }
      }
      if (store.find(key) != store.end()) {
        return store[key];
      } 
      return "Not Found";
    }

    void update(string key, string value) {
      if (!this->isTransactionStarted && this->store.find(key) != this->store.end()) {
        lock_guard<mutex> lock(mtx);
        cout << "update success key: " << key << ", value: " << value << '\n';
        store[key] = value;
        return;
      }
      map<string, string> transactionStore;
      if (this->transactionStack.size() > 0) {
        transactionStore = this->transactionStack.back();
      }
      if (this->isTransactionStarted && (this->store.find(key) != this->store.end() || transactionStore.find(key) != transactionStore.end())) {
        lock_guard<mutex> lock(mtx);
        transactionStore[key] = value;
        this->transactionStack.push_back(transactionStore);
        
        cout << "update success key: " << key << ", value: " << value << '\n';
        return;
      }
      cout << "key: " << key << "not found to update\n" << key;
      return;
    }

    void remove(string key) {
      map<string, string> transactionStore = this->transactionStack.back();
      if (this->isTransactionStarted && transactionStore.find(key) != transactionStore.end()) {
        lock_guard<mutex> lock(mtx);
        transactionStore.erase(key);
        this->transactionStack.push_back(transactionStore);
        cout << "delete success key: " << key << "\n";
        return;
      } else if (!this->isTransactionStarted && this->store.find(key) != this->store.end()) {
        lock_guard<mutex> lock(mtx);
        this->store.erase(key);
        cout << "delete success key: " << key << "\n";
        return;
      } else if (this->store.find(key) != this->store.end()) {
        lock_guard<mutex> lock(mtx);
        transactionStore[key] = "-1";
        this->transactionStack.push_back(transactionStore);
        cout << "delete will be done in main store after commit for key: " << key << "\n";
        return;
      }
      cout << "key: " << key << "not found to delete\n" << key;
      return;
    }

    void begin() {
      if (this->isTransactionStarted) {
        cout << "Multiple begin for a transaction is not allowed\n";
        return;
      }
      {
        lock_guard<mutex> lock(mtx);
        while (!this->transactionStack.empty()) {
          this->transactionStack.pop_back();
        }
        this->isTransactionStarted = true;
        cout << "Transaction begin\n";
      }
    }

    void rollback() {
      if (!this->isTransactionStarted) {
        cout << "No transaction to rollback\n";
        return;
      }
      {
        lock_guard<mutex> lock(mtx);
        while (!this->transactionStack.empty()) {
          this->transactionStack.pop_back();
        }
        this->isTransactionStarted = false;
        cout << "rollback success\n";
      }
    }

    void rollback(int times) {
      if (!this->isTransactionStarted) {
        cout << "No transaction to rollback\n";
        return;
      }
      {
        lock_guard<mutex> lock(mtx);
        while (!this->transactionStack.empty() && times > 0) {
          this->transactionStack.pop_back();
          times--;
        }
        // this->isTransactionStarted = false;
        cout << "rollback success\n";
      }
    }

    void commit() {
      if (!this -> isTransactionStarted || this->transactionStack.size() == 0) {
        cout << "No transaction to commit\n";
        return;
      }
      {
        lock_guard<mutex> lock(mtx);
        for (auto it : this->transactionStack.back()) {
          if (it.second != "-1") {
            this->store[it.first] = it.second;
          } else {
            this->store.erase(it.first);
          }
        }
        while (!this->transactionStack.empty()) {
          this->transactionStack.pop_back();
        }
        this->isTransactionStarted = false;
        cout << "commit success\n";
      }
    }

    void commit(int times) {
      if (!this -> isTransactionStarted || this->transactionStack.size() == 0) {
        cout << "No transaction to commit\n";
        return;
      }
      {
        lock_guard<mutex> lock(mtx);

        while (!this->transactionStack.empty() && times > 0) {
          map<string, string> transactionStore = this->transactionStack.front();
          for (auto it : this->transactionStack.front()) {
            // cout << it.first << " " << it.second << '\n';
            if (it.second != "-1") {
              this->store[it.first] = it.second;
            } else {
              this->store.erase(it.first);
            }
          }
          this->transactionStack.pop_front();
          times--;
        }        
        this->isTransactionStarted = false;
        cout << "commit success\n";
      }
    }
    
};

int main() { 
  cout << "Hello World!\n"; 
  map<string, string> cache;
  mutex mtx;
  list<map<string, string>> transactionStack;
  bool isTransactionStarted = false;
  KeyValueStore *store = new KeyValueStore(cache, transactionStack, isTransactionStarted, mtx);
  store->create("key1", "value1");
  store->create("key2", "value2");
  store->create("key3", "value3");
  cout << "read: key1 " << store->read("key1") << "\n";
  cout << "read: key2 " << store->read("key2") << "\n";
  cout << "read: key3 " << store->read("key3") << "\n";
  
  store->begin();
  cout << "done begin\n";
  store->create("key3", "value8");
  cout << "read: key3 " << store->read("key3") << "\n";
  store->create("key5", "value5");
  cout << "read: key 5 " << store->read("key5") << "\n";
  store->update("key5", "value7");

  cout << "read: key 5 " << store->read("key5") << "\n";
  store->update("key2", "value7");

  cout << "read: key 2 " << store->read("key2") << "\n";
  store->update("key2", "value8");

  cout << "read: key 2 " << store->read("key2") << "\n";
  store->remove("key1");

  cout << "read: key1 " << store->read("key1") << "\n";
  store->rollback(2);

  cout << "read: key1  " << store->read("key1") << "\n";
  cout << "read: key2 " << store->read("key2") << "\n";
  cout << "read: key3 " << store->read("key3") << "\n";
  cout << "read: key5 " << store->read("key5") << "\n";
  
}
