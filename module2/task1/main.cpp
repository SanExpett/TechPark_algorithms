#include <iostream>
#include <string>

constexpr size_t START_MAX_ITEMS_COUNT = 8;
constexpr double MAX_LOAD_FACTOR = 0.75;
constexpr size_t HASH_P1 = 23;
constexpr size_t HASH_P2 = 29;

int hash1(const std::string &key, int size) {
    int hash = 0;
    for(int i = key.size(); i >= 0; i--) {
        hash += (HASH_P1 * hash + key[i]) % size;
    }
    return hash % size;
}

int hash2(const std::string &key, int size) {
    int hash = 0;
    for(int i = key.size(); i >= 0; i--) {
        hash += (HASH_P2 * hash + key[i]) % size;
    }
    return (2 * hash + 1) % size;
}

struct Node {
    std::string key;
    bool deleted; 
    Node(): key(""), deleted(false) {}
    Node(const std::string &k): key(k), deleted(false) {}
};

class HashTable {


public:
    HashTable(): buffer(new Node[START_MAX_ITEMS_COUNT]), max_items_count(START_MAX_ITEMS_COUNT), items_count(0) {
        for(int i = 0; i < START_MAX_ITEMS_COUNT; i++) {
            buffer[i] = Node("");
        }
    }

    ~HashTable() {
        delete[] buffer;
    }
    

    bool find(const std::string&key) const {
        int h1 = hash1(key, max_items_count),
            h2 = hash2(key, max_items_count);
        int i = 0;
        while(buffer[h1].key != "" && i < max_items_count) {
            if(buffer[h1].key == key && !buffer[h1].deleted) {
                return true;
            }

            h1 = (h1 + h2) % max_items_count;
            i++;
        }

        return false;
    }

    bool insert(const std::string &key) {
        if( ((double) items_count / (double) max_items_count) >= MAX_LOAD_FACTOR) {
            grow();
        }

        int h1 = hash1(key, max_items_count),
            h2 = hash2(key, max_items_count);

        int i = 0,
            firstDeleted = -1;
        while(buffer[h1].key != "" && i < max_items_count) {
            if(buffer[h1].key == key && !buffer[h1].deleted) {
                return false;
            }

            if(buffer[h1].deleted && firstDeleted < 0) {
                firstDeleted = h1;
            }

            h1 = (h1 + h2) % max_items_count;
            i++;
        }

        if(firstDeleted < 0) {
            buffer[h1] = Node(key);
        }
        else
        {
            buffer[firstDeleted].key = key;
            buffer[firstDeleted].deleted = false;
        }
        items_count++;

        return true;
    }

    bool erase(const std::string &key) {
        int h1 = hash1(key, max_items_count),
            h2 = hash2(key, max_items_count);
        int i = 0;
        while(buffer[h1].key != "" && i < max_items_count) {
            if(buffer[h1].key == key && !buffer[h1].deleted) {
                // нашли
                buffer[h1].deleted = true;
                items_count--;
                return true;
            }

            h1 = (h1 + h2) % max_items_count;
            i++;
        }

        return false;
    }



private:
    void grow() {
        int newBufferSize = max_items_count * 2;
        Node* newBuffer = new Node[newBufferSize];
        for(int i = 0; i < newBufferSize; i++) {
            newBuffer[i] = Node("");
        }

        for(int i = 0; i < max_items_count; i++) {
            if(buffer[i].key != "" && !buffer[i].deleted) {
                int h1 = hash1(buffer[i].key, newBufferSize),
                    h2 = hash2(buffer[i].key, newBufferSize);

                int j = 0;
                while(newBuffer[h1].key != "" && j < newBufferSize) {
                    h1 = (h1 + h2) % newBufferSize;
                    j++;
                }

                newBuffer[h1] = buffer[i];
            }
        }

        delete[] buffer;
        buffer = newBuffer;
        max_items_count = newBufferSize;
    }

    Node* buffer; 
    int max_items_count;
    int items_count; 
};


int main(){
    HashTable ht;
    char operation;
    std::string key;

    while (std::cin >> operation >> key) {
        switch (operation) {
            case '+':
                if (ht.insert(key))
                    std::cout << "OK" << std::endl;
                else
                    std::cout << "FAIL" << std::endl;
                break;
            case '-':
                if (ht.erase(key))
                    std::cout << "OK" << std::endl;
                else
                    std::cout << "FAIL" << std::endl;
                break;
            case '?':
                if ( ht.find(key) )
                    std::cout << "OK" << std::endl;
                else
                    std::cout << "FAIL" << std::endl;
                break;    
            default:
                break;
        }
    }

    return 0;
}    
