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
        LinkedList * Right;
        LinkedList * Left;

        LinkedList() : Head(nullptr), Tail(nullptr), Size(0), Right(nullptr), Left(nullptr) {};
        ~LinkedList();
        LinkedList(const LinkedList & List);

        void operator = (const LinkedList & List);
        void operator += (const Node Value);
        void operator += (const string Value);
        void operator += (const int Value);
        void operator -= (const string Value);
        void operator *= (const int Value);
        LinkedList operator + (const LinkedList & List);
        bool operator > (const LinkedList & List);
        bool operator == (const LinkedList & List);
        bool operator != (const LinkedList & List);
        
        friend ostream & operator << (ostream & Output, const LinkedList & List);
        
        void ReversePrint(ostream & Output);
        void AddNodeAtPosition(const Node Value, const int Position);
        void AddNodeAtRow(const Node Value, const int Col);
        void Sort();
        void Clear();

        Node * GetHead() {return Head;};
        Node * GetTail() {return Tail;};
        int GetSize() {return Size;};
};  

class LinkedMatrix {
    private:
        LinkedList * Head;
        LinkedList * Tail;
        int Size;
        bool Allocated;

    public:
        LinkedMatrix() : Head(nullptr), Tail(nullptr), Size(0), Allocated(false) {};
        ~LinkedMatrix();

        void operator += (LinkedList & List);
        LinkedMatrix operator * (LinkedMatrix & Matrix);
        LinkedMatrix operator + (LinkedMatrix & Matrix);

        friend ostream & operator << (ostream & Output, LinkedMatrix & Matrix);

        LinkedMatrix Transpose();
        void AddNodeAtRowCol(const Node Value, const int Row, const int Col);
        void Fill(const int Columns);
        void ReversePrint(ostream & Output); 

        LinkedList & GetHead() {return *Head;};
        LinkedList & GetTail() {return *Tail;};
        int GetSize() {return Size;};
};

#endif
