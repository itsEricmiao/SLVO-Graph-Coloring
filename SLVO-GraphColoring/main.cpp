#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <stdlib.h>
#include <array>
#include "Vector.h"
#include "Linkedlist.h"
#include "AdjacencyList.h"
#include "Vertex.h"
#include <chrono>
#include <stack>
#include <queue>


using namespace std;
myVector<string> Parse(char* filename){
    ifstream fin(filename);
    myVector<string> input_file;
    if(fin.is_open()){
        string line;
        while ( getline (fin,line) )
        {
            input_file.putBack(line);
        }
        fin.close();
    }else{
        cout<<"Can't find input file for Part 1"<<endl;
        exit(0);
    }
    return input_file;
}

AdjList Random(int num_vertices, int number_edge, string DIST){
    AdjList list("Random Graph");
    myVector<int> vertex_values;
    myVector<Vertex*> vertex;

    myVector<pair<int, int>> edges;
    for(int i = 0; i < num_vertices; i++){
        Vertex* row = new Vertex(i);
        list.insertRow(row);
        vertex_values.putBack(i);
        vertex.putBack(row);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static default_random_engine generator(seed);

    if (DIST == "UNIFORM"){
        list.setName("RANDOM GRAPH - UNIFORM");
        int counter = 0;
        for(int i = 0; i < number_edge; i++){
            uniform_int_distribution<int> distribution(0,num_vertices-1);
            int random_number1 = distribution(generator);
            int random_number2 = distribution(generator);
            pair<int,int>p (random_number1, random_number2);
            pair<int,int>p2(random_number2, random_number1);
            while(edges.ifContains(p, p2) or random_number1 == random_number2){
                uniform_int_distribution<int> distribution(0,num_vertices-1);
                random_number1 = distribution(generator);
                random_number2 = distribution(generator);
                p.first = random_number1,
                p.second = random_number2;
                p2.first = random_number2;
                p2.second = random_number1;
            }
            Vertex* v1;
            Vertex* v2;
            int index = vertex_values.search(random_number1);
            v1 = vertex[index];
            int index2 = vertex_values.search(random_number2);
            v2 = vertex[index2];
            list.insertFor(v1, v2);
            list.insertFor(v2, v1);
            edges.putBack(p);
            edges.putBack(p2);
            counter++;
        }
    }else if(DIST == "SKEWED"){
        list.setName("RANDOM GRAPH - SKEWED");
        int counter = 0;
        for(int i = 0; i < number_edge; i++){
            std::array<double,2> intervals {0.0, float(num_vertices)};
            std::array<double,2> weights {1.0, 0.0};
            std::piecewise_linear_distribution<double> distribution (intervals.begin(),intervals.end(),weights.begin());
            int random_number1 = distribution(generator);
            int random_number2 = distribution(generator);
            pair<int,int>p (random_number1, random_number2);
            pair<int,int>p2(random_number2, random_number1);
            while(edges.ifContains(p, p2) or random_number1 == random_number2){
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                static default_random_engine generator(seed);
                std::array<double,2> intervals {0.0, float(num_vertices)};
                std::array<double,2> weights {1.0, 0.0};
                std::piecewise_linear_distribution<double> distribution (intervals.begin(),intervals.end(),weights.begin());
                random_number1 = distribution(generator);
                random_number2 = distribution(generator);
                p.first = random_number1,
                p.second = random_number2;
                p2.first = random_number2;
                p2.second = random_number1;
            }

            Vertex* v1 = new Vertex(random_number1);
            Vertex* v2 = new Vertex(random_number2);
            list.insertFor(v1, v2);
            list.insertFor(v2, v1);
            edges.putBack(p);
            edges.putBack(p2);
            counter++;
        }
        cout<<counter<<endl;
    }else if(DIST == "GAUSSIAN"){
        list.setName("RANDOM GRAPH - GAUSSIAN");
        for(int i = 0; i < number_edge; i++){

            std::normal_distribution<double> distribution(num_vertices/2,2.0);
            int random_number1 = distribution(generator);
            int random_number2 = distribution(generator);
            Vertex* v1 = new Vertex(random_number1);
            Vertex* v2 = new Vertex(random_number2);
            list.insertFor(v1, v2);
        }
    }else{
        cout<<"Error on DIST, please check the input file. "<<endl;
        exit(0);
    }
    return list;

}

AdjList Complete(int num_vertices) {
    AdjList list("Complete Graph");
    vector<Vertex*> allVs;
    Vertex* v;
    for (int i = 0; i < num_vertices; i++){
        v = new Vertex(i);
        allVs.push_back(v);
    }

    for (int i = 0; i < num_vertices; i++) {
        for(int j = 0; j < num_vertices; j++) {
            if(i != j) {
                Vertex* v1 = allVs[i];
                Vertex* v2 = allVs[j];
                list.insertFor(v1, v2);
            }
        }
    }
    return list;
}


AdjList Cycle(int num_vertices){
    AdjList list("Cycle Graph");
    vector<Vertex*> allVs;
    Vertex* v;
    for (int i = 0; i < num_vertices; i++){
        v = new Vertex(i);
        allVs.push_back(v);
    }

    for (int i = 0; i < num_vertices-1; i++){
        Vertex* v1 = allVs[i];
        Vertex* v2 = allVs[i+1];
        list.insertFor(v1, v2);
        list.insertFor(v2, v1);
    }
    Vertex* v0 = allVs[0];
    Vertex* v1 = allVs[allVs.size()-1];
    list.insertFor(v0, v1);
    list.insertFor(v1, v0);

    return list;
}

AdjList Testing(){
    AdjList list("Testing Graph");
    Vertex* v1 = new Vertex(1);
    Vertex* v2 = new Vertex(2);
    Vertex* v3 = new Vertex(3);
    Vertex* v4 = new Vertex(4);

    list.insertFor(v1, v2);
    list.insertFor(v2, v1);

    list.insertFor(v1, v4);
    list.insertFor(v4, v1);

    list.insertFor(v2, v4);
    list.insertFor(v4, v2);

    list.insertFor(v2, v3);
    list.insertFor(v3, v2);
    return list;
}

AdjList Testing2(){
    AdjList list("Testing Graph");
    Vertex* v0 = new Vertex(0);
    Vertex* v1 = new Vertex(1);
    Vertex* v2 = new Vertex(2);
    Vertex* v3 = new Vertex(3);
    Vertex* v4 = new Vertex(4);
    Vertex* v5 = new Vertex(5);
    Vertex* v6 = new Vertex(6);
    Vertex* v7 = new Vertex(7);
    Vertex* v8 = new Vertex(8);
    Vertex* v9 = new Vertex(9);

    list.insertFor(v7, v3);
    list.insertFor(v3, v7);
    list.insertFor(v5,v8);
    list.insertFor(v8,v5);
    list.insertFor(v8,v1);
    list.insertFor(v1,v8);
    list.insertFor(v3,v1);
    list.insertFor(v1,v3);
    list.insertFor(v9,v4);
    list.insertFor(v4,v9);
    list.insertFor(v3,v4);
    list.insertFor(v4,v3);

    list.insertFor(v1,v7);
    list.insertFor(v7,v1);
    list.insertFor(v9,v5);
    list.insertFor(v5,v9);
    list.insertFor(v9,v3);
    list.insertFor(v3,v9);
    list.insertFor(v4,v7);
    list.insertFor(v7,v4);
    list.insertFor(v0,v5);
    list.insertFor(v5,v0);
    list.insertFor(v2,v4);
    list.insertFor(v4,v2);
    list.insertFor(v5,v4);
    list.insertFor(v4,v5);
    list.insertFor(v5,v6);
    list.insertFor(v6,v5);
    list.insertFor(v0,v2);
    list.insertFor(v2,v0);
    list.insertFor(v2,v9);
    list.insertFor(v9,v2);
    list.insertFor(v8,v7);
    list.insertFor(v7,v8);
    list.insertFor(v0,v6);
    list.insertFor(v6,v0);
    list.insertFor(v1,v4);
    list.insertFor(v4,v1);
    list.insertFor(v5,v3);
    list.insertFor(v3,v5);

    return list;
}

void Test_Linear_Skewed_Distribution(){
    const int nrolls = 10000; // number of experiments
    const int nstars = 100;   // maximum number of stars to distribute
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::array<double,2> intervals {0.0, 10.0};
    std::array<double,2> weights {1.0, 0.0};
    std::piecewise_linear_distribution<double>distribution (intervals.begin(),intervals.end(),weights.begin());
    int p[10]={};
    for (int i=0; i<nrolls; ++i) {
        int number = distribution(generator);
        ++p[number];
    }

    std::cout << "Skewed Distribution from 0 - 9:" << std::endl;
    for (int i=0; i<9; ++i) {
        std::cout << i << "-" << i+1 << ": ";
        std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
    }
    std::cout<<std::endl;
}
void Test_Uniform_Distribution(){
    const int nrolls = 10000; // number of experiments
    const int nstars = 95;    // maximum number of stars to distribute
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0,9);

    int p[10]={};

    for (int i=0; i<nrolls; ++i) {
        int number = distribution(generator);
        ++p[number];
    }

    std::cout << "Uniform Distribution from 0 - 9:" << std::endl;
    for (int i=0; i<10; ++i)
        std::cout << i << ": " << std::string(p[i]*nstars/nrolls,'*') << std::endl;
    std::cout<<std::endl;
}
void Test_GAUSSIAN_Distribution(){
    const int nrolls=10000;  // number of experiments
    const int nstars=100;    // maximum number of stars to distribute
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(5.0,2.0);

    int p[10]={};

    for (int i=0; i<nrolls; ++i) {
        double number = distribution(generator);
        if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
    }

    std::cout << "GAUSSIAN Distribution (2.0, 5.0) from 0 - 9:" << std::endl;

    for (int i=0; i<10; ++i) {
        std::cout << i << "-" << (i+1) << ": ";
        std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
    }
}

pair<AdjList, AdjList> Build_Degree_List(AdjList Graph){
    // find the longest degree in the Graph
    int max_degree = 0;
    for(int i = 0; i < Graph.getSize(); i++){
        int degree_of_each = Graph.getRowSize(i);
        if (degree_of_each > max_degree){
            max_degree = degree_of_each;
        }
    }

    // build the degree list, creating the front node of each row first
    AdjList Degree("Degree List");
    for(int i = 0; i <= max_degree; i++){
        Vertex* frontNode = new Vertex(i);
        Degree.insertRow(frontNode);
    }
    for(int i = 0; i < Graph.getSize(); i++){
        int rowSize = Graph[i].getSize()-1;
        Vertex* Node = Graph[i][0];
        Vertex* frontNode = new Vertex(rowSize);
        Node->assign_degree(rowSize);
        Degree.insertFor(frontNode, Node);
    }

    return pair<AdjList, AdjList>(Graph, Degree);
}


//•	Smallest last vertex ordering
//•	Smallest original degree last ordering
//• Largest last vertex ordering
//•	Uniform random ordering
//• DFS
//• BFS

void DFS(AdjList Graph, AdjList Degree, myVector<Vertex*>& Ordering){
    cout<<"============================================= "<<endl;
    cout<<"Depth First Search"<<endl;
    cout<<"============================================="<<endl;
    if(Degree.getRowSize(0) > 1){
        for(int i = 1; i < Degree[0].getSize(); i++){
            Ordering.putBack(Degree[0][i]);
        }
    }
    stack<Vertex*> myStack;
    Vertex* firstVertex = Graph[0][0];
    myStack.push(firstVertex);
    Ordering.putBack(firstVertex);
    firstVertex->delete_vertex();
    while (!myStack.empty()){
        Vertex* current = myStack.top();
        myStack.pop();
        LinkedList<Vertex*> row = Graph.getRow(current);
        for(int i = 1; i < row.getSize(); i++){
            if(!row[i]->deleted()){
                myStack.push(row[i]);
                Ordering.putBack(row[i]);
                row[i]->delete_vertex();
            }
        }
    }
}

void BFS(AdjList Graph, AdjList Degree, myVector<Vertex*>& Ordering){
    cout<<"============================================= "<<endl;
    cout<<"Breadth First Search"<<endl;
    cout<<"============================================="<<endl;
    if(Degree.getRowSize(0) > 1){
        for(int i = 1; i < Degree[0].getSize(); i++){
            Ordering.putBack(Degree[0][i]);
        }
    }
    queue<Vertex*> myQueue;
    Vertex* firstVertex = Graph[0][0];
    myQueue.push(firstVertex);
    Ordering.putBack(firstVertex);
    firstVertex->delete_vertex();
    while (!myQueue.empty()){
        Vertex* current = myQueue.front();
        myQueue.pop();
        LinkedList<Vertex*> row = Graph.getRow(current);
        for(int i = 1; i < row.getSize(); i++){
            if(!row[i]->deleted()){
                myQueue.push(row[i]);
                Ordering.putBack(row[i]);
                row[i]->delete_vertex();
            }
        }
    }

}

void Largest_last_vertex_ordering(AdjList Graph, AdjList Degree, myVector<Vertex*>& Ordering){
    cout<<"============================================= "<<endl;
    cout<<"Largest Last Vertex Ordering"<<endl;
    cout<<"============================================="<<endl;
    // find and remove the largest degree first
    // while degree has vertex in it

    while(!Degree.isEmpty()) {
        int largest_degree_vertex_row_index = Degree.findLargestRow();
        int index_in_row = Degree[largest_degree_vertex_row_index].getSize() - 1;
        Vertex *largest_degree_vertex = Degree[largest_degree_vertex_row_index][index_in_row];
        // found the vertex and now we remove it from the graph and degree
        int prev_degree = largest_degree_vertex->current_degree;
        largest_degree_vertex->delete_vertex();
        Degree.removeVertex(largest_degree_vertex_row_index, index_in_row);
        Degree.removeVertex(prev_degree, index_in_row);
        Ordering.putBack(largest_degree_vertex);

        LinkedList<Vertex *> largest_degree_vertex_row = Graph.getRow(largest_degree_vertex);
        // reduce each connected vertexes by 1 degree
        int i = 1;
        while(i < largest_degree_vertex_row.getSize()){
            Vertex *current_vertex = largest_degree_vertex_row[i];
            if (!current_vertex->deleted() && current_vertex->current_degree > 0) {
                int prev_degree = current_vertex->current_degree;
                current_vertex->reduce_one_degree();
                int current_degree = current_vertex->current_degree;
                Degree.removeVertex(prev_degree, current_vertex);
                Degree.moveBetweenRow(current_vertex, current_degree);
            }else{
            }
            i++;
        }
    }
    cout<<"After removing all vertices: "<<endl;
    Degree.print();
    Graph.print_with_delete_info();
    Ordering.reverse();
}

// Below is my original SLVO with detailed comment
void Smallest_last_vertex_ordering(AdjList Graph, AdjList Degree, myVector<Vertex*>& Ordering){
    cout<<"\n============================================= "<<endl;
    cout<<"Smallest_last_vertex_ordering "<<endl;
    cout<<"=============================================\n"<<endl;
    // find and remove the smallest degree first
    // while degree has vertex in it

    while(!Degree.isEmpty()) {
        int smallest_degree_vertex_row_index = Degree.findSmallestRow();
        int index_in_row = Degree[smallest_degree_vertex_row_index].getSize() - 1;
        Vertex *smallest_degree_vertex = Degree[smallest_degree_vertex_row_index][index_in_row];
        cout<<"Smallest degree is "<<smallest_degree_vertex_row_index<<" which is ["<<*smallest_degree_vertex<<"]"<<endl;
        // found the vertex and now we remove it from the graph and degree
        int prev_degree = smallest_degree_vertex->current_degree;
        smallest_degree_vertex->delete_vertex();
        cout<<"remove vertex ["<<*smallest_degree_vertex<<"] from the graph"<<endl;
//        Degree.removeVertex(smallest_degree_vertex_row_index, index_in_row);
        Degree.removeVertex(prev_degree, index_in_row);
        Ordering.putBack(smallest_degree_vertex);

        // after remove the vertex, we need to update the degree of all vertex it connected to
        // int number_of_vertex_needs_update = Graph.getRowSize(smallest_degree_vertex) - 1;
        // get the entire row

        LinkedList<Vertex *> smallest_degree_vertex_row = Graph.getRow(smallest_degree_vertex);
        // reduce each connected vertexes by 1 degree
        int i = 1;
        while(i < smallest_degree_vertex_row.getSize()){
            Vertex *current_vertex = smallest_degree_vertex_row[i];
            if (!current_vertex->deleted() && current_vertex->current_degree > 0) {
                int prev_degree = current_vertex->current_degree;
                current_vertex->reduce_one_degree();
                int current_degree = current_vertex->current_degree;
                Degree.removeVertex(prev_degree, current_vertex);
                Degree.moveBetweenRow(current_vertex, current_degree);
                cout<<"Moving vertex ["<<*current_vertex<<"] from "<<prev_degree<<" to "<<current_degree<<endl;
                Degree.print_with_current_degree_info();
            }else{
            }
            i++;
        }
    }
    cout<<"After removing all vertices: "<<endl;
    Degree.print();
    Graph.print_with_delete_info();
    Ordering.reverse();
}


void Smallest_original_degree_last_ordering(AdjList Graph, AdjList Degree, myVector<Vertex*>& Ordering){
    cout<<"============================================= "<<endl;
    cout<<"Smallest Original Degree Last Ordering"<<endl;
    cout<<"============================================="<<endl;
    /*The Smallest Original Degree Last method is a subset of the smallest last ordering.
     * You should determine the vertices to color based on their original degree,
     * but not remove them from the graph as you do it.
     * This should run in THETA(V+E).
    */

    for(int i = 0; i < Graph.getSize(); i++){
        Ordering.putBack(Graph[i][0]);
    }
    // Sort the vector by the original degree
    for(int j = 0; j < Ordering.getSize(); j++){
        for(int k = j+1; k < Ordering.getSize(); k++){
            if (Ordering[j]->current_degree < Ordering[k]->current_degree){
                Vertex* temp = Ordering[j];
                Ordering[j] = Ordering[k];
                Ordering[k] = temp;
            }
        }
    }
}

void Uniform_random_ordering(AdjList Graph, AdjList Degree, myVector<Vertex*>& Ordering){
    cout<<"============================================= "<<endl;
    cout<<"Uniform Random Ordering"<<endl;
    cout<<"============================================="<<endl;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    int num_vertices = Graph.getSize();
    for(int i = 0; i < num_vertices; i++) {
        uniform_int_distribution<int> distribution(0, num_vertices-1);
        int random_number = distribution(generator);
        while(Graph[random_number][0]->deleted()){
            random_number = distribution(generator);
        }
        Graph[random_number][0]->delete_vertex();
        Ordering.putBack(Graph[random_number][0]);
    }
}


int Terminal_Clique(myVector<Vertex*> Ordering){
    int prev_degree = -1;
    for(int i = 0; i < Ordering.getSize(); i++){
        if(Ordering[i]->current_degree == prev_degree+1){
            prev_degree ++;
        }else{
            return prev_degree+1;
        }
    }
    return prev_degree;
}

int Max_Degree(myVector<Vertex*> Ordering){
    int max = 0;
    for(int i = 0; i < Ordering.getSize(); i++){
        if(Ordering[i]->current_degree > max){
            max = Ordering[i]->current_degree;
        }
    }
    return max;
}

// A graph indicating the degree when deleted on the vertical axes and the order colored on the x-axis.
// The maximum degree when deleted.
// The size of the terminal clique.

int Graph_coloring(AdjList Graph, myVector<Vertex*>& Ordering){
    cout<<"============================================= "<<endl;
    cout<<"Graph Coloring"<<endl;
    cout<<"============================================="<<endl;
    myVector<int> Colors;
    int terminal_clique_size = Terminal_Clique(Ordering);
    for(int i = 0; i < terminal_clique_size; i++){
        Ordering[i]->assign_color(i);
        Colors.putBack(i);
    }

    for(int i = terminal_clique_size; i < Ordering.getSize(); i++) {
        Vertex *current_vertex = Ordering[i];
        LinkedList<Vertex *> row = Graph.getRow(current_vertex);
        myVector<int> avoid_colors;
        for (int j = 0; j < row.getSize(); j++) {
            // check each connected vertex
            avoid_colors.putBack(row[j]->get_color());
        }

        // now we have the color to avoid
        // we choose the color that are not in the avoid_color vector but in the Colors vector
        myVector<int> color_available_to_use;
        for(int k = 0; k < Colors.getSize(); k++){
            for(int l = 0; l < avoid_colors.getSize(); l++){
                if(Colors[k] == avoid_colors[l]){
                    break;
                }
                if(Colors[k] != avoid_colors[l] && l == avoid_colors.getSize()-1){
                    color_available_to_use.putBack(Colors[k]);
                }
            }
          }
        current_vertex->assign_color(color_available_to_use[0]);
    }

    for(int u = 0; u < Ordering.getSize(); u++){
        cout<<*Ordering[u]<<"|"<<Ordering[u]->get_color()<<" ";
    }

    return Colors.getSize();
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
// Greedy Algorithm reference: https://www.geeksforgeeks.org/graph-coloring-set-2-greedy-algorithm/
int Greedy_Coloring(AdjList Graph, myVector<Vertex*>& Ordering){
    cout<<"============================================= "<<endl;
    cout<<"Greedy Graph Coloring"<<endl;
    cout<<"============================================="<<endl;
    int V = Graph.getSize();
    myVector<Vertex*> result;
    // Initialize remaining V-1 vertices as unassigned
    for(int k = 0; k < V; k++){
        result.putBack(Graph[k][0]);
    }
    // Assign the first color to first vertex
    result[0]->assign_color(0);
    cout<<"Assign "<<*result[0]<<" to color 0"<<endl;

    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    bool available[V];
    for (int cr = 0; cr < V; cr++){
        available[cr] = true;
    }
    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        for(int i = 0; i < Graph[u].getSize(); i++){
            int adjacent_color = Graph[u][i]->get_color();
            if(adjacent_color!=-1){
                available[adjacent_color] = false;
            }
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++){
            if (available[cr]){
                break;
            }
        }
        cout<<"Assign color "<<cr<<" to "<<*result[u]<<endl;
        result[u]->assign_color(cr); // Assign the found color

        // Reset the values back to false for the next iteration
        for(int m = 0; m < Graph[u].getSize(); m++) {
            int adjacent_color = Graph[u][m]->get_color();
            if (adjacent_color != -1){
                available[adjacent_color] = true;
            }
        }
    }

    int number_of_color = 0;
    for (int u = 0; u < V; u++){
        cout << "Vertex " << *result[u] << " --->  Color "
             << result[u]->get_color() << endl;
        if(result[u]->get_color()>number_of_color){
            number_of_color = result[u]->get_color();
        }
    }
    return number_of_color+1;
}


void PartI_Timing(){
    using namespace std::chrono;
    vector<microseconds> Y;
    vector<int> X;
    for(int i = 10; i < 1000; i=i+50){
//        int V = i;
//        int E = i*2;
//        string DIST = "GAUSSIAN";
        auto start = high_resolution_clock::now();
        AdjList list = Complete(i);
//        AdjList list = Random(V,E,DIST);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
//        cout << duration.count() << endl;
        Y.push_back(duration);
        X.push_back(i);
    }

    for(int i = 0; i < X.size(); i++){
        cout<<X[i]<<" "<<Y[i].count()<<endl;
    }
}

void PartII_Timing(){
    using namespace std::chrono;
    vector<microseconds> Y;
    vector<int> X;
    for(int i = 50; i < 500; i=i+50){
        int V = i;
        int E = i*2;
        string DIST = "SKEWED";
        myVector<Vertex*> Coloring;
//        AdjList list = Complete(i);
        AdjList list = Random(V,E,DIST);
        pair<AdjList,AdjList> Result = Build_Degree_List(list);
        Smallest_last_vertex_ordering(Result.first, Result.second, Coloring);
        auto start = high_resolution_clock::now();
        int color_number = Greedy_Coloring(Result.first, Coloring);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        Y.push_back(duration);
        X.push_back(i);
    }

    for(int i = 0; i < X.size(); i++){
        cout<<X[i]<<" "<<Y[i].count()<<endl;
    }

}

int main(int argc, char** argv) {
    /*
     •   V = Number of vertices. (MAX = 10,000)
     •	E = Number of conflicts between pairs of vertices for random graphs. (MAX = 2,000,000)
     •	G = COMPLETE | CYCLE | RANDOM (with DIST below)
     •	DIST = UNIFORM | SKEWED | YOURS
 */
    myVector<string>input_file = Parse(argv[1]);
    int V = atoi(input_file[0].c_str());
    int E = atoi(input_file[1].c_str());
    if (V > 10000){
        V = 10000;
    }
    if (E > 2000000){
        E = 2000000;
    }

    cout<<"Step I: Parsing: "<<endl;
    string G = input_file[2];
    string DIST = input_file[3];
    AdjList list("Graph");

    if (G =="COMPLETE") {
        list = Complete(V);
    }else if (G =="CYCLE") {
        list = Cycle(V);
    }else if (G =="RANDOM"){
        list = Random(V,E,DIST);

    }else{
        cout<<"Error on the input file for part 1"<<endl;
        exit(0);
    }

//    list = Testing();
    pair<AdjList,AdjList> Result = Build_Degree_List(list);
    myVector<Vertex*> Coloring;
    Result.first.print();
    Result.second.print();

    cout<<"Step II: Graph Ordering: "<<endl;
    Smallest_last_vertex_ordering(Result.first, Result.second, Coloring);
//    Largest_last_vertex_ordering(Result.first, Result.second, Coloring);
//    Uniform_random_ordering(Result.first, Result.second, Coloring);
//    Smallest_original_degree_last_ordering(Result.first, Result.second, Coloring);
//    DFS(Result.first, Result.second, Coloring);
//    BFS(Result.first, Result.second, Coloring);

    int terminal_clique_size = Terminal_Clique(Coloring);
    int max_degree = Max_Degree(Coloring);
    cout<<"Result:"<<endl;
    cout<<" • Degree Adjacency List (With Degree When Deleted From The Graph):"<<endl;
    Result.second.print_with_current_degree_info();
    cout<<" • Graph Adjacency List:"<<endl;
    Result.first.print();
    cout<<" • Terminal Clique Size: "<<terminal_clique_size<<endl;
    cout<<" • Maximum Degree When Deleted: "<<max_degree<<endl;
    cout<<" • Number of Vertex: "<<Coloring.getSize()<<endl;
    cout<<" • Ordering: "<<endl;
    cout<<"   ";
    for(int i = 0; i < Coloring.getSize(); i++){
        cout<<"["<<*Coloring[i]<<"]-("<<Coloring[i]->current_degree<<")  ";
    }
    cout<<endl;
    cout<<"Step III: Graph Coloring:"<<endl;
    int color_number = Greedy_Coloring(Result.first, Coloring);
    cout<<"Graph needs minimum of "<<color_number<<" colors"<<endl;

//
//    Test_Linear_Skewed_Distribution();
//    Test_Uniform_Distribution();
//    Test_GAUSSIAN_Distribution();

    return 0;
}
