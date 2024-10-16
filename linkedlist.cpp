#include "linkedlist.h"
#include <iostream>
using namespace std;

//list functions

LinkedList::LinkedList() {
  this->head = nullptr;
}

void LinkedList::insert(int coef, int expo) {
    Node* newNode = new Node(coef, expo);
    Node* ptr = this->head;
    Node* prev = nullptr;

   // coefficient is 0
    if (newNode->coef == 0) {
      delete newNode;
      return;
    }

    // empty list, make newNode the head
    if (head == nullptr) {
        this->head = newNode;
        newNode->next = nullptr;
        return;
    }

    // insert at the head if newNode's expo is greater than the head's
    if (newNode->expo > head->expo) {
        newNode->next = this->head;
        this->head = newNode;
        return;
    }

    // traverse list
    while (ptr != nullptr) {
        // Case 3: If we find a node with the same expo, add the coefficients
        if (newNode->expo == ptr->expo) {
            ptr->coef += newNode->coef;
            delete newNode; // We no longer need the new node after adding
            return;
        }

        // insert in the middle
        if (ptr->expo > newNode->expo && (ptr->next == nullptr || ptr->next->expo < newNode->expo)) {
            newNode->next = ptr->next;
            ptr->next = newNode;
            return;
        }

        prev = ptr;
        ptr = ptr->next;
    }

    // insert at the end (if we reached the end of the list)
    prev->next = newNode;
    newNode->next = nullptr;
}


void LinkedList::print(ostream& os) const{
    Node* ptr = this->head;

    if (this->head == nullptr) {
        os<<"Empty Linked List"<<endl;
    }

    else {
        while (ptr != nullptr) { // checks sign of coefficient before printing

            if (ptr->expo == 0 && ptr->coef < 0) {
                cout << ptr->coef;
            }

            else if (ptr->expo == 0 && ptr->coef > 0) {
                cout << "+" << ptr->coef << "x^" << ptr->expo;
            }

            else if (ptr->coef < 0) {
                cout << ptr->coef << "x^" << ptr->expo;
            } //endif

            else if (ptr->coef > 0) {
                os << '+' << ptr->coef << "x^" << ptr->expo;
            }
            ptr = ptr->next; // go to next term
        }//endwhile
        cout << endl;
    }//endelse

} //endfunc

void LinkedList::removeAll() {
    while (head != NULL) {
        Node* temp = head;
        delete head;
        head = temp->next;
    } //endwhile
} //endfunc

bool LinkedList::operator==(const LinkedList &other) {
    Node* temp = head;
    Node* temp2 = other.head;
    while (temp != NULL) {
        if (temp->expo != temp2->expo) {
            return false;
        }
        if (temp->coef != temp2->coef) {
            return false;
        }
        temp = temp->next;
        temp2 = temp2->next;

    }//endwhile
    return true;
}

LinkedList::~LinkedList() {
    removeAll();
}