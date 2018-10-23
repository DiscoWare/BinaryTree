#ifndef DEKU_H
#define DEKU_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename T>
struct Leaf
{
    Leaf() {left_ = nullptr; right_ = nullptr; };
    Leaf(T value, Leaf* left = nullptr, Leaf* right = nullptr) : value_(value), left_(left), right_(right) {};
    ~Leaf() = default;

    T value_;
    Leaf* left_;
    Leaf* right_;
};

template<typename T>
class GreatDeku
{
public:
    GreatDeku() { size_ = 0; };
    GreatDeku(Leaf<T>* root, unsigned long long size) : root_(root), size_(size) {};

    void insert(const T& value);
    void erase(const T& value);
    T& find(T& value);
    Leaf<T>* getRoot() { return root_; };
    unsigned long long getSize() { return size_; };

    void printInOrder();
    void prettyPrint();
    void clear();
private:
    Leaf<T>* root_;
    unsigned long long size_;
};

template<typename T>
void printInOrder(Leaf<T>* current);

#endif

template<typename T>
Leaf<T>* findInsertionPoint(Leaf<T>*& current, const T& value)
{
    if (value < current->value_)
    {
        if (current->left_ == nullptr)
            return current;
        return findInsertionPoint(current->left_, value);
    }
    if (value > current->value_)
    {
        if (current->right_ == nullptr)
            return current;
        return findInsertionPoint(current->right_, value);
    }
}

template<typename T>
void GreatDeku<T>::insert(const T& value)
{
    Leaf<T> *newLeaf;
    newLeaf = new Leaf<T>(value);
    if (size_ == 0)
    {
        root_ = newLeaf;
        ++size_;
        return;
    }

    Leaf<T> *insertionPoint;
    insertionPoint = findInsertionPoint(root_, value);
    if (value < insertionPoint->value_)
    {
        insertionPoint->left_ = newLeaf;
        ++size_;
    }
    else if (value > insertionPoint->value_)
    {
        insertionPoint->right_ = newLeaf;
        ++size_;
    }
}

template<typename T>
Leaf<T>* findValue(Leaf<T>* current, const T& value)
{
    Leaf<T>* result;
    result = findPrevValue(current, value);
    if (result->left_->value_ == value)
        result = result->left_;
    else if (result->right_->value_ == value)
        result = result->right_;
    return result;
}

template<typename T>
Leaf<T>* findPrevValue(Leaf<T>* current, const T& value)
{
    if (current == nullptr)
        throw invalid_argument("Value not found");
    if (current->left_ != nullptr)
        if (current->left_->value_ == value)
            return current;
    if (current->right_ != nullptr)
        if (current->right_->value_ == value)
            return current;
    if (value < current->value_)
        return findPrevValue(current->left_, value);
    if (value > current->value_)
        return findPrevValue(current->right_, value);
}

template<typename T>
void eraseAndCopy(Leaf<T>* current, Leaf<T>* root, GreatDeku<T>& copyTo)
{
    if (current == nullptr)
        throw invalid_argument("Value not found");
    if (current->left_ != nullptr)
    {
        eraseAndCopy(current->left_, root, copyTo);
    }
    if (current->right_ != nullptr)
    {
        eraseAndCopy(current->right_, root, copyTo);
    }
    if (current->value_ != root->value_)
        copyTo.insert(current->value_);
    delete current;
}

template<typename T>
void GreatDeku<T>::erase(const T& value)
{
    Leaf<T>* eraseLeaf;
    Leaf<T>* prevLeaf;
    if (value == root_->value_)
    {
        GreatDeku<T> newTree;
        newTree.size_ = 0;
        eraseAndCopy(root_, root_, newTree);
        root_ = newTree.root_;
        size_ = newTree.size_;
    }
    else 
    {
        eraseLeaf = findValue(root_, value);
        prevLeaf = findPrevValue(root_, value);
        if (prevLeaf->left_ != nullptr)
            if (value == prevLeaf->left_->value_)
                prevLeaf->left_ = nullptr;
        if (prevLeaf->right_ != nullptr)
            if (value == prevLeaf->right_->value_)
                prevLeaf->right_ = nullptr;
        eraseAndCopy(eraseLeaf, eraseLeaf, *this);
    }
}

template<typename T>
void internalPrintInOrder(Leaf<T>*& current)
{
    if (current->left_ != nullptr)
        internalPrintInOrder(current->left_);
    cout << current->value_ << endl;
    if (current->right_ != nullptr)
        internalPrintInOrder(current->right_);
}

template<typename T>
void GreatDeku<T>::printInOrder()
{
    if (size_ > 0)
        internalPrintInOrder(root_);
}

template<typename T>
void GreatDeku<T>::prettyPrint()
{
    vector< vector< Leaf<T>* > > allRows;
    int rowCount = 0;
    vector< Leaf<T>* > currentRow = {root_};
    vector< Leaf<T>* > nextRow;
    bool done = false;
    while (!done)
    {
        done = true;
        for (auto v : currentRow)
        {
            if (v != nullptr)
            {
                if (v->left_ != nullptr)
                {
                    done = false;
                }
                nextRow.push_back(v->left_);
                if (v->right_ != nullptr)
                {
                    done = false;
                }
                nextRow.push_back(v->right_);
            }
        }

        allRows.push_back(currentRow);
        currentRow.erase(currentRow.begin(), currentRow.end());
        currentRow = nextRow;
        nextRow.erase(nextRow.begin(), nextRow.end());
        ++rowCount;
    }

    int currentRowCount = 1;
    for (auto v : allRows)
    {
        for (auto x : v)
        {
            for (int i = 0; i < rowCount / currentRowCount; ++i)
            {
                cout << " ";
            }
            if (x != nullptr)
                cout << x->value_ << " ";
            else 
                cout << " ";
        }
        cout << endl;
        ++currentRowCount;
    }
}

template<typename T>
void internalClear(Leaf<T>*& leaf)
{
    if (leaf->left_ != nullptr)
        internalClear(leaf->left_);
    if (leaf->right_ != nullptr)
        internalClear(leaf->right_);
    delete leaf;
}

template<typename T>
void GreatDeku<T>::clear()
{
    internalClear(root_);
    root_ = nullptr;
    size_ = 0;
}