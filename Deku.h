#ifndef DEKU_H
#define DEKU_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename KEY, typename VALUE>
struct Leaf
{
    Leaf() {left_ = nullptr; right_ = nullptr; };
    Leaf(const KEY& key, const VALUE& value, Leaf* left = nullptr, Leaf* right = nullptr, Leaf* up = nullptr) 
        : key_(key), value_(value), left_(left), right_(right), up_(up) {};
    ~Leaf() = default;

    KEY key_;
    VALUE value_;
    Leaf* left_;
    Leaf* right_;
    Leaf* up_;
};

template<typename KEY, typename VALUE>
class GreatDeku
{
public:
    GreatDeku() { size_ = 0; };
    GreatDeku(Leaf<KEY, VALUE>* root, unsigned long long size) : root_(root), size_(size) {};

    void insert(const KEY& key, const VALUE& value);
    void erase(const KEY& key);

    Leaf<KEY, VALUE>* find(const KEY& key);
    Leaf<KEY, VALUE>* getRoot() { return root_; };
    unsigned long long getSize() { return size_; };

    void printInOrder();
    void prettyPrint();
    void clear();
private:
    Leaf<KEY, VALUE>* root_;
    unsigned long long size_;

    void printInOrder(Leaf<KEY, VALUE>* current);
    void erase(Leaf<KEY, VALUE>* deleteMe);
};

#endif

template<typename KEY, typename VALUE>
void GreatDeku<KEY, VALUE>::insert(const KEY& key, const VALUE& value)
{
    Leaf<KEY, VALUE>* newLeaf = new Leaf<KEY, VALUE>(key, value);
    if (size_ == 0)
        root_ = newLeaf;
    Leaf<KEY, VALUE>* current = root_;
    while (current->key_ != key)
    {
        if (key < current->key_)
        {
            if (current->left_ == nullptr)
            {
                current->left_ = newLeaf;
                current->left_->up_ = current;
            }
            current = current->left_;
        }
        else
        {
            if (current->right_ == nullptr)
            {
                current->right_ = newLeaf;
                current->right_->up_ = current;
            }
            current = current->right_;    
        }
    }
    current->value_ = value;
    ++size_;
}

template<typename KEY, typename VALUE>
Leaf<KEY, VALUE>* GreatDeku<KEY, VALUE>::find(const KEY& key)
{
    Leaf<KEY, VALUE>* current = root_;
    while (current != nullptr)
    {
        if (current->key_ == key)
            return current;
        else if (key < current->key_)
            current = current->left_;
        else 
            current = current->right_;
    }
    return nullptr;
}

template<typename KEY, typename VALUE>
Leaf<KEY, VALUE>* getLeftMost(Leaf<KEY, VALUE>* current)
{
    while (current->left_ != nullptr)
        current = current->left_;
    return current;
}

template<typename KEY, typename VALUE>
void GreatDeku<KEY, VALUE>::erase(const KEY& key)
{
    Leaf<KEY, VALUE>* deleteMe = find(key);
    erase(deleteMe);
    --size_;
}

template<typename KEY, typename VALUE>
void GreatDeku<KEY, VALUE>::erase(Leaf<KEY, VALUE>* deleteMe)
{
    if (deleteMe->left_ != nullptr && deleteMe->right_ != nullptr)
    {
        Leaf<KEY, VALUE>* leftMost = getLeftMost(deleteMe->right_);
        deleteMe->value_ = leftMost->value_;
        deleteMe->key_ = leftMost->key_;
        erase(leftMost);
    }
    else if (deleteMe->left_ != nullptr || deleteMe->right_ != nullptr)
    {
        if (deleteMe->left_ != nullptr)
        {
            if (deleteMe->up_)
            {
                if (deleteMe->up_->left_ == deleteMe)
                    deleteMe->up_->left_ = deleteMe->left_;
                else
                    deleteMe->up_->right_ = deleteMe->left_;
            }
            else
                root_ = deleteMe->left_;
            deleteMe->left_->up_ = deleteMe->up_;
        }
        else
        {
            if (deleteMe->up_)
            {
                cout << "HI\n";
                if (deleteMe->up_->right_ == deleteMe)
                    deleteMe->up_->right_ = deleteMe->right_;
                else
                    deleteMe->up_->left_ = deleteMe->right_;
            }
            else
                root_ = deleteMe->right_;
            deleteMe->right_->up_ = deleteMe->up_;
        }
        delete deleteMe;
    }
    else
    {   
        if (deleteMe->up_)
        {
            if (deleteMe->up_->left_ == deleteMe)
                deleteMe->up_->left_ = nullptr;
            else 
                deleteMe->up_->right_ = nullptr;
        }
        delete deleteMe;
    }
}

template<typename KEY, typename VALUE>
void GreatDeku<KEY, VALUE>::printInOrder(Leaf<KEY, VALUE>* current)
{
    if (current->left_)
        printInOrder(current->left_);
    cout << current->key_ << ": " << current->value_ << endl;
    if (current->right_)
        printInOrder(current->right_);
}

template<typename KEY, typename VALUE>
void GreatDeku<KEY, VALUE>::printInOrder()
{
    if (size_)
        printInOrder(root_);
}

// template<typename T>
// Leaf<T>* findValue(Leaf<T>* current, const T& value)
// {
//     Leaf<T>* result;
//     result = findPrevValue(current, value);
//     if (result->left_->value_ == value)
//         result = result->left_;
//     else if (result->right_->value_ == value)
//         result = result->right_;
//     return result;
// }

// template<typename T>
// Leaf<T>* findPrevValue(Leaf<T>* current, const T& value)
// {
//     if (current == nullptr)
//         throw invalid_argument("Value not found");
//     if (current->left_ != nullptr)
//         if (current->left_->value_ == value)
//             return current;
//     if (current->right_ != nullptr)
//         if (current->right_->value_ == value)
//             return current;
//     if (value < current->value_)
//         return findPrevValue(current->left_, value);
//     if (value > current->value_)
//         return findPrevValue(current->right_, value);
// }

// template<typename T>
// void eraseAndCopy(Leaf<T>* current, Leaf<T>* root, GreatDeku<T>& copyTo)
// {
//     if (current == nullptr)
//         throw invalid_argument("Value not found");
//     if (current->left_ != nullptr)
//     {
//         eraseAndCopy(current->left_, root, copyTo);
//     }
//     if (current->right_ != nullptr)
//     {
//         eraseAndCopy(current->right_, root, copyTo);
//     }
//     if (current->value_ != root->value_)
//         copyTo.insert(current->value_);
//     delete current;
// }

// template<typename T>
// void GreatDeku<T>::erase(const T& value)
// {
//     Leaf<T>* eraseLeaf;
//     Leaf<T>* prevLeaf;
//     if (value == root_->value_)
//     {
//         GreatDeku<T> newTree;
//         newTree.size_ = 0;
//         eraseAndCopy(root_, root_, newTree);
//         root_ = newTree.root_;
//         size_ = newTree.size_;
//     }
//     else 
//     {
//         eraseLeaf = findValue(root_, value);
//         prevLeaf = findPrevValue(root_, value);
//         if (prevLeaf->left_ != nullptr)
//             if (value == prevLeaf->left_->value_)
//                 prevLeaf->left_ = nullptr;
//         if (prevLeaf->right_ != nullptr)
//             if (value == prevLeaf->right_->value_)
//                 prevLeaf->right_ = nullptr;
//         eraseAndCopy(eraseLeaf, eraseLeaf, *this);
//     }
// }

// template<typename T>
// void internalPrintInOrder(Leaf<T>*& current)
// {
//     if (current->left_ != nullptr)
//         internalPrintInOrder(current->left_);
//     cout << current->value_ << endl;
//     if (current->right_ != nullptr)
//         internalPrintInOrder(current->right_);
// }

// template<typename T>
// void GreatDeku<T>::printInOrder()
// {
//     if (size_ > 0)
//         internalPrintInOrder(root_);
// }

// template<typename T>
// void GreatDeku<T>::prettyPrint()
// {
//     vector< vector< Leaf<T>* > > allRows;
//     int rowCount = 0;
//     vector< Leaf<T>* > currentRow = {root_};
//     vector< Leaf<T>* > nextRow;
//     bool done = false;
//     while (!done)
//     {
//         done = true;
//         for (auto v : currentRow)
//         {
//             if (v != nullptr)
//             {
//                 if (v->left_ != nullptr)
//                 {
//                     done = false;
//                 }
//                 nextRow.push_back(v->left_);
//                 if (v->right_ != nullptr)
//                 {
//                     done = false;
//                 }
//                 nextRow.push_back(v->right_);
//             }
//         }

//         allRows.push_back(currentRow);
//         currentRow.erase(currentRow.begin(), currentRow.end());
//         currentRow = nextRow;
//         nextRow.erase(nextRow.begin(), nextRow.end());
//         ++rowCount;
//     }

//     int currentRowCount = 1;
//     for (auto v : allRows)
//     {
//         for (auto x : v)
//         {
//             for (int i = 0; i < rowCount / currentRowCount; ++i)
//             {
//                 cout << " ";
//             }
//             if (x != nullptr)
//                 cout << x->value_ << " ";
//             else 
//                 cout << " ";
//         }
//         cout << endl;
//         ++currentRowCount;
//     }
// }

// template<typename T>
// void internalClear(Leaf<T>*& leaf)
// {
//     if (leaf->left_ != nullptr)
//         internalClear(leaf->left_);
//     if (leaf->right_ != nullptr)
//         internalClear(leaf->right_);
//     delete leaf;
// }

// template<typename T>
// void GreatDeku<T>::clear()
// {
//     internalClear(root_);
//     root_ = nullptr;
//     size_ = 0;
// }