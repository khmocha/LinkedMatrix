#ifndef LL1_H
#define LL1_H

#include <iostream>
#include <string>

using namespace std;

struct Node {
    Node * Right;
    Node * Left;
    string Data;
    int Number;

    Node() : Right(nullptr), Left(nullptr), Data(""), Number(0) {};
    Node(string pData, int pNumber);
    ~Node() {};
    Node(const Node * OtherNode);
};

class LinkedList {
    private:
        Node * Head;
        Node * Tail;
        int Size;
    public:
        LinkedList() : Head(nullptr), Tail(nullptr), Size(0) {};
        ~LinkedList();
        LinkedList(const LinkedList & List);

        void operator = (const LinkedList & List);
        void operator += (const Node Value);
        void operator += (const string Value);
        void operator += (const int Value);
        void operator -= (const string Value);
        LinkedList operator + (const LinkedList & List);
        bool operator > (const LinkedList & List);
        
        friend ostream & operator << (ostream & Output, const LinkedList & List);
        
        void ReversePrint(ostream & Output);
        void AddNodeAtPosition(const Node Value, const int Position);
        void Sort();
        void Clear();

        Node * GetHead() {return Head;};
        Node * GetTail() {return Tail;};
        int GetSize() {return Size;};
};  

#endif
