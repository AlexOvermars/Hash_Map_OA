#ifndef HASHMAPOPENADDRESSING_HASHMAP_H
#define HASHMAPOPENADDRESSING_HASHMAP_H
#include <vector>


class hashMap {
private:
    std::vector<std::vector<int>> storage;
    int size;

    int nextOpen(int key);
    bool isPrime(int num);
    int nextPrime(int num);

public:
    hashMap();
    hashMap(int cap);
    void put(int key, int val);
    double get_load_factor();
    int empty_buckets();
    void resize_table(int newCap);
    int get(int key);
    bool contains(int key);
    void remove(int key);
    void clear();
    std::vector<std::vector<int>> get_table();
    int getIndex(int key);
    int getSize();
    void toString();
};

#endif //HASHMAPOPENADDRESSING_HASHMAP_H
