/**
* @author Valentijn van Overveld
*/

#ifndef BINTREE_H
#define BINTREE_H
#include "Node.h"
#include <iostream>
#include <string>

template<typename T>
class BinTree
{
    public:
        Node<T> *root = nullptr;

        BinTree(){}
        BinTree(T obj) {Node<T> n(obj); root = &n;}

        /**
        *
        *
        */
        Node<T>* Insert(T obj, Node<T> *curNode){
            if(curNode == nullptr)
                return new Node<T>(obj);
            if(obj < curNode->payload)
                curNode->leftPtr = Insert(obj, curNode->leftPtr);
            else if(obj > curNode->payload)
                curNode->rightPtr = Insert(obj, curNode->rightPtr);
            return curNode;
        }

        Node<T>* Search(T obj, Node<T> *curNode){
            Node<T> *n;
            if(!curNode){
                return nullptr;
            } else if(curNode->payload == obj){
                return curNode;
            } else if(obj < curNode->payload){
                n = Search(obj, curNode->leftPtr);
            } else {
                n = Search(obj, curNode->rightPtr);
            }
            return n;
        }

        Node<T>* findMin(Node<T> *curNode){
            if(curNode && curNode->leftPtr != nullptr){
                curNode = curNode->leftPtr;
            }
            return curNode;
        }

        Node<T>* Delete(T obj, Node<T> *curNode){
            if(curNode == nullptr){
                return curNode;
            } else if(obj < curNode->payload){
                curNode->leftPtr = Delete(obj, curNode->leftPtr);
            } else if(obj > curNode->payload){
                curNode->rightPtr = Delete(obj, curNode->rightPtr);
            } else {
                std::cout << "RECORD DELETED" << std::endl << *curNode << std::endl << std::endl;
                if(curNode->leftPtr == nullptr && curNode->rightPtr == nullptr){
                    return nullptr;
                } else if(curNode->leftPtr == nullptr){
                    return curNode->rightPtr;
                } else if(curNode->rightPtr == nullptr){
                    return curNode->leftPtr;
                }
                Node<T> *tempRight = curNode->rightPtr;
                Node<T> *temp = findMin(tempRight);
                curNode->payload = temp->payload;
                curNode->rightPtr = Delete(obj, curNode->rightPtr);
            }
            return curNode;
        }

        virtual ~BinTree() {}

    protected:

    private:
};

#endif // BINTREE_H
