//
// Created by Eric Miao on 4/29/21.
//

#ifndef FINALPROJECT_VECTOR_H
#define FINALPROJECT_VECTOR_H
using namespace std;
template <typename T>
class myVector
{
private:
    T* data;
    int size;   //Number of the things added
    int capacity;  //The total number of available space
public:
    myVector();
    myVector(int initSize);
    myVector (const myVector<T>& arg); //copy constructor
    ~myVector();    //destructor

    myVector<T>& operator = (const myVector& arg);
    T & operator[] (int locaiton);

    int getCapacity();  //return the total capacity of the vector
    int getSize();  //return the total size of the vector
    int search(T target);
    T & elementAt(int loc);   //get the certain element of array
    T & pop();
    void setElmentAt(int loc, T val); //Set element at the certain place in a vector
    void print(); //Print the enrire Vector
    void putBack(const T& val);  //Take the next member and put it in the last char array
    void deleteAt(int loc); //delete certain index of the vector
    bool ifContains(T val, T val2);
    bool ifContains(T val);
    void reverse();
};


template <typename T>
myVector<T>::myVector()
{
    size = 0;
    capacity = 10;
    data = new T[10];
}


template <typename T>
myVector<T>::myVector(int initSize)
{
    size = 0;
    capacity = initSize;
    data = new T[capacity];
}

//Copy constructor
//Pointer to the invoking member
template <typename T>
myVector<T>::myVector(const myVector<T>& arg)
{
    //this is the pointer points to vector
    this -> capacity = arg.capacity;
    this->size = arg.size;
    data = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        this -> data[i] = arg.data[i];
    }

}

template <typename T>
myVector<T> & myVector<T>::operator= (const myVector<T>& arg)
{
    delete [] data;
    capacity = arg.capacity;
    size = arg.size;
    data = new T[capacity];
    for (int i = 0; i < capacity; i++)
    {
        data[i] = arg.data[i];
    }
    return *this;
}

template <typename T>
T & myVector<T>::operator[] (int locaiton)
{
    return this->elementAt(locaiton);
}

template <typename T>
T & myVector<T>::elementAt(int loc)  //location could be out of bound
{
    if (loc > capacity  || loc < 0)
    {
        throw logic_error("Vector::elementAt - location out of bounds");
    }
    else
    {
        return data[loc];
    }
}

template <typename T>
myVector<T>::~myVector()
{
    delete [] data;
}

template <typename T>
void myVector<T>::setElmentAt(int loc, T val)
{
    if (loc < capacity)
    {
        data[loc] = val;
        size++;
    }
    else
    {
        cout<<"Error: setElementAt"<<endl;
    }
}

template <typename T>
void myVector<T>::putBack(const T& val)
{
    //3 main oop
    //inheritance, polymophysm, and capsulism
    if (size == capacity)
    {
        T* temp = new T[capacity*2];
        for(int i = 0; i < size; i++)
        {
            temp[i] = data[i]; //*(temp+1) = *(data+1)
        }
        capacity = capacity * 2; //double the size value
        delete [] data; //delete the elements in the data array
        data = temp; //avoid dangling pointer
    }
    data[size] = val;
    size++;
}


template <typename T>
void myVector<T>::print()
{
    cout<<"The size of the Vector is "<<size<<endl;
    cout<<"The capacity of the Vector is "<<capacity<<endl;

    if(size > 0)
    {
        for (int i = 0; i < size; i ++)
        {
            cout<<"Number "<<i<<" element is: "<<data[i]<<endl;
        }
    }
    else if (size <= 0)
    {
        cout<<"Error: The vector is empty"<<endl;
    }
}

template <typename T>
void myVector<T>::deleteAt(int loc)
{
    T* temp = new T [capacity];
    for (int i = 0; i < loc; i ++)
    {
        temp[i] = data[i];
    }
    for (int i = loc+1; i < size; i ++)
    {
        temp[i-1] = data[i];
    }
    delete [] data;
    data = temp;
    size--;
}

template <typename T>
int myVector<T>::getCapacity()
{
    return capacity;
}

template <typename T>
int myVector<T>::getSize()
{
    return size;
}

template <typename T>
T & myVector<T>::pop()
{
    //cout<<"Size is "<<size<<endl;
    return this->elementAt(size-1);

}
template <typename T>
bool myVector<T>::ifContains(T val, T val2){
    for (int i = 0; i < this->size; i ++)
    {
        if(data[i] == val){
            return true;
        }
        if(data[i] == val2){
            return true;
        }
    }
    return false;
}

template <typename T>
bool myVector<T>::ifContains(T val){
    for (int i = 0; i < size; i ++)
    {
        if(data[i] == val){
            return true;
        }
    }
    return false;
}

template <typename T>
void myVector<T>::reverse(){
    myVector<T> newV;
    for(int i = this->size-1; i >= 0 ;i--){
        newV.putBack(data[i]);
    }
    for(int i = 0; i < newV.size; i++){
        data[i] = newV[i];
    }

}

template <typename T>
int myVector<T>::search(T target){
    for(int i = 0; i < size; i++){
        if (data[i] == target){
            return i;
        }
    }
    return -1;
}

#endif //FINALPROJECT_VECTOR_H
