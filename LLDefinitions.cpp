#include "LL1.h"

Node::Node(string pData, int pNumber) {
    Right = nullptr;
    Left = nullptr;

    Data = pData;
    Number = pNumber;
}

Node::Node(const Node * OtherNode) {
    Right = nullptr;
    Left = nullptr;

    Data = OtherNode->Data;
    Number = OtherNode->Number;
}

LinkedList::~LinkedList() {
    Node * CurrentNode = Head;
    while (CurrentNode != nullptr) {
        Node * TemporaryNode = CurrentNode;
        CurrentNode = CurrentNode->Right;

        delete TemporaryNode;
        TemporaryNode = nullptr;
    }
    //cout << "Deconstructor called! " << this << endl;
}

LinkedList::LinkedList(const LinkedList & List) {
    Node * CurrentNode = List.Head;
    Head = nullptr;
    Tail = nullptr;
    Size = 0;

    Right = nullptr;
    Left = nullptr;

    while (CurrentNode != nullptr) {
        *this += *CurrentNode;
        CurrentNode = CurrentNode->Right;
    }
}

void LinkedList::operator = (const LinkedList & List) { 
    this->Clear();
    Node * CurrentNode = List.Head;

    while (CurrentNode != nullptr) {
        *this += CurrentNode;
        CurrentNode = CurrentNode->Right;
    }
}

void LinkedList::operator += (const Node Value) {
    Node * NewNode = new Node(&Value);
    
    if (Head != nullptr) {
        NewNode->Left = Tail;
        Tail->Right = NewNode;
        Tail = NewNode;
    } else {
        Head = NewNode;
        Tail = NewNode;
    }
    Size++;
}

void LinkedList::operator += (const string Value) {
    Node * NewNode = new Node(); 
    NewNode->Data = Value;

    if (Head != nullptr) {
        NewNode->Left = Tail;
        Tail->Right = NewNode;
        Tail = NewNode;
    } else {
        Head = NewNode;
        Tail = NewNode;
    }
    Size++;
}

void LinkedList::operator += (const int Value) {
    Node * NewNode = new Node(); 
    NewNode->Number = Value;

    if (Head != nullptr) {
        NewNode->Left = Tail;
        Tail->Right = NewNode;
        Tail = NewNode;
    } else {
        Head = NewNode;
        Tail = NewNode;
    }
    Size++;
}

LinkedList LinkedList::operator + (const LinkedList & List) {
    LinkedList NewList = *this;
    Node * CurrentNode = List.Head;

    while (CurrentNode != nullptr) {
        NewList += *CurrentNode;
        CurrentNode = CurrentNode->Right;
    }

    return NewList;
}

bool LinkedList::operator > (const LinkedList & List) {
    return Size > List.Size;
}

bool LinkedList::operator == (const LinkedList & List) {
    return Size == List.Size;
}

bool LinkedList::operator != (const LinkedList & List) {
    return Size != List.Size;
}

ostream & operator << (ostream & Output, const LinkedList & List) {
    Node * CurrentNode = List.Head;

    while (CurrentNode != nullptr) {
        Output << CurrentNode->Data << " " << CurrentNode->Number << ",  ";
        CurrentNode = CurrentNode->Right;
    }
    Output << endl;
    return Output;
}

void LinkedList::ReversePrint(ostream & Output) {
    Node * CurrentNode = Tail;
     
    while (CurrentNode != nullptr) {
        Output << CurrentNode->Data << " " << CurrentNode->Number << ",  ";
        CurrentNode = CurrentNode->Left;
    }
    Output << endl;
}

void LinkedList::operator -= (const string Value) {
    Node * CurrentNode = Head;
    Node * LeftNode = nullptr;
    Node * RightNode = nullptr;
    
    while (CurrentNode != nullptr) {
        if (CurrentNode->Data == Value) {
            if (CurrentNode != Head && CurrentNode != Tail) {
                LeftNode = CurrentNode->Left;
                RightNode = CurrentNode->Right;

                LeftNode->Right = RightNode;
                RightNode->Left = LeftNode;
            } else {
                if (CurrentNode == Head) {
                    RightNode = CurrentNode->Right;
                    RightNode->Left = nullptr;

                    Head = RightNode;
                    if (Tail == Head) {
                        Tail = Head;
                    }
                } else if (CurrentNode == Tail) {
                    LeftNode = CurrentNode->Left;
                    LeftNode->Right = nullptr;

                    Tail = LeftNode;
                }
            }
            delete CurrentNode;
            CurrentNode = nullptr;

            Size--;
            return;
        }
        CurrentNode = CurrentNode->Right;
    }
    cout << "Node not found" << endl;
}

void LinkedList::operator *= (const int Value) {
    Node * CurrentNode = Head;

    while (CurrentNode != nullptr) {
        CurrentNode->Number *= Value;

        CurrentNode = CurrentNode->Right;
    }

}

void LinkedList::AddNodeAtPosition(const Node Value, const int Position) {
    Node * NewNode = new Node(&Value);
    Node * CurrentNode = Head;
    Node * LeftNode = nullptr;

    if (Position > Size || Position < 1) {
        cout << "Cannot add. Position " << Position << " is invalid." << endl;
        return;
    }

    for (int i = 1; i <= Position; i++) {
        if (i == Position) {
            if (CurrentNode != Head) {
                LeftNode = CurrentNode->Left;

                LeftNode->Right = NewNode;
                NewNode->Right = CurrentNode;

                NewNode->Left = LeftNode;
                CurrentNode->Left = NewNode;
            } else {
                NewNode->Right = CurrentNode;
                NewNode->Left = nullptr;
                CurrentNode->Left = NewNode;

                Head = NewNode;
                if (Tail == Head) {
                    Tail = Head;
                }
            }
            Size++;
            return;
        }
        CurrentNode = CurrentNode->Right;
    }
}

void LinkedList::AddNodeAtRow(const Node Value, const int Col) {
    Node * CurrentNode = Head;

    for (int i = 1; i <= Col; i++) {
        if (CurrentNode == nullptr) {
            if (i < Col) {
                *this += Node();
            } else {
                *this += Value;
            }
            CurrentNode = Head;
            for (int j = 1; j <= i; j++) {
                CurrentNode = CurrentNode->Right;
            }
            continue;
        }

        CurrentNode = CurrentNode->Right;
    }
}

void LinkedList::Sort() {
    Node * CurrentNode = Head;
    Node * CurrentNode2 = Head;
    Node * RightNode = nullptr;
    Node * Right2Node = nullptr;
    Node * LeftNode = nullptr;

    while (CurrentNode != nullptr) {
        while (CurrentNode2->Right != nullptr) {
            if (CurrentNode2->Number > CurrentNode2->Right->Number) {
                if (CurrentNode2 != Head) {
                    RightNode = CurrentNode2->Right; 
                    Right2Node = RightNode->Right;
                    LeftNode = CurrentNode2->Left;
        
                    LeftNode->Right = RightNode;
                    RightNode->Right = CurrentNode2;
                    CurrentNode2->Right = Right2Node;

                    RightNode->Left = LeftNode;
                    CurrentNode2->Left = RightNode;

                    if (Right2Node != nullptr) {
                        Right2Node->Left = CurrentNode2;
                    } else {
                        Tail = CurrentNode2;
                    }

                } else {
                    RightNode = CurrentNode2->Right;
                    Right2Node = RightNode->Right;
                    LeftNode = CurrentNode2->Left;
                    Head = RightNode;

                    CurrentNode2->Right = Right2Node;
                    RightNode->Right = CurrentNode2;

                    RightNode->Left = nullptr;
                    CurrentNode2->Left = RightNode;
                    Right2Node->Left = CurrentNode2;
                }
                CurrentNode2 = Head;
                continue;
            }
            CurrentNode2 = CurrentNode2->Right;
        }
        
        CurrentNode2 = Head;
        CurrentNode = CurrentNode->Right;
    }
}

void LinkedList::Clear() {
    Node * CurrentNode = Head;

    while (CurrentNode != nullptr) {
        Node * TemporaryNode = CurrentNode;
        CurrentNode = CurrentNode->Right;

        delete TemporaryNode;
        TemporaryNode = nullptr;
    }

    Head = nullptr;
    Tail = nullptr;
    Size = 0;
}

LinkedMatrix::~LinkedMatrix() {
    if (Allocated == false) {
        return;
    }

    //cout << "Deconstructor called for Matrix!" << endl;
    LinkedList * CurrentLL = Head;

    while (CurrentLL != nullptr) {
        LinkedList * TemporaryLL = CurrentLL;
        CurrentLL = CurrentLL->Right;

        delete TemporaryLL;
        TemporaryLL = nullptr;
    }
    //cout << "Deconstructor for Matrix has ended!" << endl << endl;
}

void LinkedMatrix::operator += (LinkedList & List) {
    LinkedList * CurrentLL = Head;

    if (Head != nullptr) {
        List.Left = Tail;
        Tail->Right = &List;
        Tail = &List;
    } else {
        Head = &List;
        Tail = Head;
    }

    Size++;
}

LinkedMatrix LinkedMatrix::operator * (LinkedMatrix & Matrix) {
    LinkedMatrix NewMatrix = LinkedMatrix();
    NewMatrix.Allocated = true;

    LinkedMatrix RHSMatrix = Matrix.Transpose();

    LinkedList * LHSCurrentLL = Head; 
    LinkedList * RHSCurrentLL = RHSMatrix.Head;

    Node * LHSCurrentNode = LHSCurrentLL->GetHead();
    Node * RHSCurrentNode = RHSCurrentLL->GetHead();

    for (int i = 0; i < Size; i++) {
        LinkedList * NewList = new LinkedList();
        NewMatrix += *NewList;
    }

    LinkedList * NewCurrentLL = NewMatrix.Head;
    Node * NewCurrentNode = NewCurrentLL->GetHead();

    int Sum = 0;
    
    while (LHSCurrentLL != nullptr) {
        while (RHSCurrentLL != nullptr) {
            RHSCurrentNode = RHSCurrentLL->GetHead();
            while (LHSCurrentNode != nullptr) {
                Sum += RHSCurrentNode->Number * LHSCurrentNode->Number;

                RHSCurrentNode = RHSCurrentNode->Right;
                LHSCurrentNode = LHSCurrentNode->Right;
            }
            *NewCurrentLL += Sum;
            Sum = 0;

            LHSCurrentNode = LHSCurrentLL->GetHead();
            RHSCurrentLL = RHSCurrentLL->Right;
        }
        NewCurrentLL = NewCurrentLL->Right;
        LHSCurrentLL = LHSCurrentLL->Right;
        if (LHSCurrentLL != nullptr) {
            LHSCurrentNode = LHSCurrentLL->GetHead();
        }

        RHSCurrentLL = RHSMatrix.Head;
        if (RHSCurrentLL != nullptr) {
            RHSCurrentNode = RHSCurrentLL->GetHead();
        }
    }

    return NewMatrix;
}

LinkedMatrix LinkedMatrix:: operator + (LinkedMatrix & Matrix) {
    LinkedMatrix NewMatrix = LinkedMatrix();
    NewMatrix.Allocated = true;

    LinkedList * LHSCurrentLL = Head;
    LinkedList * RHSCurrentLL = Matrix.Head;

    Node * LHSCurrentNode = LHSCurrentLL->GetHead();
    Node * RHSCurrentNode = RHSCurrentLL->GetHead();

    for (int i = 0; i < Size; i++) {
        LinkedList * NewList = new LinkedList();
        NewMatrix += *NewList;
    }

    LinkedList * NewCurrentLL = NewMatrix.Head;

    while (LHSCurrentLL != nullptr) {
        while (LHSCurrentNode != nullptr) {
            *NewCurrentLL += LHSCurrentNode->Number + RHSCurrentNode->Number;
            
            LHSCurrentNode = LHSCurrentNode->Right;
            RHSCurrentNode = RHSCurrentNode->Right;
        }

        NewCurrentLL = NewCurrentLL->Right;
        LHSCurrentLL = LHSCurrentLL->Right;
        if (LHSCurrentLL != nullptr) {
            LHSCurrentNode = LHSCurrentLL->GetHead();
        }

        RHSCurrentLL = RHSCurrentLL->Right;
        if (RHSCurrentLL != nullptr) {
            RHSCurrentNode = RHSCurrentLL->GetHead();
        }
    }

    return NewMatrix;
}

ostream & operator << (ostream & Output, LinkedMatrix & Matrix) {
    LinkedList * CurrentLL = Matrix.Head;

    while (CurrentLL != nullptr) {
        Output << CurrentLL << endl << *CurrentLL << endl;
        CurrentLL = CurrentLL->Right;
    }

    return Output;
}

LinkedMatrix LinkedMatrix::Transpose() {
    LinkedMatrix NewMatrix = LinkedMatrix();
    NewMatrix.Allocated = true;

    LinkedList * CurrentLL = Head;
    Node * CurrentNode = nullptr;

    for (int i = 0; i < CurrentLL->GetSize(); i++) {
        LinkedList * NewList = new LinkedList();
        NewMatrix += *NewList;
    }

    LinkedList * NewCurrentLL = nullptr;

    while (CurrentLL != nullptr) {
        CurrentNode = CurrentLL->GetHead();
        NewCurrentLL = NewMatrix.Head;

        while (CurrentNode != nullptr) {
            *NewCurrentLL += *CurrentNode;

            NewCurrentLL = NewCurrentLL->Right;
            CurrentNode = CurrentNode->Right;
        }

        CurrentLL = CurrentLL->Right;
    }

    return NewMatrix;
}

void LinkedMatrix::AddNodeAtRowCol(const Node Value, const int Row, const int Col) {
    LinkedList * CurrentLL = Head;

    for (int i = 1; i <= Row; i++) {
        if (i == Row) {
            CurrentLL->AddNodeAtRow(Value, Col);
            return;
        }
        
        CurrentLL = CurrentLL->Right;
    }
}

void LinkedMatrix::Fill(const int Columns) {
    LinkedList * CurrentLL = Head;
    Node * CurrentNode = CurrentLL->GetHead();

    while (CurrentLL != nullptr) {
        for (int i = 0; i < Columns; i++) {
            if (CurrentNode == nullptr) {
                *CurrentLL += Node("", 0);
                continue;
            }
            CurrentNode = CurrentNode->Right;
        }

        CurrentLL = CurrentLL->Right;
        if (CurrentLL != nullptr) {
            CurrentNode = CurrentLL->GetHead();
        }
    }
}

void LinkedMatrix::ReversePrint(ostream & Output) {
    LinkedList * CurrentLL = Tail;

    while (CurrentLL != nullptr) {
        Output << CurrentLL << endl << *CurrentLL << endl;
        CurrentLL = CurrentLL->Left;
    }
}