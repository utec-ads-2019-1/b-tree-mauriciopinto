#ifndef NODE_H
#define NODE_H

#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
class node;

template <typename T>
class key {
public:
    T data;
    node<T>* left; 
    node<T>* right;

    key(T data) : data(data), right(nullptr), left(nullptr){};
};


template <typename T>
class node {
public:
    unsigned int size;
    vector<key<T>*> keys;
    typename vector<key<T>*>::iterator ki;
    vector<node<T>*> childs;
    typename vector<node<T>*>::iterator ni;
    bool isLeaf;

    node(unsigned int size, bool isLeaf = true) : size(size), isLeaf(isLeaf) {}

    bool findKey(T data){
        for(int i = 0; i < keys.size() - 1; i++){
            cout << keys[i]->data << endl;
            if (keys[i]->data == data) return true;
            if (data > keys[i]->data){
                if(data < keys[i+1]->data){
                    cout << "searching on " << keys[i]->data << " right node" << endl; 
                    if(keys[i]->right) keys[i]->right->findKey(data);
                    else return false;
                }
                else if(data > keys[i+1]->data){
                    if(i + 2 == keys.size()){
                        if(keys[i+1]->right) keys[i+1]->right->findKey(data);
                        else return false;
                    }
                    else continue;
                }
            }
            else if(data < keys[i]->data) {
                if(keys[i]->left) keys[i]->left->findKey(data);
                else return false; 
            }
        }
        return false;
    }

    unsigned int getSize(){
        return size;
    }
    vector<key<T>*> getKeys(){
        return keys;
    }
    bool getIsLeaf(){
        return isLeaf;
    }
    void sort(int n){
        int min;
        for (int i = 0;i < n-1; i++) {
            min = i;
            for (int j = i+1; j < n; j++) {
                if (keys[j]->data < keys[min]->data) {
                    min = j;
                }
            }
            swap(keys[min], keys[i]);
        }
    }
    void notLeaf(){
        isLeaf = false;
    }

    void addKey(key<T>* newKey){
        keys.push_back(newKey);
        sort(keys.size());
    }
    /**
     * An alternative is to create two different nodes (Internal and Leaf) that inherite from Node 
     * an implement this function
     */
    //virtual bool isLeaf() = 0;

//friend class BTree;
};

#endif