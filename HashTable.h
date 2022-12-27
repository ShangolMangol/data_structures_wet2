//
// Created by idota on 27/12/2022.
//

#ifndef WET2_HASHTABLE_H

#define WET2_HASHTABLE_H

#include "AVLTree.h"

template<class T, class Compare>
class HashTable
{
public:
    AVLTree<T, Compare>* array;
    int size;
    int numOfElements;

    HashTable() : array(new AVLTree<T, Compare>[30]()), size(30), numOfElements(0)
    {
//        for (int i = 0; i < size; ++i) {
//            array[i] = nullptr;
//        }
    }

    ~HashTable()
    {
        delete[] array;
    }

    void insert(T data)
    {
        int index = data->playerId % size;
        array[index].root = array[index].insert(array[index].root, data);
        numOfElements++;
        double factor = double(numOfElements)/size;
        if(factor >= 1.0)
            rehashAndIncrease();
    }

    T find(int id)
    {
        AVLNode<T>* node = array[id % size].findNode(array[id % size].root, id);
        if(node == nullptr)
            return nullptr;
        return node->data;
    }

    void rehashAndIncrease()
    {
        AVLTree<T, Compare>* newArray = new AVLTree<T, Compare>[size*2]();
        AVLTree<T, Compare>* tempArray = array;
        array = newArray;
        size = size*2;
        numOfElements = 0;

//        for (int i = 0; i < size*2; ++i)
//        {
//            newArray[i] = nullptr;
//        }


        for (int i = 0; i < size/2; ++i)
        {
            while(tempArray[i].root != nullptr)
            {

                this->insert(tempArray[i].root->data);
                tempArray[i].root = tempArray[i].deleteRoot();
            }
        }

//        for (int i = 0; i < size; ++i)
//        {
//            while(array[i].root != nullptr)
//            {
//                newArray[i].root = newArray[i].insert(newArray[i].root,array[i].root->data);
////                array[i].root = array[i].deleteNode(array[i].root, array[i].root->data);
//                array[i].root = array[i].deleteRoot();
//            }
//        }

        delete[] tempArray;
    }

};


#endif //WET2_HASHTABLE_H
