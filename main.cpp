#include <iostream>

#include "btree.h"

using namespace std;

int main(int argc, char *argv[]) {
    BTree<int> btree(4);
    btree.insert(3);
    btree.print();
    btree.insert(4);
    btree.print();
    btree.insert(5);
    btree.print();
    btree.insert(6);
    btree.print();
    btree.insert(1);
    btree.print();
    btree.insert(2);
    btree.print();
    return EXIT_SUCCESS;
}