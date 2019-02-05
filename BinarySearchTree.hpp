/*
 * Created by Anil Osman TUR
 * Binary Search Tree header interface file
 */
#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
#include <vector>
#include <stdlib.h>

class node
{
    unsigned int key;
    std::vector<std::string> values;
    node* left;
    node* right;

public:
    node(unsigned int key);
    node(unsigned int key, const std::string& data);
    void setLeft(node* ptr);
    node* getLeft();
    void setRight(node* ptr);
    node* getRight();
    void addData(const std::string& data);
    int removeData(const std::string& data);
    int isData(const std::string& data);
    std::vector<std::string> getValues() const;
    void clearValues();
    const unsigned int getKey();
    int size();

};

class BinarySearchTree
{
private:
    node *root;
    unsigned int treeSize;

    node* insertHelper(node* item, unsigned int key, const std::string& data);
    node* insertHelper(node* item, unsigned int key);
    node* removeHelper(node* item, unsigned int key, const std::string& data);
    node* removeHelper(node* item, unsigned int key);
    node* deleteNode(node* item, node* leaf);
    node* deleteMin(node* item);
    node* min(node* item);
    std::vector<std::string> find(node* item, unsigned int numberOfDigits) const;
    void printTree(node* item);

public:
    explicit BinarySearchTree(const std::string& inputFile);
    void insert(const std::string& data);
    void insert(unsigned int numberOfDigits);
    void remove(const std::string& data);
    void remove(unsigned int numberOfDigits);
    std::vector<std::string>find(unsigned int numberOfDigits) const;
    unsigned int size();
    void deleteMin();
    void printTree();

};

#endif // BINARYSEARCHTREE_HPP
