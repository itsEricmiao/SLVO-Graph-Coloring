//
// Created by Eric Miao on 4/29/21.
//

#ifndef FINALPROJECT_VERTEX_H
#define FINALPROJECT_VERTEX_H

#include "Linkedlist.h"
#include <iostream>
#include <ostream>
class Vertex{
public:
    int value;
    int original_degree;
    int current_degree;
    int color;
    bool is_deleted;


    Vertex();
    Vertex(int val){
        this->value = val;
        this->original_degree = 0;
        this->current_degree = 0;
        this->color = -1;
        this->is_deleted = false;
    }

    void reduce_one_degree(){
        this->current_degree = this->current_degree - 1;
    }

    void assign_degree(int init_degree){
        this->current_degree = init_degree;
        this->original_degree = init_degree;
    }

    void assign_color(int init_color){
        this->color = init_color;
    }

    void delete_vertex(){
        this->is_deleted = true;
    }


    int get_color(){
        return this->color;
    }

    bool operator == (const Vertex& rhs){
        return (this->value == rhs.value);
    }

    bool deleted(){
        return this->is_deleted;
    }


    void print_vertex_details(){
        cout<<"       Vertex value: "<<this->value<<endl;
        cout<<"              original degree: "<<this->original_degree<<endl;
        cout<<"              current degree: "<<this->current_degree<<endl;;
        cout<<"              color: "<<this->color<<endl;
        if (this->is_deleted == false){
            cout<<"       Deleted: No"<<endl;
        }else{
            cout<<"       Deleted: YES"<<endl;
        }
    }

};

ostream& operator<<(ostream& os, const Vertex& obj)
{
    // write obj to stream
    os<<obj.value;
    return os;
}
#endif //FINALPROJECT_VERTEX_H
