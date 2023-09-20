/**
* @author Valentijn van Overveld
*/

#ifndef NODE_H
#define NODE_H
#include <iostream>

template<typename T>
class Node
{
    public:
        Node *leftPtr = nullptr;
        Node *rightPtr = nullptr;
        T payload;

        Node(){}
        Node(T obj){payload = obj;}
        friend std::ostream& operator<<(std::ostream& o, const Node& n){o << n.payload; return o;}
        bool operator<(const Node& n){return payload < n.payload;}
        bool operator>(const Node& n){return payload > n.payload;}
        virtual ~Node(){}
};

#endif // NODE_H
