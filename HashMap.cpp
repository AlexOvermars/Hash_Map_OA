#include "HashMap.h"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

hashMap::hashMap() {
    storage.resize(2);
    size = 0;
}
 
hashMap::hashMap(int cap) {
    storage.resize(cap);
    size = 0;
}

void hashMap::put(int key, int val) {
    int keyIndex = getIndex(key);
    // If load factor is at .5
    if (get_load_factor() >= .5) {
        resize_table(storage.size() * 2);
    }
    //cout << get_load_factor() << endl;
    // If given key already exists
    if (keyIndex != -1) {
        storage[keyIndex][1] = val;
    }

    // Else add the value
    else {
        keyIndex = nextOpen(key);
        storage[keyIndex].push_back(key);
        storage[keyIndex].push_back(val);
        size++;
    }
    //cout << storage.size() << ", ";
}

// How full is the storage (0 to 1)
double hashMap::get_load_factor() {
    return ((double) this->size / (double) this->storage.size());
}

// Returns number of empty spots
int hashMap::empty_buckets() {
    return (storage.size() - size);
}

void hashMap::resize_table(int newCap) {
    // If newCap is smaller than current size
    if (newCap < storage.size()) {
        return;
    }

    // If newCap isn't prime, make it the next largest prime number
    if (!isPrime(newCap)) {
        newCap = nextPrime(newCap);
    }

    // Rehash all pairs
    vector<vector<int>> pairs = get_table();
    this->clear();
    storage.resize(newCap);
    //cout << endl << "Resize: " << endl;
    for (int i=0; i<pairs.size(); i++) {
        //cout << i;
        this->put(pairs[i][0], pairs[i][1]);
    }
    //cout << endl << endl;
}

int hashMap::get(int key) {
    int keyIndex = getIndex(key);
    if (keyIndex != -1) {
        return storage[keyIndex][1];
    }
    return -1;
}

bool hashMap::contains(int key) {
    if (getIndex(key) == -1) {
        return false;
    }
    return true;
}

void hashMap::remove(int key) {
    int keyIndex = this->getIndex(key);
    if ((key < 0) || (keyIndex == -1)) {
        return;
    }
    this->size--;
    storage[keyIndex].clear();
}

void hashMap::clear() {
    int storageSize = storage.size();
    storage.clear();
    storage.resize(storageSize);
    size = 0;
}

// Get every key and value pair
vector<vector<int>> hashMap::get_table() {
    vector<vector<int>> pairs;
    for (int i=0; i<storage.size(); i++) {
        if (!storage[i].empty()) {
            pairs.push_back(storage[i]);
        }
    }
    return pairs;
}

// Next open value using quadratic probing
int hashMap::nextOpen(int key) {
    int keyHash = hash<int>{}(key);
    int trackNum = 0;
    int storeSize = storage.size();

    // Until we find an empty keyHash
    while (!storage[((keyHash + trackNum * trackNum) % storeSize)].empty()) {
        trackNum++;
    }
    return (keyHash + trackNum * trackNum) % storeSize;
}

// Returns index of key
int hashMap::getIndex(int key) {
    int keyHash = hash<int>{}(key);
    int trackNum = 0;
    int keyTrack = keyHash % storage.size();

    // Finds the correct key/value pair
    while ((!storage[keyTrack].empty()) && (storage[keyTrack][0] != key)) {
        trackNum++;
        keyTrack = (keyHash + trackNum * trackNum) % storage.size();
    }

    if (storage[keyTrack].empty()) {
        return -1;
    }
    return keyTrack;
}

// Checks if number is prime
bool hashMap::isPrime(int num) {
    // If the number is a small prime number
    if ((num == 2) || (num == 3)) {
        return true;
    }
    // If the number is 1 or an even number
    else if ((num == 1) || (num%2 == 0)) {
        return false;
    }

    // Checks for if val is divisible by any number other than 1 < val
    int val = ceil(sqrt(num));
    for (int i=2; i<=val; i++) {
        if (num%i == 0) {
            return false;
        }
    }
    return true;
}

// Returns the closest higher prime number
int hashMap::nextPrime(int num) {
    if (num%2 == 0) {
        num++;
    }
    while (!isPrime(num)) {
        num += 2;
    }
    return num;
}

void hashMap::toString() {
    for (int i=0; i<storage.size(); i++) {
        if (storage[i].empty()) {
            cout << "<null, null>, ";
        }
        else {
            cout << "<" << storage[i][0]  << ", " << storage[i][1] << ">, ";
        }
    }
    cout << endl;
}

int hashMap::getSize() {
    return size;
}