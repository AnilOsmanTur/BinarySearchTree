/*
 * Created by Anil Osman TUR
 * Binary Search Tree implementation file
 */
#include "BinarySearchTree.hpp"
#include <fstream>

using namespace std;

// node class definition
node::node(unsigned int key)
{
    this->key = key;
    left = NULL;
    right = NULL;
}

node::node(unsigned int key, const string& data)
{
    this->key = key;
    values.push_back(data);
    left = NULL;
    right = NULL;
}

void node::setLeft(node* ptr)
{
    left = ptr;
}

node* node::getLeft()
{
    return left;
}

void node::setRight(node* ptr)
{
    right = ptr;
}

node* node::getRight()
{
    return right;
}

void node::addData(const string& data)
{
    values.push_back(data);
}

int node::removeData(const string& data)
{
    if(values.empty()) return -1;
    for (auto i = values.cbegin(); i != values.cend(); i++){
        if( data.compare(*i) == 0 ){
            values.erase(i);
            return 1;
        }
    }
    return 0;
}

/*
 * returns 1 when the string is found
 * returns -1 when the vector is empty
 * returns 0 when the string couldn't found
 */
int node::isData(const std::string& data)
{
    if(values.empty()) return -1;
    for (auto i = values.cbegin(); i != values.cend(); i++){
        if( data.compare(*i) == 0 ){
            return 1;
        }
    }
    return 0;
}

vector<string> node::getValues() const
{
    return values;
}

void node::clearValues()
{
    values.clear();
    values.resize(0);
}

const unsigned int node::getKey()
{
    return key;
}

int node::size()
{
    return values.size();
}




// bst class functions definitions
BinarySearchTree::BinarySearchTree(const string& inputFile)
{
    root = NULL;
    treeSize = 0;
    ifstream infile(inputFile, ifstream::in);
    if(infile.is_open()){

        unsigned int i;
        do {
            string s;
            infile>>s;

            if(isdigit(s[0])){
                i = stoi(s);
                insert(i);
            }else if(s.size() > 0){
                insert(s);
            }

        }while(!infile.eof());

        infile.close();
        printTree();
    }else{
        cout<<"Can't open the file."<<endl;
    }
}

void BinarySearchTree::insert(const string& data)
{
    treeSize++;
    root = insertHelper(root, data.size(), data);
}

void BinarySearchTree::insert(unsigned int numberOfDigits)
{
    treeSize++;
    root = insertHelper(root, numberOfDigits);
}

void BinarySearchTree::remove(const string& data)
{
    treeSize--;
    root = removeHelper(root, data.size(), data);
}

void BinarySearchTree::remove(unsigned int numberOfDigits)
{
    treeSize--;
    root = removeHelper(root, numberOfDigits);
}

vector<string> BinarySearchTree::find(unsigned int numberOfDigits) const
{
    return find(root, numberOfDigits);
}

vector<string> BinarySearchTree::find(node* item, unsigned int numberOfDigits) const
{
    if( numberOfDigits < item->getKey() ){
        return find(item->getLeft(), numberOfDigits);
    }else if( numberOfDigits < item->getKey() ){
        return find(item->getRight(), numberOfDigits);
    }else{
        return item->getValues();
    }
}

// some helper functions
unsigned int BinarySearchTree::size()
{
    return this->treeSize;
}

// insertion process helper functions
node* BinarySearchTree::insertHelper(node* item, unsigned int key,const string& data)
{
    if (!item) {
        return new node(key, data);
    }
    if (key < item->getKey()) {
        item->setLeft(insertHelper(item->getLeft(), key, data));
    }else if (key > item->getKey()) {
        item->setRight(insertHelper(item->getRight(), key, data));
    }else {
        item->addData(data);
    }
    return item;
}

node* BinarySearchTree::insertHelper(node* item, unsigned int key)
{
    if (!item) {
        return new node(key);
    }
    if (key < item->getKey()) {
        item->setLeft(insertHelper(item->getLeft(), key));
    }else if (key > item->getKey()) {
        item->setRight(insertHelper(item->getRight(), key));
    }
    return item;
}

// deteletion process helper functions
node* BinarySearchTree::removeHelper(node* item, unsigned int key, const string& data)
{
    if(!item){
        return NULL;
    }
    if(key < item->getKey()){
        item->setLeft(removeHelper(item->getLeft(), key, data));
    }else if(key > item->getKey()){
        item->setRight(removeHelper(item->getRight(), key, data));
    }else{
        if( item->isData(data) ){
            item->removeData(data);
            if(!item->size()){
                // then the vector is empty
                item->clearValues();
                if (!item->getRight()){
                    return deleteNode(item, item->getLeft());
                }
                if (!item->getLeft()){
                    return deleteNode(item, item->getRight());
                }

                node* p = item;
                item = min(p->getRight());
                item->setRight(deleteMin(p->getRight()));
                item->setLeft(p->getLeft());
            }
        }

    }
    return item;
}
node* BinarySearchTree::deleteNode(node* item, node* leaf)
{
   node *ptr = item;
   item = leaf;
   delete ptr;
   return item;
}

void BinarySearchTree::deleteMin(){
    root = deleteMin(root);
}
node* BinarySearchTree::deleteMin(node* item){
    if(!item->getLeft()){
        return deleteNode(item, item->getRight());
    }
    item->setLeft(deleteMin(item->getLeft()));
    return item;
}

node* BinarySearchTree::min(node* item){
    if(!item->getLeft()){
        return item;
    }else{
        return min(item->getLeft());
    }
}

node* BinarySearchTree::removeHelper(node* item, unsigned int key)
{
    if(!item){
        return NULL;
    }
    if(key < item->getKey()){
        item->setLeft(removeHelper(item->getLeft(), key));
    }else if(key > item->getKey()){
        item->setRight(removeHelper(item->getRight(), key));
    }else{
        item->clearValues();
        if (!item->getRight()){
            return deleteNode(item, item->getLeft());
        }
        if (!item->getLeft()){
            return deleteNode(item, item->getRight());
        }

        node* p = item;
        item = min(p->getRight());
        item->setRight(deleteMin(p->getRight()));
        item->setLeft(p->getLeft());
    }
    return item;
}

void BinarySearchTree::printTree()
{
    cout<<"<";
    printTree(root);
    cout<<">"<<endl;
}

void BinarySearchTree::printTree(node* item)
{
    if(item){
        cout<<"(";
        printTree(item->getLeft());
        cout<< " " <<item->getKey()<< " ";
        printTree(item->getRight());
        cout<<")";
    }
}
