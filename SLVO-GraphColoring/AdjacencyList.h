//
// Created by Eric Miao on 5/7/21.
//

#ifndef FINALPROJECT_ADJACENCYLIST_H
#define FINALPROJECT_ADJACENCYLIST_H
#include <iostream>
#include "Linkedlist.h"
#include "Vertex.h"
using namespace std;
class AdjList {
private:
    LinkedList<LinkedList<Vertex*>> data;
    string Name;
public:
    AdjList();
    AdjList(string);
    void setName(string val);

    // insert functions
    bool insertFor(Vertex* find, Vertex* val);
    void insertRow(Vertex* find);
    void moveBetweenRow(Vertex* prev, int newRowIndex);
    void removeVertex(int row, Vertex* item);
    void removeVertex(int row, int col);

    //utility functions
    bool isRowFound(Vertex* target);
    bool isEmpty();
    int findSmallestRow();
    int findLargestRow();
    int findRow(Vertex* target);
    LinkedList<Vertex*> getRow(int index);
    LinkedList<Vertex*> getRow(Vertex* target);
    int getRowSize(int index);
    int getRowSize(Vertex* target);
    int getSize();
    void print_with_delete_info();
    void print_with_current_degree_info();
    void print_with_color_info();
    void print();
    void print2();
    LinkedList<Vertex*> operator [] (int index);

};

AdjList::AdjList(){

}

AdjList::AdjList(string input){
    this->Name = input;
}


void AdjList::moveBetweenRow(Vertex* prev, int newRowIndex){
   this->insertFor(data[newRowIndex][0], prev);
}

void AdjList::removeVertex(int row, Vertex* item){
    for(int i = 0; i < data[row].getSize(); i++){
        if(data[row][i] == item){
            data[row].removeAt(i);
        }
    }

}

void AdjList::removeVertex(int row, int col){
    data[row].removeAt(col);

}


bool AdjList::isEmpty(){
    for (int i = 0; i < data.getSize(); i++) {
        if (getRowSize(i) > 1){
            return false;
        }
    }
    return true;
}

int AdjList::findSmallestRow(){
    for (int i = 0; i < data.getSize(); i++) {
        if (getRowSize(i) > 1){
            return i;
        }
    }
    return -1;
}

int AdjList::findLargestRow(){
    for (int i = data.getSize()-1; i >= 0; i--) {
        if (getRowSize(i) > 1){
            return i;
        }
    }
    return -1;

}

bool AdjList::isRowFound(Vertex* target){
    for (int i = 0; i < data.getSize(); i++) {
        if (*data[i][0] == *target) {
            return true;
        }
    }
    return false;
}

LinkedList<Vertex*> AdjList::getRow(int index){
    return data[index];
}

LinkedList<Vertex*> AdjList::getRow(Vertex* target){
    int index = findRow(target);
    return data[index];
}


int AdjList::findRow(Vertex* target){
    for (int i = 0; i < data.getSize(); i++) {
        if (data[i][0]->value == target->value){
            return i;
        }
    }
    return -1;
}


bool AdjList::insertFor(Vertex* find, Vertex* val){
    bool inserted = false;
    for (int i = 0; i < data.getSize(); i++) {
        if (*data[i][0] == *find) {
            for(int j = 0; j < data[i].getSize(); j++){
                if(*data[i][j] == *val){
                }
            }
            data[i].addBack(val);
            inserted = true;
        }
    }
    if (inserted != true) {
        LinkedList<Vertex*> temp;
        temp.addBack(find);
        temp.addBack(val);
        data.addBack(temp);
    }
    return true;
}

void AdjList::insertRow(Vertex* find){
    LinkedList<Vertex*> temp;
    temp.addBack(find);
    data.addBack(temp);
}

int AdjList::getRowSize(int index){
    if (index >= data.getSize()) {
        cout << "Array index out of bound, exiting";
        exit(0);
    }

    return data[index].getSize();
}

int AdjList::getRowSize(Vertex* target){
    for(int i = 0; i < this->getSize(); i++){
        if(data[i][0] == target){
            return data[i].getSize();
        }
    }
    return -1;
}

int AdjList::getSize(){
    return this->data.getSize();
}

void AdjList::setName(string val){
   this->Name = val;
}

void AdjList::print() {
    cout<<"---------------"<<this->Name<<"---------------"<<endl;
    for (int i = 0; i < data.getSize(); i++) {
        for (int j = 0; j < data[i].getSize(); j++) {
            if (j == data[i].getSize() - 1) {
                cout << "[" << *data[i][j] << "]";
            } else {
                cout << "[" << *data[i][j] << "]---";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void AdjList::print2() {
    cout<<"---------------"<<this->Name<<" (Pointers)"<<"---------------"<<endl;
    for (int i = 0; i < data.getSize(); i++) {
        for (int j = 0; j < data[i].getSize(); j++) {
            if (j == data[i].getSize() - 1) {
                cout << "[" << data[i][j] << "]";
            } else {
                cout << "[" << data[i][j] << "]---";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void AdjList::print_with_delete_info() {
    cout<<"---------------"<<this->Name<<" (Deleted)"<<"---------------"<<endl;
    for (int i = 0; i < data.getSize(); i++) {
        for (int j = 0; j < data[i].getSize(); j++) {
            if (j == data[i].getSize() - 1) {
                cout << "[" << *data[i][j]<<"]("<< data[i][j]->is_deleted << ")";
            } else {
                cout << "[" << *data[i][j]<<"]("<< data[i][j]->is_deleted << ")"<< "---";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void AdjList::print_with_color_info() {
    cout<<"---------------"<<this->Name<<" (Deleted)"<<"---------------"<<endl;
    for (int i = 0; i < data.getSize(); i++) {
        for (int j = 0; j < data[i].getSize(); j++) {
            if (j == data[i].getSize() - 1) {
                cout << "[" << *data[i][j]<<"]("<< data[i][j]->color << ")";
            } else {
                cout << "[" << *data[i][j]<<"]("<< data[i][j]->color << ")"<< "---";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void AdjList::print_with_current_degree_info() {
    cout<<"---------------"<<this->Name<<" (Current Degree)"<<"---------------"<<endl;
    for (int i = 0; i < data.getSize(); i++) {
        for (int j = 0; j < data[i].getSize(); j++) {
            if (j == data[i].getSize() - 1) {
                cout << "[" << *data[i][j]<<"]("<< data[i][j]->current_degree << ")";
            } else {
                cout << "[" << *data[i][j]<<"]("<< data[i][j]->current_degree << ")"<< "---";
            }
        }
        cout << endl;
    }
    cout << endl;
}


LinkedList<Vertex*> AdjList::operator [] (int index){
    if (index >= data.getSize()) {
        cout << "Array index out of bound, exiting";
        exit(0);
    }
    return data[index];
}

#endif //FINALPROJECT_ADJACENCYLIST_H
