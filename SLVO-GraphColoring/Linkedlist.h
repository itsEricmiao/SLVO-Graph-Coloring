//
// Created by Eric Miao on 4/29/21.
//

#ifndef FINALPROJECT_LINKEDLIST_H
#define FINALPROJECT_LINKEDLIST_H
#include <iostream>

using namespace std;

template<class T>
class Node {
    template<class U> friend
    class LinkedList;

private:
    T data;
    Node<T> *prev; //point to the previous node
    Node<T> *next; //point to the next node
public:
    Node();  //default constructor
    Node(const T &val);
    Node(const Node<T> &rhs);
    bool operator = (const Node<T>& rhs);

};

template<class T>
Node<T>::Node() {
    next = nullptr;
    prev = nullptr;
}

template<class T>
Node<T>::Node(const T &val) {
    next = nullptr;
    prev = nullptr;
    data = val;
}

template<class T>
Node<T>::Node(const Node<T> &rhs) {
    next = nullptr;
    prev = nullptr;
    data = rhs.data;
}

template<class T>
bool Node<T>::operator = (const Node<T>& rhs){
    return (this->value == rhs.value);

}

template<class T>
ostream& operator<<(ostream& os, const Node<T>& obj)
{
    // write obj to stream
    os<<&obj.data;
    return os;
}



template<class T>
class LinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    Node<T> *iterator;
    int size;

public:
    //Rule of 3:
    LinkedList();//default constructor
    LinkedList(T &val);

    LinkedList(const LinkedList<T> &list);//copy constructor
    ~LinkedList();//destructor

    LinkedList &operator=(const LinkedList<T> &rhs);

    friend ostream &operator<<(ostream &o, const LinkedList<T> &list);

    T &operator[](int index);


    void copyList(const LinkedList<T> &input);

    void printForward();

    void setSize(int num);

    int search(T val);

    int getSize();

    void addFront(T val);

    void addBack(T val);

    void addAt(int index, T val);

    bool ifContain(T val);

    bool moveIteratorToNext();

    void resetIterator();

    void removeAt(int index);

    T removeFront();

    T removeBack();

    T getIterator();

    Node<T> *getIteratorNode();

    bool isEmpty();

    void clear();

    T get(int index) const;

};


template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    iterator = nullptr;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(T &val) {
    Node<T> *temp = new Node<T>(val);
    head = temp;
    tail = temp;
    iterator = temp;
    size = 1;
}


template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    if (list.size == 0) {
        head = nullptr;
        tail = nullptr;
        iterator = nullptr;
        size = 0;
    } else {
        size = 0;
        copyList(list);
    }
}

template<class T>
void LinkedList<T>::resetIterator() {
    iterator = head;
}

template<class T>
bool LinkedList<T>::moveIteratorToNext() {
    if (iterator->next != nullptr) {
        iterator = iterator->next;
        return true;
    }
    return false;
}

template<class T>
T LinkedList<T>::getIterator() {
    return iterator->data;
}

template<class T>
int LinkedList<T>::getSize() {
    return size;
}

template<class T>
T &LinkedList<T>::operator[](int index) {
    while (index < size && index >= 0) {
        Node<T> *current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    this->clear();  //Clear the current list
    copyList(rhs);
    return *this;
}

template<class T>
void LinkedList<T>::copyList(const LinkedList<T> &input) {
    if (input.head == nullptr) {
        throw out_of_range("ERROR: LinkedList - copyList(): input linkedlist is invalid or empty");
    } else if (input.head != nullptr) {
        addBack(input.head->data);
        if (input.size == 1) {
            tail = iterator = head;
        } else {
            Node<T> *current = input.head;
            while (current != nullptr && current->next != nullptr) {

                if (current == input.iterator) {
                    iterator = current;
                }

                current = current->next;
                T tempData = current->data;
                addBack(tempData);
                tail = current;
            }
        }

        size = input.size;
    }
}

template<class T>
void LinkedList<T>::setSize(int num) {
    size = num;
}

template<class T>
T LinkedList<T>::get(int index) const {
    T current;
    if (index < size) {
        Node<T> *temp;
        temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        current = temp->data;
    }
    return current;
}

template<class T>
void LinkedList<T>::addFront(T val) {
    Node<T> *temp = new Node<T>(val);
    if (size == 0) {
        //edge case: if the list is empty
        head = tail = iterator = temp; //head and back point to newly created node
    } else {
        Node<T> *current = head;
        temp->next = current;
        current->prev = temp;
        head = temp;
    }
    size++;
}


template<class T>
void LinkedList<T>::addBack(T val) {
    Node<T> *temp = new Node<T>(val); //create a new node
    if (size == 0) //edge case: if the list is empty
    {
        head = tail = iterator = temp; //head and back point to newly created node
    } else //if the list is not empty
    {
        Node<T> *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = temp;
        temp->prev = current; //manually sets back to newly added element
    }
    size++;
}

template<class T>
void LinkedList<T>::addAt(int index, T val) {
    Node<T> *tempPrev;
    Node<T> *tempNext;

    if (index < 0 || index > size - 1) {
        throw out_of_range("Linkedlist - addAt()");
    } else if (index == 0 && head != nullptr) {
        addFront(val);
    } else if (head != nullptr && index < size - 1) {
        tempPrev = head;
        for (int i = 0; i < index; i++) {
            tempPrev = tempPrev->next;
        }
        tempNext = tempPrev->next;
        Node<T> *tempCurrent = new Node<T>(val);
        tempPrev->next = tempCurrent;
        tempCurrent->prev = tempPrev;
        tempNext->prev = tempCurrent;
        tempCurrent->next = tempNext;
        size++;
    } else if (head != nullptr && index == size - 1) {
        addBack(val);
    }
}

template<class T>
void LinkedList<T>::printForward() {
    Node<T> *current;
    Node<T> *tempNext;
    if (head != nullptr) {
        current = head;
        while (current->next != nullptr) {
            tempNext = current->next;
            cout << current->data << endl;
            current = tempNext;
        }
        cout << current->data << endl;
    }
}

template<class T>
void LinkedList<T>::clear() {
    Node<T> *temp;
    Node<T> *tempNext;
    if (head != nullptr) {
        temp = head;
        while (temp != nullptr) {
            tempNext = temp->next;
            delete temp;
            temp = tempNext;
        }
        head = nullptr;
    }
    size = 0;
}

template<class T>
void LinkedList<T>::removeAt(int index) {
    Node<T> *tempPrev;
    Node<T> *tempCurrent;
    Node<T> *tempNext;
    if (index > size) {
        throw out_of_range("ERROR: Out of range");
    } else if (index == 0 && head != nullptr) {
        tempNext = head->next;
        delete head;
        //tempNext->prev = nullptr;
        head = tempNext;
        size--;
    } else if (head != nullptr && index > 0 && index < this->getSize() - 1) {
        tempCurrent = head;
        for (int i = 0; i < index; i++) {
            if (tempCurrent->next != nullptr) {
                tempCurrent = tempCurrent->next;
            }
        }
        tempPrev = tempCurrent->prev;
        tempNext = tempCurrent->next;
        delete tempCurrent;
        tempPrev->next = tempNext;
        tempNext->prev = tempPrev;
        size--;
    } else if (head != nullptr && index > 0 && index == this->getSize() - 1) {
        tempCurrent = head;
        for (int i = 0; i < index; i++) {
            if (tempCurrent->next != nullptr) {
                tempCurrent = tempCurrent->next;
            }
        }
        tempPrev = tempCurrent->prev;
        delete tempCurrent;
        tempPrev->next = nullptr;
        tempPrev = tail;
        size--;
    }
}

template<class T>
T LinkedList<T>::removeFront() {
    removeAt(0);
}

template<class T>
T LinkedList<T>::removeBack() {
    removeAt(this->getSize() - 1);
}

template<class T>
bool LinkedList<T>::ifContain(T val) {
    if (size == 1) {
        if (head->data == val) {
            return true;
        }
    }
    Node<T> *temp = head;
    while (temp != nullptr && temp->next != nullptr) {
        if (temp->data == val) {
            return true;
        }
        temp = temp->next;
        if (temp->data == val) {
            return true;
        }
    }
    return false;
}


template<class T>
bool LinkedList<T>::isEmpty() {
    if (head == nullptr) {
        return true;
    }
    return false;
}


template<class T>
int LinkedList<T>::search(T val) {
    if (head != nullptr) {
        Node<T> *current = head;
        int count = 0;
        while (current->next != nullptr) {
            if (current->data == val) {
                return count;
            }
            current = current->next;
            count++;
        }
        if (current->data == val) {
            return count;
        }
    }
    return -1;
}

template<class T>
Node<T> *LinkedList<T>::getIteratorNode() {
    return iterator;
}

template<class T>
LinkedList<T>::~LinkedList() {
    clear();
}

#endif //FINALPROJECT_LINKEDLIST_H
