#ifndef BTREE_H
#define BTREE_H

#include "node.h"
template <typename T>
class BTree {
    public:
        node<T>* root;
        vector<node<T>*> nodes;
        unsigned int degree;

        BTree(unsigned int degree) : degree(degree), root(nullptr) {};

        T search(T data) {
            cout << "searching " << data << endl;
            bool found = root->findKey(data); 
            if(found) return data;
            else return 0;
        }

        key<T>* findFatherKey(node<T>* node1){
            for(int i = 0; i < nodes.size(); i++){
                for(int j = 0; j < nodes[i]->keys.size(); j++){
                    if(nodes[i]->keys[j]->left == node1 || nodes[i]->keys[j]->right == node1){
                        return nodes[i]->keys[j];
                    }
                }
            }
            cout << "returning null" << endl;
            return nullptr;
        }

        node<T>* locateNode(T data){
            cout << data << endl;
            node<T>* current = root;
            vector<key<T>*> currentKeys = current->keys;
            cout << "finding node where data will be inserted" << endl;    
            while(!current->isLeaf){
                cout << current->isLeaf << endl;
                for(int i = 0; i < currentKeys.size();i++){
                    if(currentKeys[i]->data == data) return current;
                    if (data > currentKeys[i]->data){
                        cout << "data higher than current" << endl;
                        if(data < (currentKeys[i+1]->data)){ 
                            if(currentKeys[i]->right){
                                current = currentKeys[i]->right;
                            }
                        }
                    }
                    else if(data < currentKeys[i]->data) {
                        cout << data << " is less than " << currentKeys[i]->data << endl;
                        if(currentKeys[i]->left){
                            cout << currentKeys[i]->left->isLeaf << endl;
                            current = currentKeys[i]->left;
                            cout << "current isLeaf = " << current->isLeaf << endl;
                        }
                    }
                }
            }
            return current;
        }

        void split(node<T>* leaf){
            cout << "splitting" << endl;
            node<T>* newNode1 = new node<T>(degree);
            node<T>* newNode2 = new node<T>(degree);
            key<T>* fatherKey = findFatherKey(leaf);
            node<T>* father;
            if(fatherKey == nullptr) father = nullptr;
            else father = locateNode(fatherKey->data);
            int length = leaf->keys.size();
            int middle = length/2;
            key<T>*midKey = leaf->keys[middle];
            cout << "midkey is " << midKey->data << endl;
            for (int i = 0; i < middle; i++){
                newNode1->addKey(leaf->keys[i]);
            }
            for(int i = middle + 1; i < length; i++){
                newNode2->addKey(leaf->keys[i]);
            }
            midKey->left = newNode1;
            midKey->right = newNode2;
            
            if(father == nullptr){
                cout << "father is null" << endl;
                node<T>* newRoot = new node<T>(degree);
                newRoot->addKey(midKey);
                root = newRoot;
                root->notLeaf();
                nodes.push_back(newRoot);
                return;
            }
            else {
                father->addKey(midKey);
                bool isLeft = (fatherKey->left == leaf) ? true : false;
                if(isLeft) fatherKey->left = newNode2;
                else fatherKey->right = newNode1; 
                nodes.push_back(newNode1);
                nodes.push_back(newNode2);
                if(father->keys.size() >= degree) split(father);
            }
        }

        bool insert(T data) {
            cout << "inserting " << data << endl;
            key<T>* newKey = new key<T>(data);
            if(!root){ 
                cout << "no root" << endl;
                node<T>* newRoot = new node<T>(degree);
                newRoot->addKey(newKey);
                root = newRoot;
                nodes.push_back(newRoot);
                cout << "added " << newKey->data << "as root" << endl;
                return true;
            }
            if(root->findKey(data)) return false;
            else{
                cout << "adding " << data << endl;
                node<T>* leaf = locateNode(data);
                leaf->addKey(newKey);
                cout << "degree " << degree << " node keys " << leaf->keys.size() << endl;
                if(leaf->keys.size() >= degree) split(leaf);
                cout << "finished inseting" << endl;
                return true;
            }
            return false;
        }

        bool remove(int k) {

            return true;
        }

        void showNode(node<T>* node1){
            for(int i = 0; i < node1->keys.size(); i++){
                cout << node1->keys[i]->data << " ";;
            }
            cout << endl;
            for(int i = 0; i < node1->keys.size(); i++){
                if(node1->keys[i]->left) showNode(node1->keys[i]->left);
                if(i+1 == node1->keys.size() && node1->keys[i]->right) showNode(node1->keys[i]->right);
            }
        }

        void print() {
            showNode(root);
        }

        //~BTree();
};

#endif